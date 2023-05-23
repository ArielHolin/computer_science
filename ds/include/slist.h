/*********************************************************************
* Description: Implementation of a singly linked list data structure.
* Name: HRD20
* Date: 10.8.21
* Versions: 1.1
* 1.0 - ready for review
* 2.0 - after review
* 2.1 - 11.08.21 - Rina review
*********************************************************************/
#ifndef __SLIST_H__
#define __SLIST_H__
 
#include <stddef.h> /* size_t */

typedef int bool_ty;

typedef struct slist slist_ty;

typedef struct slist_node slist_node_ty; 
typedef slist_node_ty* slist_iter_ty;


/* action_func_ty is function that operate on data from element using param from user
   return_val : 0 for success, 1 otherwise 
*/
typedef int (*action_func_ty)(void *data, void *param);

/* is_match_func_ty is function that compare data from element using param from user
  return_val : 1 for true, 0 for false
*/
typedef bool_ty (*is_match_func_ty)(const void *data, void *param);

/*******************************************************************************
* Function Description: Create a new linked list.
			       
* Arguments: none.

* Return value: Reference to the slist_ty.
   
* Notes: After usage of the slist, one should always destroy it (with the 
        function SlistDestroy).
        
* Time Complexity:	O(1)
*******************************************************************************/
slist_ty *SlistCreate(void);

/*******************************************************************************
* Function Description: Deallocates memory used for the linked list.
			       
* Arguments: linked list (slist): The linked list that should be destroyed.
   
* Notes: if slist is NULL, no operation is performed.
        
* Time Complexity: O(n)
*******************************************************************************/
void SlistDestroy(slist_ty *slist);

/*******************************************************************************
* Function Description: insert an element to the linked list before iter.
			       
* Arguments: element: The element to insert (becoming a new node).
             iter: iterator to the element in the linked list we insert before.

* Return value: return iterator of inserted element, dummy node (tail) on failure.

* Notes:
        
* Time Complexity: on success  O(1), on fail O(n)
*******************************************************************************/
slist_iter_ty SlistInsert(void *element, slist_iter_ty iter);


/*******************************************************************************
* Function Description: remove the element from the slist.
			       
* Arguments: iter: iterator to the element we need to remove

* Return value: the next of iter.
   
* Notes: undefined behavior if iter is dummy END node.

* Time Complexity: O(1)
*******************************************************************************/
slist_iter_ty SlistRemove(slist_iter_ty iter);

/*******************************************************************************
* Function Description: return if slist is empty.
			       
* Arguments: slist: The slist to check.

* Return value:1 if empty, 0 otherwise.
   
* Notes: undefined behavior if slist is null.
        
* Time Complexity: O(1)
*******************************************************************************/
bool_ty SlistIsEmpty(const slist_ty *slist);

/*******************************************************************************
* Function Description: Return the number of elements in the slist.
			       
* Arguments: slist: The slist to get the size of.

* Return value: The number of elements in the slist.
   
* Notes: undefined behavior if slist is null.
        
* Time Complexity: O(n)
*******************************************************************************/
size_t SlistCount(const slist_ty *slist);

/*******************************************************************************
* Function Description: find iter to the first element which obeys to specific criteria according to "match_func",
                        in the range [from, to) . 
			       
* Arguments: from: start iterator to match the elements.
             to: end iterator to match the elements. (exclusive)
             match_func: function that compare data.
             param: parameter to match.

* Return value: Return iter to the element we search for or "to" if not exist.
   
* Notes:

* AH: Find first iterator in the interval [from, to), for which match_func 
      return TRUE. If iterator not found, return to.
        
* Time Complexity: O(n)	
*******************************************************************************/
slist_iter_ty SlistFind(slist_iter_ty from, slist_iter_ty to, 
                        is_match_func_ty match_func, void *param);

/*******************************************************************************
* Function Description: make action on every node in the linked list until failure, in the range [from, to)
			       
* Arguments: from: start iterator to match the elements.
             to: end iterator to match the elements.
             action_func_ty: function that operate on each element.
             param: parameter to make action with.

* Return value: 0 for success, otherwise return the int we get from action_func.
   
* Notes: if fail in middle of function, stop the for each function.

* AH: Apply action_func on each iterator in the interval [from, to).
      If action_func fail return FALSE, else return TRUE.
        
* Time Complexity: O(n)
*******************************************************************************/
int SlistForEach(slist_iter_ty from, slist_iter_ty to_iter, 
                 action_func_ty action_func, void *param);

/******************************* iter functions *******************************/

/*******************************************************************************
* Function Description: return iterator to first element of linked list.
			       
* Arguments: Slist: linked list.

* Return value: iterator to first element.
   
* Notes: undefined behavior if slist is null.
        
* Time Complexity: O(1)
*******************************************************************************/
slist_iter_ty SlistBegin(const slist_ty *slist);

/*******************************************************************************
* Function Description: return iterator to dummy end element of linked list.
			       
* Arguments: Slist: linked list.

* Return value: iterator to dummy element.
   
* Notes: undefined behavior if slist is null.
        
* Time Complexity: O(1)
*******************************************************************************/
slist_iter_ty SlistEnd(const slist_ty *slist);

/*******************************************************************************
* Function Description: return next iterator linked list.
			       
* Arguments: iterator: iter to current element.

* Return value: iterator to next element.
   
* Notes: undefined behavior when operate on dummy END.
        
* Time Complexity: O(1)
*******************************************************************************/
slist_iter_ty SlistNext(slist_iter_ty iterator);

/*******************************************************************************
* Function Description: return data of given iterator.
			       
* Arguments: iterator: current iterator.

* Return value: data of current iterator.
   
* Notes: undefined behavior if iterator is dummy END.
        
* Time Complexity: O(1)
*******************************************************************************/
void *SlistGetData(slist_iter_ty iterator);

/*******************************************************************************
* Function Description: set data to given iterator.
			       
* Arguments: iterator: current node.
             data: data to set into current node.

* Notes: undefined behavior if iterator is dummy.
        
* Time Complexity: O(1)
*******************************************************************************/
void SlistSetData(slist_iter_ty iterator, void *data);

/*******************************************************************************
* Function Description: check if both iterators are for the same element.
			       
* Arguments: iterator1: first iter to compare.
             iterator2: seconed iter to compare.
             
* Return value: 1 if equal, 0 otherwise.

* Notes:
        
* Time Complexity: O(1)
*******************************************************************************/
bool_ty SlistIsEqual(slist_iter_ty iterator1, slist_iter_ty iterator2);

/*******************************************************************************
* Function Description: Merge both lists by appending src at the end of dst.
			       
* Arguments: dst: destination slist.
             src: source slist.
             
* Return value: Merged slist.

* Notes: After merging, src slist is empty.
        
* Time Complexity: O(1)
*******************************************************************************/
slist_ty *SlistMerge(slist_ty *dst,slist_ty *src);

#endif /* __SLIST_H__ */
