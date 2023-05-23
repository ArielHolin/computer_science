/******************************************************************************
* Description: Header of scheduler 
* Name: HRD20
* Date: 29/08/21
* Versions: 1.0 ready for review
* Versions: 1.1  after class review
* Versions: 1.2  after Yishai suggestion to name different typedefs for functions
            1.3 header compiles
*******************************************************************************/
#ifndef __SCHEDULER_H__
#define __SCHEDULER_H__

#include <stddef.h> /* size_t */
#include <time.h> /*time_t*/

#include "uid.h"

typedef enum status_of_execution
{
    SUCCESS = 0,
    STOPPED = 1,
    TASK_ERROR = 2,
    SYS_ERROR = 3
}status_of_execution_ty;

typedef struct scheduler scheduler_ty;

/*
scheduler_func_ty is the type of the functions the user of the 
scheduler want to schedule for execution.

return value: status of execution.
				0 - success - completed
				1 - not completed
				2 - error 

argument: param - for user parameter/data.
*/

typedef int (*scheduler_func_ty)(void *param);

/*******************************************************************************
* Function Description: scheduler creator
			       
* Arguments: void

* Return value: pointer to the scheduler
   
* Notes: if failed returns NULL

* Time Complexity: O(1)
*******************************************************************************/
scheduler_ty *SchedulerCreate(void);

/*******************************************************************************
* Function Description: scheduler destroyer
			       
* Arguments: pointer to the scheduler to destroy

* Return value:
   
* Notes: No operation is performed if scheduler = NULL

* Time Complexity: O(n) - n = number of tasks
*******************************************************************************/
void SchedulerDestroy(scheduler_ty *scheduler);

/*******************************************************************************
* Function Description: adds a task to the scheduler
			       
* Arguments: scheduler: pointer to the scheduler to add to
             interval: time to intertval the function
             func: pointer to the function to schedule
             param: parameter to pass to the function (for user convenience)

* Return value: uid of the created task or bad_uid on fail
   
* Notes: undefined behavior if NULL is recieved

* Time Complexity: O(n) - n = number of tasks
*******************************************************************************/
uid_ty SchedulerAdd(scheduler_ty *scheduler, time_t interval, scheduler_func_ty func, 
                    void *param);

/*******************************************************************************
* Function Description: deletes a task from the scheduler
			       
* Arguments: scheduler: pointer to the scheduler to delete from
            uid: the task id to remove

* Return value: return 0 in case id was found and removed, else - return 1.
   
* Notes: undefined behavior if NULL is recieved

* Time Complexity: O(n) - n = number of tasks
*******************************************************************************/
int SchedulerRemove(scheduler_ty *scheduler, uid_ty id);

/*******************************************************************************
* Function Description: runs the scheduler
			       
* Arguments: pointer to the scheduler to run

* Return value: status_of_execution.
   
* Notes: undefined behavior if  NULL is recieved. in case actual time surpass 
* 		 the starting time, function will be executed immediately.
         In case one of the function stops or fails, SchedulerRun stop, return error value,
         and the function will no longer be in the scheduler.
         
* Time Complexity: O(n) - n = number of tasks
*******************************************************************************/
status_of_execution_ty SchedulerRun(scheduler_ty *scheduler);

/*******************************************************************************
* Function Description: stops the scheduler
			       
* Arguments: pointer to the scheduler to stop

* Return value: None.
   
* Notes: undefined behavior if  NULL is recieved

* Time Complexity: O(1)
*******************************************************************************/
void SchedulerStop(scheduler_ty *scheduler);

/*******************************************************************************
* Function Description: gets the number of tasks in the scheduler.
			       
* Arguments: pointer to the scheduler

* Return value: number of tasks in the scheduler.
   
* Notes: undefined behavior if NULL is recieved

* Time Complexity: O(n) - n = number of tasks.
*******************************************************************************/
size_t SchedulerSize(const scheduler_ty *scheduler);

/*******************************************************************************
* Function Description: Checks wether the scheduler is empty or not
			       
* Arguments: pointer to the scheduler

* Return value: 1 if scheduler is empty, 0 otherwise
   
* Notes:  undefined behavior if NULL is recieved

* Time Complexity: O(1)
*******************************************************************************/
int SchedulerIsEmpty(const scheduler_ty *scheduler);

/*******************************************************************************
* Function Description: clears the scheduler elements, keeps the scheduler clean
			       
* Arguments: pointer to the scheduler

* Return value: None.
   
* Notes: undefined behavior if NULL is recieved

* Time Complexity: O(n) - n = number of tasks.
*******************************************************************************/
void SchedulerClear(scheduler_ty *scheduler);

#endif /* __SCHEDULER_H__ */
