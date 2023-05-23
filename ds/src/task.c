/*******************************************************************************
*  task.c                                                                      *
*  Author: Ariel                                                               *
*  Reviewer: Liel                                                              *
*******************************************************************************/
#include <time.h>   /* time_t       */
#include <stdlib.h> /* malloc, free */
#include <assert.h> /* assert       */

#include "task.h"

struct task
{
    uid_ty uid;
    time_t interval;
    time_t time_to_run;
    task_func_ty function;
    void *param;
};

/***** TaskCreate *************************************************************/

task_ty *TaskCreate(time_t interval, task_func_ty function, void *param)
{
	task_ty *new_task = (task_ty *)malloc(sizeof(task_ty));
	uid_ty bad_uid = UidGetBadUid();
	
	if( !new_task ) 
	{
		return NULL;
	}
	
	new_task->uid = UidCreate();
	
	if( UidIsSame(new_task->uid, bad_uid) )
	{
		free(new_task);
		new_task = NULL;
		
		return NULL;
	}
	
	new_task->interval = interval;
	new_task->time_to_run = time(NULL) + interval;
	new_task->function = function;
	new_task->param = param;
	
	return (new_task);
}

/***** TaskDestroy ************************************************************/

void TaskDestroy(task_ty *task)
{
	if( task )
	{			
		free(task);
		task = NULL;
	}
}

/***** TaskGetUid *************************************************************/

uid_ty TaskGetUID(const task_ty *task)
{
	assert(task);
	
	return (task->uid);
}

/***** TaskGetTimeToRun *******************************************************/

time_t TaskGetTimeToRun(const task_ty *task)
{
	assert(task);
	
	return (task->time_to_run);
}

/***** TaskUpdateTimeToRun ****************************************************/

void TaskUpdateTimeToRun(task_ty *task)
{
	assert(task);
	
	task->time_to_run = time(NULL) + task->interval;
}

/***** TaskRun ****************************************************************/

int TaskRun(const task_ty *task)
{
	assert(task);
	
	return (task->function(task->param));
}
