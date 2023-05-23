/*******************************************************************************
* Description: Implementation of a stack data structure.                       *
               The stack can store any type of element (given as               *
               void *).                                                        *
* Name: HRD20                                                                  *
* Date: 4.8.21                                                                 *
* Versions: 1.0                                                                *
*******************************************************************************/
#ifndef __STACK_H__
#define __STACK_H__
 
#include <stddef.h> /* size_t */

typedef int bool_ty;
typedef struct stack stack_ty;

/*******************************************************************************
* Function Description: Create a new stack with fixed capacity size.
			       
* Arguments: capacity: Max number of elements the stack can store.

* Return value: Reference to the stack.
   
* Notes: After usage of the stack, one should always destroy it (with the 
        function StackDestroy).
        
* Time Complexity:	O(1)
*******************************************************************************/
stack_ty *StackCreate(size_t capacity);

/*******************************************************************************
* Function Description: Deallocates memory used for the stack.
			       
* Arguments: stack: The stack that should be destroyed.
   
* Notes: Destroying a non stack is undefined.
        
* Time Complexity: O(1)
*******************************************************************************/
void StackDestroy(stack_ty *stack);

/*******************************************************************************
* Function Description: Pushes an element to the stack.
			       
* Arguments: stack: The stack to push the element onto.
             element: The element pushed.
   
* Notes: In case of pushing an element to a full stack, behavior is undefined. 
        
* Time Complexity: O(1)
*******************************************************************************/
void StackPush(stack_ty *stack, void *element);


/*******************************************************************************
* Function Description: Pops the last element from the stack.
			       
* Arguments: stack: The stack to pop from.
   
* Notes: In case the stack is empty, behavior is undefined.
         It is advisable to peek before pop.

* Time Complexity: O(1)
*******************************************************************************/
void StackPop(stack_ty *stack);

/*******************************************************************************
* Function Description: Peek at the stack.
			       
* Arguments: stack: The stack to peek at.

* Return value: Reference to the last element pushed onto the stack.
   
* Notes: In case the stack is empty, behavior is undefined.
        
* Time Complexity: O(1)
*******************************************************************************/
void *StackPeek(const stack_ty *stack);

/*******************************************************************************
* Function Description: Return the number of occupied elements in the stack.
			       
* Arguments: stack: The stack to get the size of.

* Return value: The number of occupied elements in the stack.
   
* Notes: 
        
* Time Complexity: O(1)
*******************************************************************************/
size_t StackSize(const stack_ty *stack);

/*******************************************************************************
* Function Description: Return the max number of elements the stack can store. 
			       
* Arguments: The stack to get the capacity of.

* Return value: the max number of elements the stack can store.
   
* Notes: 
        
* Time Complexity: O(1)	
*******************************************************************************/
size_t StackCapacity(const stack_ty *stack);

/*******************************************************************************
* Function Description: Checks if the stack is empty.
			       
* Arguments: stack: The stack to check.

* Return value: 0 for not empty or (!= 0) for empty.
   
* Notes: 
        
* Time Complexity: O(1)
*******************************************************************************/
bool_ty StackIsEmpty(const stack_ty *stack);

#endif /* __STACK_H__ */
