/******************************************************************************
* Description: Interface of Queue.
* Name: HRD20
* Date: 15.8.2021
* Versions: 1.0
* 1.0 - ready for review
*******************************************************************************/
#ifndef __QUEUE_H__
#define __QUEUE_H__
 
#include <stddef.h>  /* size_t */

typedef struct queue queue_ty;
 
/*******************************************************************************
* Function Description: Creating a new queue
			       
* Arguments: 

* Return value: Reference to queue, if fail return NULL.
   
* Notes: 
        
* Time Complexity: O(1)	
*******************************************************************************/
queue_ty *QueueCreate(void);

/*******************************************************************************
* Function Description: Deallocates memory used for queue
			       
* Arguments: Queue

* Return value:  
   
* IMPORTANT: If queue is NULL, behaviour is undefined. 
        
* Time Complexity: O(n) (n = size of queue)	
*******************************************************************************/
void QueueDestroy(queue_ty *queue);

/*******************************************************************************
* Function Description: Peek at first element of queue.
			       
* Arguments: Queue

* Return value: First element of queue 
   
* IMPORTANT: If queue is empty, behaviour is undefined.
        
* Time Complexity: O(1)
*******************************************************************************/
void *QueuePeek(const queue_ty *queue);
/*******************************************************************************
* Function Description: Inserting element to the rear of the queue
			       
* Arguments: Queue to insert and element to insert

* Return value: If sucsses return 0, else fail.   
   
* Notes: 
        
* Time Complexity: O(1) 
*******************************************************************************/
int QueueEnqueue(queue_ty *queue, void *element);

/*******************************************************************************
* Function Description: Removing element from the front of the queue
			       
* Arguments: Queue to remove element from

* Return value:  
   
* Notes: If queue is empty, behaviour is undefined.
        
* Time Complexity: O(1) 
*******************************************************************************/
void QueueDequeue(queue_ty *queue);

/*******************************************************************************
* Function Description: Checks whether queue is empty
			       
* Arguments: Queue

* Return value: If empty return 1, else return 0.  
   
* Notes: 
        
* Time Complexity: O(1) 
*******************************************************************************/
int QueueIsEmpty(const queue_ty *queue);

/*******************************************************************************
* Function Description: number of elements in queue.
			       
* Arguments: Queue

* Return value: size of queue 
   
* Notes:
        
* Time Complexity: O(n) (n = size of queue)
*******************************************************************************/
size_t QueueSize(const queue_ty *queue);

/*******************************************************************************
* Function Description: Appending q_src to end of q_dest.
			       
* Arguments: q_src, q_dest

* Return value: start of q_dest. 
   
* IMPORTANT: If queues are empty, behaviour is undefined. After append, src remains empty
 (size = 0. no free)
        
* Time Complexity: O(n) (n = size of queue)
*******************************************************************************/
queue_ty *QueueAppend(queue_ty *q_dest, queue_ty *q_src);

#endif /* __QUEUE_H__ */
