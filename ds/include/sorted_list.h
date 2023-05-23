/*******************************************************************************
* Description: Header of sorted linked list data structure.  
* Name: HRD20
* Date: 22/08/21
* Versions: 1.0 ready for review
*           1.1 after adjustments
*           1.2 after review
*           2.0 header ready
*******************************************************************************/

#ifndef __SORTED_LIST_H__
#define __SORTED_LIST_H__

#include <stddef.h> /* size_t */

#include "dlist.h"
#include "functions.h"

typedef struct sorted_list sorted_list_ty;

typedef struct sorted_list_iter sorted_list_iter_ty;

/*******************************************************************************
* Function Description: creates an empty sorted list.
			       
* Arguments:  cmp_func: function which provides the criteria by which the
			  list will be sorted.

* Return value: reference to the list.
   
* Notes: after usage one should always destroy it (with SortedListDestroy function).
        
* Time Complexity: O(1)
*******************************************************************************/
sorted_list_ty *SortedListCreate(cmp_func_ty cmp_func);

/*******************************************************************************
* Function Description: deallocates memory used for the sorted list.
			       
* Arguments: sorted_list_ty (list) to be destroyed.
   
* Notes: if list is NULL, no operation is performed.
        
* Time Complexity: O(n)
*******************************************************************************/
void SortedListDestroy(sorted_list_ty *list);

/*******************************************************************************
* Function Description: creates and inserts a new element to the sorted
                        list at the correct position.
			       
* Arguments: list : list to insert to.
             new_data: The data for the element to insert
             
* Return value: returns an iterator to the inserted element. end dummy node is 
                returned on failure.

* Notes: Inserts "new_data" to the sorted linked list according to default 
         sorting criteria. On failure returns end dummy.
        
* Time Complexity: O(n). n = number of elements.
*******************************************************************************/
sorted_list_iter_ty SortedListInsert(sorted_list_ty *list, void *new_data);

/*******************************************************************************
* Function Description: removes an element from the list.
			       
* Arguments: iter_to_remove: iterator to the element to be removed.

* Return value: the next element in the list.
   
* Notes: undefined behavior if iter points to one of the dummies.

* Time Complexity: O(1)
*******************************************************************************/
sorted_list_iter_ty SortedListRemove(sorted_list_iter_ty iter_to_remove);

/*******************************************************************************
* Function Description: removes an element from the front of the list.
			       
* Arguments: list: the list from which we want to remove the first element. 

* Return value: the popped element's data.
   
* Notes: undefined behavior if used on an empty list.

* Time Complexity: O(1)
*******************************************************************************/
void *SortedListPopFront(sorted_list_ty *list);
/*******************************************************************************
* Function Description: removes an element from the back of the list.
			       
* Arguments: list: the list from which we want to remove the last element. 

* Return value: the popped element's data.
   
* Notes: undefined behavior if used on an empty list.

* Time Complexity: O(1)
*******************************************************************************/
void *SortedListPopBack(sorted_list_ty *list);

/*******************************************************************************
* Function Description: checks if the list is empty.
			       
* Arguments: list: the list to be checked.

* Return value: 1 if the list is empty, 0 otherwise.
   
* Notes: undefined behavior if the list is null.
        
* Time Complexity: O(1)
*******************************************************************************/
int SortedListIsEmpty(const sorted_list_ty *list);

/*******************************************************************************
* Function Description: counts the number of elements in the list.
			       
* Arguments: list: The list to be sized.

* Return value: number of elements in the list.
   
* Notes: undefined behavior if the list is null.
        
* Time Complexity: O(n)
*******************************************************************************/
size_t SortedListSize(const sorted_list_ty *list);

/*******************************************************************************
* Function Description: finds the first element which obeys a specific
                        criteria set by the default compare function
                        in the given range [from, to) . 
			       
* Arguments: list: sorted list.
             from: iterator to start the search.
             to: end point iterator.
             to_find: data the user wishes to find.

* Return value: iterator to the first element which meets the search requirements 
                or "to" iterator if no element in range meets the aformantioned 
                criteria. 
  
* Notes: Undefined behavior on NULL list. 
        
* Time Complexity: O(n)	
*******************************************************************************/
sorted_list_iter_ty SortedListFind(sorted_list_ty *list, sorted_list_iter_ty from,
                                   sorted_list_iter_ty to, const void *to_find);

