/*******************************************************************************
*  Stack.c                                                                     *
*  Author: Ariel                                                               *
*  Reviewer:                                                                   *
*******************************************************************************/
#include <stddef.h> /* size_t       */
#include <stdlib.h> /* malloc, free */
#include <assert.h> /* assert       */

#include "../include/stack.h"

#define ISFULL(stack) (stack->top >= stack->capacity)

struct stack 
{
	size_t top;
	size_t capacity;
	void **data;
};

/********* StackCreate ********************************************************/

stack_ty *StackCreate(size_t capacity)
{
	stack_ty *new_stack = (stack_ty *)malloc(sizeof(stack_ty));
	
	if ( !new_stack )
	{
		return NULL;
	}
	
	new_stack->data = (void **)malloc(capacity * sizeof(void *));
	
	if ( !new_stack->data )
	{
		free(new_stack);
		new_stack = NULL;
		
		return NULL;
	}
	
	*new_stack->data = NULL; 
	new_stack->capacity = capacity;
	new_stack->top = 0;
	
	return new_stack;
}

/********** StackDestroy ******************************************************/

void StackDestroy(stack_ty *stack)
{
	assert(stack);
	
	free(stack->data);
	stack->data = NULL;
	
	free(stack);
	stack = NULL;
}

/********* StackPush **********************************************************/

void StackPush(stack_ty *stack, void *element)
{
	assert(stack);
	assert(element);
	assert( !ISFULL(stack) );
	
	stack->data[stack->top] = element;
	++stack->top;
}

/******** StackPop ************************************************************/

void StackPop(stack_ty *stack)
{
	assert(stack);
	assert(!StackIsEmpty(stack));
	
	--stack->top;
}

/******* StackPeek ************************************************************/

void *StackPeek(const stack_ty *stack)
{
	assert(stack);
	assert(!StackIsEmpty(stack));
	
	return (stack->data[stack->top - 1]);
}

/******** StackPeek ***********************************************************/

size_t StackSize(const stack_ty *stack)
{
	assert(stack);
	
	return (stack->top);
}

/******** StackCapacity *******************************************************/

size_t StackCapacity(const stack_ty *stack)
{
	assert(stack);
	
	return (stack->capacity);
}

/******* StackIsEmpty *********************************************************/

bool_ty StackIsEmpty(const stack_ty *stack)
{
	assert(stack);
	
	return (0 == stack->top);
}




