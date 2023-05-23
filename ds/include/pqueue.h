/*******************************************************************************
* Description: Header of priority queue
* Name: HRD20
* Date: 25/08/21
* Versions: 1.0 ready for review
* Versions: 1.1  review
* Versions: 1.2  include functions.h
*******************************************************************************/
#ifndef __PQUEUE_H__
#define __PQUEUE_H__

#include <stddef.h> /* size_t */

#include "functions.h"

typedef struct pqueue pqueue_ty;

/*******************************************************************************
* Function Description: creates an empty priority queue.
			       
* Arguments:  cmp_func: the comparison function

* Return value: pointer to the priority queue. if it fails it returns NULL.
   
* Notes: after use one should always destroy the priority queue (with PQDestroy function).
        
* Time Complexity: O(1)
*******************************************************************************/
pqueue_ty *PQCreate(cmp_func_ty cmp_func);

/*******************************************************************************
* Function Description: Destroys priority queue by deleting its elements and frees 
						its allocated memory.
			       
* Arguments: pqueue: the priority queue to be destroyed.
   
* Notes:  if pqueue is NULL, no operation is preformed.
        
* Time Complexity: O(n)
*******************************************************************************/
void PQDestroy(pqueue_ty *pqueue);

/*******************************************************************************
* Function Description: Creates an element and pushes it in the queue according to
						its priority, if more than one element have the same priority,
						it acts according to LIFO
			       
* Arguments: pqueue: the priority queue to insert into
			 data : the element data to be inserted
   
            return value: 0 for success, 1 for failure
            
* Notes: undefined behavior if queue is NULL.
        
* Time Complexity: O(n)
*******************************************************************************/
int PQEnqueue(pqueue_ty *pqueue, void *data);

/*******************************************************************************
* Function Description: Dequeues the element with the highest priority, and returns
						its data, if there are more that one element with the same
						priority, it behaves as queue and dequeues the 1st element 
						that was enqeueued
			       
* Arguments: pqueue: the priority queue to dequeue from
			returns the data of the dequeued element.
   
* Notes: if there are more that one element with the same
        priority, it behaves as queue and dequeues the 1st element 
        that was enqeueued.

        undefined behavior if queue is NULL or empty.
        
* Time Complexity: O(1)
*******************************************************************************/
void *PQDequeue(pqueue_ty *pqueue);

/*******************************************************************************
* Function Description: returns the data of the highest priority element.

* Arguments:  pqueue: the priority queue to get data from
   			
* Notes: undefined behavior if queue is NULL or empty.
        
* Time Complexity: O(1)
*******************************************************************************/
void *PQPeek(const pqueue_ty *pqueue);

/*******************************************************************************
* Function Description: counts the number of elements in the priority queue.
			       
* Arguments: pqueue: The priority queue to be sized.

* Return value: number of elements in the pqueue.
   
* Notes: undefined behavior if the pqueue is null.
        
* Time Complexity: O(n)
*******************************************************************************/
size_t PQSize(const pqueue_ty *pqueue);

/*******************************************************************************
* Function Description: checks if the priority queue is empty.
			       
* Arguments: pqueue: the priority queue to be checked.

* Return value: 1 if the priority queue is empty, 0 otherwise.
   
* Notes: undefined behavior if the priority queue is null.
        
* Time Complexity: O(1)
*******************************************************************************/
int PQIsEmpty(const pqueue_ty *pqueue);

/*******************************************************************************
* Function Description: removes all the elements from the priority queue, keeps the 
						pqueue clear with no elements
			       
* Arguments: pqueue: the priority queue to be cleared.
   
* Notes: undefined behavior if the pqueue is null.
        
* Time Complexity: O(n)
*******************************************************************************/
void PQClear(pqueue_ty *pqueue);

/*******************************************************************************
* Function Description: deletes the first element from the priority queue that matches
						the given param, using data comparision funtion sent by
						the user (data_cmp_function return 1 if match).
			       
* Arguments: pqueue: the priority queue to remove element from.
			 is_match_func: the function that compares elemet's data and param given 
			 				by the user, if they match the function should return 1.
			 				otherwise it return zero.
			 user_data: the parameter to match elements to (criteria).
			 				
* Return value: if an element is deleted then its data.
				if no element is deleted then NULL is returned.
   
* Notes: undefined behavior if the pqueue is NULL.
        
* Time Complexity: O(n)
*******************************************************************************/
void *PQErease(pqueue_ty *pqueue, is_match_ty is_match_func, void *user_data);

#endif /* __PQUEUE_H__ */
