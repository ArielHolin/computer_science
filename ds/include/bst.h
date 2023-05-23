/*********************************************************************
* Description: API for Binary Search Tree Data Structure
* Name: HRD20
* Date: 3/10/2021
* Versions: 1.0 - Upon Approval
*           1.1 - every function approved, except foreach
*           1.2 - updating cmp_func_ty Description
*           2.0 - approved
*********************************************************************/
#ifndef __BST_H__
#define __BST_H__

#include <stddef.h> /* size_t */

typedef struct bst bst_ty;
typedef struct node node_ty;
typedef node_ty *bst_iter_ty;

/* cmp_func_ty return value greater than, smaller than or equal to zero
   if new_data > tree_data, new_data < tree_data, new_data == tree_data respectively */
typedef int (*cmp_func_ty)(void *tree_data, void *new_data);

/* operation_ty return 0 for succes, else return int that indicates the type of failure
   for user convenience. */
typedef int (*operation_ty)(void *data, void *param);
/*******************************************************************************
* Function Description: Creates a Binary Search Tree
			       
* Arguments: cmp_func_ty

* Return value: Pointer to the created BST 
   
* Notes: If cmp_func is not valid - undefined behavior.
         If BSTCreate fails, return NULL.
        
* Time Complexity: O(1)
*******************************************************************************/
bst_ty *BSTCreate(cmp_func_ty cmp_func);

/*******************************************************************************
* Function Description: Deallocates memory used by BST
			       
* Arguments: Pointer to bst.

* Return value:  
   
* Notes: If bst == NULL, no operation is performed.
        
* Time Complexity: O(n) n - number of elements
*******************************************************************************/
void BSTDestroy(bst_ty *bst);

/*******************************************************************************
* Function Description: Returns the size of the binary search tree
			       
* Arguments: Pointer to BST.

* Return value: The number of nodes in the BST.  
   
* Notes: If bst is not valid, undefined behavior
        
* Time Complexity: O(nlog(n)) n - number of elements.
*******************************************************************************/
size_t BSTSize(const bst_ty *bst);

/*******************************************************************************
* Function Description: Determines if bst is empty.
			       
* Arguments: Pointer to bst.

* Return value: If empty return 1, else return 0 
   
* Notes: If bst is not valid, undefined behavior
        
* Time Complexity: O(1)
*******************************************************************************/
int BSTIsEmpty(const bst_ty *bst);

/*******************************************************************************
* Function Description: Insert a new node into the appropriate location at the BST.
			       
* Arguments: bst - BST to Insert.
             data - Data for the inserted node.

* Return value: Pointer to the inserted node. 
   
* Notes: If function fails to insert, return end of the BST. 
         If bst or data are not valid, undefined behavior.
   
* Time Complexity: O(n) n - number of elements. 
*******************************************************************************/
bst_iter_ty BSTInsert(bst_ty *bst, void *new_data);

/*******************************************************************************
* Function Description: Removes an iterator from the appropriate location at the BST.
			       
* Arguments: iter - the iterator to remove.

* Return value:  
   
* Notes: If the iterator is not valid, undefined behavior.
         If BST is empty, undefined behavior.
   
* Time Complexity: O(n) n - number of elements. 
*******************************************************************************/
void BSTRemove(bst_iter_ty iter);

/*******************************************************************************
* Function Description: Return iterator that holds the smallest value of BST.
			       
* Arguments: Pointer to BST.

* Return value: iterator holding the smallest value of BST.
   
* Notes: If bst is not valid, undefined behavior.
         If bst is empty, return end not valid iterator.
        
* Time Complexity:	O(n) n - number of elements.
*******************************************************************************/
bst_iter_ty BSTBegin(const bst_ty *bst);

/*******************************************************************************
* Function Description: Return end not valid iterator.
			       
* Arguments: Pointer to BST.

* Return value: end dummy iterator.
   
* Notes: If bst is not valid, undefined behavior.
         If bst is empty, return end not valid iterator.
        
* Time Complexity:	O(1) n - number of elements.
*******************************************************************************/
bst_iter_ty BSTEnd(const bst_ty *bst);

/*******************************************************************************
* Function Description: Returns iterator to next smallest value.
			       
* Arguments: iterator to search for previous value.

* Return value: Iterator to next smallest value. 
   
* Notes: If iter is not valid, undefined behavior.
         If iterator holds the begin value, return end not valid iterator.
        
* Time Complexity:	O(n) n - number of elements.
*******************************************************************************/
bst_iter_ty BSTPrev(bst_iter_ty iter);

/*******************************************************************************
* Function Description: Returns iterator to next greater value.
			       
* Arguments: iterator to search for next value.

* Return value: Iterator to next greater value. 
   
* Notes: If iter is not valid, undefined behavior.
         If iterator holds the greatest value, return end not valid iterator.
        
* Time Complexity:	O(n) n - number of elements.
*******************************************************************************/
bst_iter_ty BSTNext(bst_iter_ty iter);

/*******************************************************************************
* Function Description: Determines if two iterators are identical.
			       
* Arguments: iter1, iter2 - The iterators to compare.

* Return value: If iterators are equal return 1, else return 0. 
   
* Notes: 
        
* Time Complexity: O(1)	
*******************************************************************************/
int BSTIterIsEqual(const bst_iter_ty iter1, const bst_iter_ty iter2);

/*******************************************************************************
* Function Description: Returns data of current iterator.
			       
* Arguments: bst iterator.

* Return value: value of current iterator. 
   
* Notes: 
        
* Time Complexity: O(1)	
*******************************************************************************/
void *BSTGetData(const bst_iter_ty iter);

/*******************************************************************************
* Function Description: Returns iterator that holds the same value as data, if found.
			       
* Arguments: Pointer to bst.
             data to search.

* Return value: If found - return iterator that holds data,
                else, return end not valid iterator. 
   
* Notes: undefined behavior if bst is not valid.
        
* Time Complexity: O(n) n - number of elements.	
*******************************************************************************/
bst_iter_ty BSTFind(const bst_ty *bst, void *data);

/*******************************************************************************
* Function Description: Perfroms op on each element of the iterator interval [from, to).
			       
* Arguments: from - start iterator.
             to - end iterator.
             op - operation function.
             param - param of the operation function, for user convenience.

* Return value: 0 for success, otherwise return int that was returned from op function 
   
* Notes: - If op fails before reaching to, function stops.
         - It is user responsibility to make sure that the data of from
           iterator is smaller than the data of to iterator.
         - It is user responsibility that op function doesn't destruct
           the structure of the bst.

* Time Complexity: O(n) n - number of elements.	
*******************************************************************************/
int BSTForEach(bst_iter_ty from, bst_iter_ty to, operation_ty op, void *param);

#endif /* __BST_H__ */
