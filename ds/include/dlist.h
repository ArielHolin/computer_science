/*******************************************************************************
* Description: Header of doubly linked list data structure.
* Name: HRD20
* Date: 18/08/21
* Versions: 1.0 ready for review
*           1.1 after adjustments
*           1.2 after review
*           2.0 header ready
*******************************************************************************/

#ifndef __DLIST_H__
#define __DLIST_H__

#include <stddef.h> /* size_t */

/******************************************************************************/

typedef struct dlist_node *dlist_iter_ty;
typedef struct dlist dlist_ty;

/* is_match_func_ty is a function that compares the elements to param, which is 
set by the user. the return value is 1 for true, 0 for false */
typedef int (*is_match_func_ty)(const void *data, void *param);

/* action_func_ty is a function that applies an operation on chosen elements 
the return value is 0 for success, 1 otherwise  */
typedef int (*operation_ty)(void *data, void *param);

/*******************************************************************************
* Function Description: creates an empty doubly linked list.
			       
* Arguments: -

* Return value: reference to the dlist_ty.
   
* Notes: after usage one should always destroy it (with DListDestroy function).
        
* Time Complexity: O(1)
*******************************************************************************/
dlist_ty *DListCreate(void);

/*******************************************************************************
* Function Description: deallocates memory that is used for the doubly linked 
  list and all the elements inside it.
			       
* Arguments: linked list (dlist): The linked list that should be destroyed.
   
* Notes: if dlist is NULL, no operation is performed.
        
* Time Complexity: O(n)
*******************************************************************************/
void DListDestroy(dlist_ty *list);

/*******************************************************************************
* Function Description: creates and inserts a new element to the doubly 
  linked list before the iterator.
			       
* Arguments: element: The element to insert
             iter: iterator to the element in the linked list.

* Return value: returns an iterator to the inserted element. end dummy node is 
  returned on failure.

* Notes: inserts a new element to the linked list before the iterator
        
* Time Complexity: on success  O(1), on fail O(n)
*******************************************************************************/
dlist_iter_ty DListInsert(dlist_iter_ty iter, void *element);

/*******************************************************************************
* Function Description: creates and inserts a new element to the front of the
  doubly linked list.
			       
* Arguments: element: The element to insert
             list: the list to which we want to insert the element 

* Return value: returns an iterator to the inserted element. end dummy node is 
  returned on failure.

* Notes: -
        
* Time Complexity:  O(1)
*******************************************************************************/
dlist_iter_ty DListPushFront(dlist_ty *dlist, void *element);

/*******************************************************************************
* Function Description: creates and inserts a new element to the back of the
  doubly linked list.
			       
* Arguments: element: The element to insert
             list: the list to which we want to insert the element 

* Return value: returns an iterator to the inserted element. end dummy node is 
  returned on failure.

* Notes: -
  
* Time Complexity:  O(1)
*******************************************************************************/
dlist_iter_ty DListPushBack(dlist_ty *dlist, void *element);

/*******************************************************************************
* Function Description: removes an element from the dlist.
			       
* Arguments: iter: iterator to the element that we want to remove

* Return value: the next element to which the iterator points.
   
* Notes: undefined behavior if iter points to the one of the dummies.

* Time Complexity: O(1)
*******************************************************************************/
dlist_iter_ty DListRemove(dlist_iter_ty iter_to_remove);

/*******************************************************************************
* Function Description: removes an element from the front of the dlist.
			       
* Arguments: list: the list from which we want to remove the first element 

* Return value: the element that the user popped.
   
* Notes: undefined behavior to pop from an empty list.

* Time Complexity: O(1)
*******************************************************************************/
void *DListPopFront(dlist_ty *dlist);

/*******************************************************************************
* Function Description: removes an element from the back of the dlist.
			       
* Arguments: list: the list from which we want to remove the first element 

* Return value: the element that the user popped.
   
* Notes: undefined behavior to pop from an empty list.

* Time Complexity: O(1)
*******************************************************************************/
void *DListPopBack(dlist_ty *dlist);

/*******************************************************************************
* Function Description: checks if the list is empty.
			       
* Arguments: dlist: to check if it's empty.

* Return value:1 if the list is empty, 0 otherwise.
   
* Notes: undefined behavior if the list is null.
        
* Time Complexity: O(1)
*******************************************************************************/
int DListIsEmpty(const dlist_ty *dlist);

/*******************************************************************************
* Function Description: counts the number of elements in the list.
			       
* Arguments: dlist: The dlist to get the number of values in it.

* Return value: The number of elements in the dlist.
   
* Notes: undefined behavior if dlist is null.
        
* Time Complexity: O(n)
*******************************************************************************/
size_t DListSize(const dlist_ty *dlist);

