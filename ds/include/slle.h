/******************************************************************************
* Description: Implementation of linked list exercises.
* Name: HRD20
* Date: 12.8.2021
* Versions: 1.0
* 1.0 - ready for review
*******************************************************************************/
#ifndef __LINKED_LIST_EXERCIESES_H__
#define __LINKED_LIST_EXERCIESES_H__
 
typedef struct node node_t; 

/*******************************************************************************
* Function Description: Reverse the order of a given slist.
			       
* Arguments: list first element (head): The list that should be reversed.

* Return value: list first element after reverse.
   
* Notes: 
        
* Time Complexity:	O(n)
*******************************************************************************/
node_t *Flip(node_t *head); 

/*******************************************************************************
* Tells whether a given slist has loop.
			       
* Arguments: list first element (head):  The list that need to be checked.

* Return value: return 1 for has loop ,0 for no loop.
   
* Notes:
        
* Time Complexity: O(n)
*******************************************************************************/
int HasLoop(const node_t *head);

/*******************************************************************************
* Function Description: Returns a pointer  to a first node mutual to both slist, 
                        if any.
			       
* Arguments:  lists first element (head_1):  the first list.
              lists first element (head_2):  the secound list.

* Return value: return the node where the intersection occurs.

* Notes:
        
* Time Complexity: O(n)
*******************************************************************************/
node_t *FindIntersection(node_t *head_1, node_t *head_2);

#endif /*__LINKED_LIST_EXERCIESES_H__ */
