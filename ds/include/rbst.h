/*********************************************************************
* Description: API for Recursive Binary Sorted Tree Data Structure
* Name: HRD20
* Date: 3/10/2021
* Versions: 1.0 - Upon Approval
*********************************************************************/
#ifndef __RBST_H__
#define __RBST_H__

#include <stddef.h> /* size_t */

typedef struct rbst rbst_ty;

typedef enum traverse_order
{
    PRE_ORDER   = 0,
    IN_ORDER    = 1,
    POST_ORDER  = 2

}trav_ty;

/* cmp_func_ty return value greater than, smaller than or equal to zero
   if new_data > tree_data, new_data < tree_data, new_data == tree_data respectively */
typedef int (*cmp_func_ty)(void *tree_data, void *new_data);

/* operation_ty return 0 for succes, else return int that indicates the type of failure
   for user convenience. */
typedef int (*operation_ty)(void *data, void *param);

/*******************************************************************************
* Function Description: Creates a Recursive Binary Search Tree
			       
* Arguments: cmp_func_ty

* Return value: Pointer to the created RBST 
   
* Notes: If cmp_func is not valid - undefined behavior.
         If RBSTCreate fails, return NULL.
        
* Time Complexity: O(1)
*******************************************************************************/
rbst_ty *RBSTCreate(cmp_func_ty cmp_func);

/*******************************************************************************
* Function Description: Deallocates memory used by RBST
			       
* Arguments: Pointer to rbst.

* Return value: none

* Notes: If rbst == NULL, no operation is performed 
        
* Time Complexity: O(n) n - number of elements
*******************************************************************************/
void RBSTDestroy(rbst_ty *rbst);

/*******************************************************************************
* Function Description: Returns the size of the binary search tree
			       
* Arguments: Pointer to RBST.

* Return value: The number of nodes in the RBST.  
   
* Notes: If rbst is not valid, undefined behavior
        
* Time Complexity: O(n) n - number of elements.
*******************************************************************************/
size_t RBSTSize(const rbst_ty *rbst);

/*******************************************************************************
* Function Description: Returns the height of RBST.
			       
* Arguments: Pointer to RBST.

* Return value: size_t height of the binary sorted tree: number of edges between 
  the root to it's furthest child. 
   
* Notes: If rbst is not valid, undefined behavior.
   
* Time Complexity: O(1) 
*******************************************************************************/
size_t RBSTHeight(const rbst_ty *rbst);

/*******************************************************************************
* Function Description: Determines if rbst is empty.
			       
* Arguments: Pointer to rbst.

* Return value: If empty return 1, else return 0 
   
* Notes: If rbst is not valid, undefined behavior
        
* Time Complexity: O(1)
*******************************************************************************/
int RBSTIsEmpty(const rbst_ty *rbst);

/*******************************************************************************
* Function Description: Insert a new node into the appropriate location at the RBST.
			       
* Arguments: rbst - RBST to Insert.
             data - Data for the inserted node.

* Return value: int status of the insertion: 0 for SUCCESS. 
   
* Notes: If rbst or data are not valid, undefined behavior.
   
* Time Complexity: O(log(n)) n - number of elements. 
*******************************************************************************/
int RBSTInsert(rbst_ty *rbst, void *new_data);

/*******************************************************************************
* Function Description: Removes an element from RBST based on compare function.
			       
* Arguments: rbst - RBST to remove from.
             data - Data to compare using the compare function.
* Return value:  none
   
* Notes: If RBST or data are not valid, undefined behavior.
         If the data was not found, no operation is performed.
   
* Time Complexity: O(log(n)) n - number of elements. 
*******************************************************************************/
void RBSTRemove(rbst_ty *rbst, void *data);

/*******************************************************************************
* Function Description: Returns the data that was found. 
                        If the data was not found - returns NULL;
			       
* Arguments: rbst - RBST to search in.
             data to search.

* Return value: If found - returns the data. else, returns NULL. 
   
* Notes: undefined behavior if rbst or data are not valid.
        
* Time Complexity: O(log(n)) n - number of elements.	
*******************************************************************************/
void *RBSTFind(const rbst_ty *rbst, void *data);

/*******************************************************************************
* Function Description: Perfroms op on each element of the iterator interval.
			       
* Arguments: rbst - RBST to traverse.
             op - operation function.
             param - param of the operation function, for user convenience.

* Return value: 0 for SUCCESS, otherwise returns int that was returned from op function 
   
* Notes: - If op fails before traversing the entire RBST, function stops.
         - It is user responsibility that op function doesn't destruct
           the structure of the rbst.

* Time Complexity: O(n) n - number of elements.	
*******************************************************************************/
int RBSTForEach(rbst_ty *rbst, operation_ty op, void *param, trav_ty trav_order);

#endif /* __RBST_H__ */