/*******************************************************************************
* Function Description:  find iter to the first element which obeys to specific criteria according to "match_func",
                         in the range [from, to) . 
			       
* Arguments: from: where the iterator starts to search for the element.
             to: where the iterator ends to search for the element.(exclusive)
             match_func: function that compares the data in an element to the
             param set by the user.
             param: parameter the user wants to compare the data with.

* Return value: Return iterator to the element we search for or "to" if not 
  exist.
   
* Notes: - 
        
* Time Complexity: O(n)	
*******************************************************************************/
dlist_iter_ty DListFind(dlist_iter_ty from, dlist_iter_ty to, 
                        is_match_func_ty match, void *param);

/*******************************************************************************
* Function Description: creates a list with all the elements that satisfy the 
  requirments of the match function and return a pointer to the list of those
  elements.
  			       
* Arguments: from: start iterator to match the elements.
             to: end iterator to match the elements.
             match_func: function that compares the data in an element to the
             param set by the user.
             param: parameter the user wants to compare the data with.
             output_dlist: a pointer to a list that contains the elements that
             where found by the function.  

* Return value: 0 for success, otherwise 1 for failure of allocate memory in insert to output_dlist
   
* Notes: return an empty list if non of the requested matches was found. 
         the user MUST allocate and deallocate memory for the output list. 
        
* Time Complexity: O(n)
*******************************************************************************/
int DListMultiFind(dlist_iter_ty from, dlist_iter_ty to, 
	               is_match_func_ty match, void *param, dlist_ty *output_dlist);

/*******************************************************************************
* Function Description: make an action in the range of [from, to), on every node 
                        in the linked list until failure
			       
* Arguments: from: start iterator to match the elements.
             to: end iterator to match the elements.
             action_func_ty: function that operates on each element.
             param: parameter to make action with.

* Return value: 0 for success, otherwise return the int we get from action_func.
   
* Notes: if fail in middle of function, stop the for each function.
        
* Time Complexity: O(n)
*******************************************************************************/
int DListForEach(dlist_iter_ty from, dlist_iter_ty to, operation_ty op, 
                 void *param);

/*******************************************************************************
* Function Description: appends the list of nodes that are in the range of 
  [from, to) and attaches the appended list to the location of the dest 
  iterator (after dest iterator).
			       
* Arguments: from: start iterator to match the elements.
             to: end iterator to match the elements.
             dest: iterator to where to attach the appended list.

* Return value: returns the first element added to the dest iterator.
   
* Notes: -
        
* Time Complexity: O(1)
*******************************************************************************/
dlist_iter_ty DListSplice(dlist_iter_ty from, dlist_iter_ty to, 
						  dlist_iter_ty dest);

/******************************************************************************/

/***************************** iterator functions *****************************/

/*******************************************************************************
* Function Description: returns an iterator to first element of the linked list.
			       
* Arguments: Dlist: linked list.

* Return value: iterator to the first element.
   
* Notes: undefined behavior if slist is null. return the end dummy of the list 
if it is empty
        
* Time Complexity: O(1)
*******************************************************************************/
dlist_iter_ty DListBegin(const dlist_ty *dlist);

/*******************************************************************************
* Function Description: returns an iterator to end dummy of linked list.
			       
* Arguments: Dlist: linked list.

* Return value: iterator to end dummy element.
   
* Notes: undefined behavior if slist is null.
        
* Time Complexity: O(1)
*******************************************************************************/
dlist_iter_ty DListEnd(const dlist_ty *dlist);

/*******************************************************************************
* Function Description: returns the next iterator to the linked list.
			       
* Arguments: iterator: iter to current element.

* Return value: iterator to next element.
   
* Notes: undefined behavior when operate on dummy END.
        
* Time Complexity: O(1)
*******************************************************************************/
dlist_iter_ty DListNext(const dlist_iter_ty iter);

/*******************************************************************************
* Function Description: returns the prev iterator to the linked list.
			       
* Arguments: iterator: iter to current element.

* Return value: iterator to prev element.
   
* Notes: undefined behavior when operate on dummy head.
        
* Time Complexity: O(1)
*******************************************************************************/
dlist_iter_ty DListPrev(const dlist_iter_ty iter);

/*******************************************************************************
* Function Description: returns the data of a given iterator.
			       
* Arguments: iterator: current iterator.

* Return value: data of current iterator.
   
* Notes: undefined behavior if iterator is end dummy.
        
* Time Complexity: O(1)
*******************************************************************************/
void *DListGetData(dlist_iter_ty iter);

/*******************************************************************************
* Function Description: updates the data of a given element.
			       
* Arguments: iterator: current node.
             data: data to set into current node.

* Notes: undefined behavior if iterator is dummy.
        
* Time Complexity: O(1)
*******************************************************************************/
void DListSetData(dlist_iter_ty iter, void *data);

/*******************************************************************************
* Function Description: check if the iterators are equal.
			       
* Arguments: iter1: first iterator to compare.
             iter2: seconed iterator to compare.
             
* Return value: 1 if equal, 0 otherwise.

* Notes: -
        
* Time Complexity: O(1)
*******************************************************************************/
int DListIsEqual(const dlist_iter_ty iter1, const dlist_iter_ty iter2);

/******************************************************************************/

#endif /* __DLIST_H__ */
