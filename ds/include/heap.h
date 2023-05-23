/*********************************************************************
* Description: API for Heap data structure
* Name: HRD20
* Date: 24/10/2021
* Versions: 1.0 - 
*********************************************************************/
#ifndef __HEAP_H__
#define __HEAP_H__

#include <stddef.h>

/* cmp_func_ty return value greater than, smaller than or equal to zero
   if heap_data > new_data , heap_data < new_data, new_data == heap_data respectively */
typedef int (*heap_cmp_func_ty)(const void *heap_data,const void *new_data);

/* is_match_func_ty return if the data to remove is found.
   return 1 data is found, 0 otherwise.*/
typedef int (*is_match_func_ty)(const void *data, const void *param);

typedef struct heap heap_ty;

/*******************************************************************************
* Function Description: creates an empty heap.
			       
* Arguments:    cmp_func: the comparison function.
                capacity: the initial capacity.

* Return value: pointer to the new heap. if it fails it returns NULL.
   
* Notes:
        
* Time Complexity: O(1)
*******************************************************************************/
heap_ty *HeapCreate(heap_cmp_func_ty cmp_func, size_t capacity);

/*******************************************************************************
* Function Description: Destroys the heap by free its allocated memory.
			       
* Arguments: heap: the heap to be destroyed.
   
* Notes:  if heap is NULL, no operation is preformed.
        
* Time Complexity: O(1)
*******************************************************************************/
void HeapDestroy(heap_ty *heap);

/*******************************************************************************
* Function Description: pushes an element it to the heap according to
						its value, and the cmp_func policy.
			       
* Arguments: heap: the heap to insert into
			 data : the element data to be inserted
   
* return value: 0 for success, 1 for failure
            
* Notes: undefined behavior if heap is NULL.
        
* Time Complexity:  O(n), amortize O(log(n))
*******************************************************************************/
int HeapPush(heap_ty *heap, void *data);

/*******************************************************************************
* Function Description: pop the element with the highest priority.
			       
* Arguments:    heap: the heap pop from.

                
* return value: 0 for success, 1 for failure.

* Notes: undefined behavior if heap is NULL or empty.

* Time Complexity: O(n), amortize O(log(n))
*******************************************************************************/
int HeapPop(heap_ty *heap);

/*******************************************************************************
* Function Description: peek to the highest priority, and returns the value of 
                        the elements.
			       
* Arguments: heap: the heap peek from.

* Notes: undefined behavior if heap is NULL or empty.
        
* Time Complexity: O(1)
*******************************************************************************/
void *HeapPeek(const heap_ty *heap);

/*******************************************************************************
* Function Description: returnes the number of elements in the heap data structure.
			       
* Arguments: heap: the heap to check for size.

* Return value: number of elements in the heap.
   
* Notes: undefined behavior if the heap is null.
        
* Time Complexity: O(1)
*******************************************************************************/
size_t HeapSize(const heap_ty *heap);

/*******************************************************************************
* Function Description: checks if the heap data structure is empty.
			       
* Arguments: heap: the heap data structure to be checked.

* Return value: 1 if the heap data structure is empty, 0 otherwise.
   
* Notes: undefined behavior if the heap is null.
        
* Time Complexity: O(1)
*******************************************************************************/
int HeapIsEmpty(const heap_ty *heap);

/*******************************************************************************
* Function Description: deletes the first element from the heap data structure
                        that matches the given data, using data comparision funtion
                        sent by the user (heap_cmp_function return 1 if match).
			       
* Arguments: heap:      the heap data structure to remove element from.
			 param:     the parameter to match elements to (criteria).
             match_func: the function that determine policy of the search.
			 				
* Return value: if an element is deleted then its returns the element data.
				if no element is deleted then NULL is returned.
   
* Notes: undefined behavior if the heap is NULL.
        
* Time Complexity: O(n)
*******************************************************************************/
void *HeapRemove(heap_ty *heap, void *param, is_match_func_ty match_func);


#endif /* __HEAP_H__ */
