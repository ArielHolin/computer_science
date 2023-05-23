/*********************************************************************
* Description: Header of Task.h for inner use
* Name: HRD20
* Date: 29.8.2021
* Versions: 1.0 before class review
            1.1 after class review
            1.2 after Yishai suggestion to name different typedefs for 
                functions
            1.3 header compiles
*********************************************************************/
#ifndef __TASK_H__
#define __TASK_H__
 
#include <stddef.h> /* size_t */
#include <time.h>   /* time_t */

#include "uid.h"

typedef struct task task_ty;

/*
task_func_ty is the type of the functions the user of the 
scheduler want to schedule for execution.

return value: status of execution.
				0 - success - completed
				1 - not completed
				2 - error

argument: param - for user convenince.
*/

typedef int (*task_func_ty)(void *param);

/*******************************************************************************
* Function Description: Creates a new task instance. 
			       
* Arguments: interval: Time between function execution.
             function: User function to execute inside the task.
             param: Extra parameter for user convenience.

* Return value:  Pointer to task instance.
   
* Notes: If TaskCreate fails it returns NULL.
        
* Time Complexity:	O(1)
*******************************************************************************/
task_ty *TaskCreate(time_t interval, task_func_ty function, void *param);
/*******************************************************************************
* Function Description: Deallocates memory used for the Task. 
                   
* Arguments: task: the task instance to destroy.

* Return value:  None.
   
* Notes: If task is NULL, no operation is performed.
        
* Time Complexity:  O(1)
*******************************************************************************/
void TaskDestroy(task_ty *task);
/*******************************************************************************
* Function Description: get the unique ID of the current task.
                   
* Arguments: task: the task we want to get his UID.

* Return value: UID of the current task.
   
* Notes: Undefined Behavior if task is NULL.
        
* Time Complexity:  O(1)
*******************************************************************************/
uid_ty TaskGetUID(const task_ty *task);
/*******************************************************************************
* Function Description: Get the starting time of the current task.
                   
* Arguments: task: the task we want to get his current time-to-run.

* Return value:  The starting time of the current task.
   
* Notes: Undefined Behavior if task is NULL.
        
* Time Complexity:  O(1) 
*******************************************************************************/
time_t TaskGetTimeToRun(const task_ty *task);

/*******************************************************************************
* Function Description: Updates The starting time of the current task.
                   
* Arguments: task: the task we want to update his time-to-run.

* Return value:  None.
   
* Notes: Undefined Behavior if task is NULL.
        
* Time Complexity:  O(1) 
*******************************************************************************/
void TaskUpdateTimeToRun(task_ty *task);

/*******************************************************************************
* Function Description: exectues the function of the current task.
                   
* Arguments: task: the task we want to executes his function.

* Return value:  status_of_execution.
*                
* Notes: Undefined Behavior if task is NULL. 
        
* Time Complexity:  O(1)
*******************************************************************************/
int TaskRun(const task_ty *task);

#endif /* __TASK_H__ */
