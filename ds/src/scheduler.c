/*******************************************************************************
*  scheduler.c                                                                 *
*  Author: Ariel                                                               *
*  Reviewer: Liel                                                              *
*******************************************************************************/
#include <stdlib.h> /* malloc, free */
#include <assert.h> /* assert       */
#include <unistd.h> /* sleep        */

#include "scheduler.h"
#include "task.h"
#include "pqueue.h"
#include "uid.h"

enum stop_status
{
	CONTINUE = 0,
	STOP = 1
};

enum ilrd_status
{
	ILRD_SUCCESS = 0,
	ILRD_FAIL = 1
};

typedef enum task_func_status
{
	TASK_SUCCESS = 0,
	TASK_NOT_COMPLETE = 1,
	TASK_TASK_ERROR = 2
}task_func_status_ty;

struct scheduler
{
    pqueue_ty *pq;
    int stop;
};

static int cmp_func(const void *task1, const void *task2);
static int match_func(const void *uid1, const void *uid2);

/***** SchedulerCreate ********************************************************/

scheduler_ty *SchedulerCreate(void)
{
	scheduler_ty *new_scheduler = (scheduler_ty *)malloc(sizeof(scheduler_ty));
	
	if( !new_scheduler ) 
	{
		return NULL;
	}
	
	new_scheduler->pq = PQCreate(cmp_func);
	
	if( !new_scheduler->pq )
	{
		free(new_scheduler);
		new_scheduler = NULL;
		
		return NULL;
	}
	
	new_scheduler->stop = CONTINUE;
	
	return (new_scheduler);
}

/***** SchedulerDestroy *******************************************************/

void SchedulerDestroy(scheduler_ty *scheduler)
{
	if( scheduler )
	{
		SchedulerClear(scheduler);
		
		PQDestroy(scheduler->pq);
		
		free(scheduler);
		scheduler = NULL;
	}
}

/***** SchedulerClear *********************************************************/

void SchedulerClear(scheduler_ty *scheduler)
{
	task_ty *dequeued_task = NULL;
	
	assert(scheduler);
	assert(scheduler->pq);
	
	while( !SchedulerIsEmpty(scheduler) )
	{
		dequeued_task = (task_ty *)PQDequeue(scheduler->pq);
		
		TaskDestroy(dequeued_task);
	}
}

/***** SchedulerIsEmpty *******************************************************/

int SchedulerIsEmpty(const scheduler_ty *scheduler)
{
	assert(scheduler);
	assert(scheduler->pq);
	
	return (PQIsEmpty(scheduler->pq));
}

/***** SchedulerSize **********************************************************/

size_t SchedulerSize(const scheduler_ty *scheduler)
{
	assert(scheduler);
	assert(scheduler->pq);
	
	return (PQSize(scheduler->pq));
}

/***** SchedulerStop **********************************************************/

void SchedulerStop(scheduler_ty *scheduler)
{
	assert(scheduler);
	assert(scheduler->pq);
	
	scheduler->stop = STOP;
}

/***** SchedulerRemove ********************************************************/

int SchedulerRemove(scheduler_ty *scheduler, uid_ty id)
{
	void *remove_ret = NULL;
	
	assert(scheduler);
	assert(scheduler->pq);
	
	remove_ret = PQErease(scheduler->pq, match_func, &id);
	
	if( remove_ret ) 
	{
		TaskDestroy((task_ty *)remove_ret);
		return (ILRD_SUCCESS);
	}
	
	return (ILRD_FAIL);
}

/***** SchedulerAdd ***********************************************************/

uid_ty SchedulerAdd(scheduler_ty *scheduler, time_t interval, scheduler_func_ty func, 
                    void *param)
{
	task_ty *new_task = NULL;
	uid_ty bad_uid = UidGetBadUid();
	int enqueue_res = ILRD_SUCCESS;
	
	assert(scheduler);
	assert(scheduler->pq);
	assert(func);
	
	new_task = TaskCreate(interval, (task_func_ty)func, param);
	
	if( !new_task ) 
	{
		return (bad_uid);
	}
	
	enqueue_res = PQEnqueue(scheduler->pq, (task_ty *)new_task);
	
	if( enqueue_res == ILRD_SUCCESS )
	{
		return (TaskGetUID(new_task));
	}
	
	TaskDestroy(new_task);
	return (bad_uid);
}

/***** SchedulerRun ***********************************************************/

status_of_execution_ty SchedulerRun(scheduler_ty *scheduler)
{
	task_func_status_ty status = TASK_SUCCESS;
	task_ty *dequeued_task = NULL;
	time_t diff_ttr_now = 0;
	int enqueue_status = ILRD_SUCCESS;
	
	assert(scheduler);
	assert(scheduler->pq);
	
	while( !SchedulerIsEmpty(scheduler) && !scheduler->stop && status != TASK_TASK_ERROR)
	{
		dequeued_task = (task_ty *)PQDequeue(scheduler->pq);
		
		diff_ttr_now = TaskGetTimeToRun(dequeued_task) - time(NULL);
		
		while( diff_ttr_now > 0 )
		{
			diff_ttr_now = sleep(diff_ttr_now);
		}
		
		status = TaskRun(dequeued_task);
		
		if( status != TASK_NOT_COMPLETE )
		{
			TaskDestroy(dequeued_task);
		}
		
		else
		{
			TaskUpdateTimeToRun(dequeued_task);
			enqueue_status = PQEnqueue(scheduler->pq, dequeued_task);
			
			if( enqueue_status == ILRD_FAIL )
			{
				TaskDestroy(dequeued_task);
				return (SYS_ERROR);
			}
		}	
	}
	
	if( scheduler->stop == STOP )
	{
		scheduler->stop = CONTINUE;
		return (STOPPED);
	}
	
	if( status == TASK_TASK_ERROR )
	{
		return (TASK_ERROR);
	}
	
	return (SUCCESS);
}

/***** Helper Functions *******************************************************/

static int cmp_func(const void *task1, const void *task2)
{
	return (TaskGetTimeToRun((task_ty *)task2) - TaskGetTimeToRun((task_ty *)task1));
}

static int match_func(const void *uid1, const void *uid2)
{
	return (UidIsSame(*(uid_ty *)uid1, *(uid_ty *)uid2));
}