/*******************************************************************************
* Function Description: finds the first element which obeys a specific
                        criteria set by the compare function set by the user
                        in the given range [from, to) . 
			       
* Arguments: cmp_func: compare function to find to iter we want.
             from: iterator to start the search.
             to: end point iterator.
             to_find: data the user wishes to find.

* Return value: iterator to the first element which meets the search requirements 
                or "to" iterator if no element in range meets the aformantioned 
                criteria 
  
* Notes: Undefined behavior on NULL list. 
        
* Time Complexity: O(n)	
*******************************************************************************/
sorted_list_iter_ty SortedListFindIf(cmp_func_ty cmp_func, sorted_list_iter_ty from, 
                     sorted_list_iter_ty to, const void *to_find);

/*******************************************************************************
* Function Description: make an action in the range of [from, to), on every node 
                        in the sorted list.
			       
* Arguments: from: start iterator to match the elements.
             to: end iterator to match the elements.
             action_func_ty: function that operates on each element.
             param: parameter to make action with.

* Return value: 0 for success, otherwise return the int we get from action_func.
   
* Notes: if fail in middle of function, stop the for each function.
         user is responsible to maintain sorted list order.
        
* Time Complexity: O(n)
*******************************************************************************/
int SortedListForEach(sorted_list_iter_ty from, sorted_list_iter_ty to, 
                      operations_ty op, void *param);

/*******************************************************************************
* Function Description: Merges two sorted lists.
			       
* Arguments: dest_list: sorted list to be merged into.
             src_list: sorted list to merge.

* Return value:
   
* Notes: Undefined behavior on NULL lists.
         Both dest_list and src_list are sorted according to the same cmp_func.
         Otherwise, undefined behavior.
        
* Time Complexity: O(n + m) n = number of elements in dest_list.
                            m = number of elements in src_list.
*******************************************************************************/
void SortedListMerge(sorted_list_ty *dest_list, sorted_list_ty *src_list);

/******************************************************************************/



/***************************** iterator functions *****************************/

/*******************************************************************************
* Function Description: returns an iterator to first element of the sorted list.
			       
* Arguments: list: sorted list.

* Return value: iterator to the first element.
   
* Notes: undefined behavior if slist is null. return the end dummy of the list 
if it is empty
        
* Time Complexity: O(1)
*******************************************************************************/
sorted_list_iter_ty SortedListBegin(const sorted_list_ty *list);

/*******************************************************************************
* Function Description: returns an iterator to end dummy of list.
			       
* Arguments: list: sorted list.

* Return value: iterator to end dummy element.
   
* Notes: undefined behavior if list is null.
        
* Time Complexity: O(1)
*******************************************************************************/
sorted_list_iter_ty SortedListEnd(const sorted_list_ty *list);

/*******************************************************************************
* Function Description: returns the next iterator of the list.
			       
* Arguments: iterator: iter to current element.

* Return value: iterator to next element.
   
* Notes: undefined behavior when operate on dummy tail.
        
* Time Complexity: O(1)
*******************************************************************************/
sorted_list_iter_ty SortedListNext(const sorted_list_iter_ty iter);

/*******************************************************************************
* Function Description: returns the prev iterator of the list.
			       
* Arguments: iterator: iter to current element.

* Return value: iterator to prev element.
   
* Notes: undefined behavior when operate on dummy.
        
* Time Complexity: O(1)
*******************************************************************************/
sorted_list_iter_ty SortedListPrev(const sorted_list_iter_ty iter);

/*******************************************************************************
* Function Description: returns the data of a given iterator.
			       
* Arguments: iterator: current iterator.

* Return value: data of current iterator.
   
* Notes: undefined behavior if iterator is dummy.
        
* Time Complexity: O(1)
*******************************************************************************/
void *SortedListGetData(sorted_list_iter_ty iter);

/*******************************************************************************
* Function Description: check if the iterators are equal.
			       
* Arguments: iter1: first iterator to compare.
             iter2: seconed iterator to compare.
             
* Return value: 1 if equal, 0 otherwise.

* Notes: -
        
* Time Complexity: O(1)
*******************************************************************************/
int SortedListIsEqual(const sorted_list_iter_ty iter1, 
                      const sorted_list_iter_ty iter2);

/******************************************************************************/

#ifndef NDEBUG
#define DEBUG_ONLY(exp) exp
#else
#define DEBUG_ONLY(exp) 
#endif

struct sorted_list_iter
{
    dlist_iter_ty dlist_iter;
    DEBUG_ONLY(sorted_list_ty *list;)
};

#endif /* __SORTED_DLIST_H__ */
