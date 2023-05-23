/*******************************************************************************
*  stack_by_value.c quiz                                                       *
*  Author: Ariel                                                               *
*******************************************************************************/
#include <stddef.h> /* size_t       */
#include <assert.h> /* assert       */
#include <stdlib.h> /* malloc, free */
#include <string.h> /* memcpy       */ 
#include <stdio.h>  /* printf       */

#define OFFSETOF(TYPE, ELEMENT) ((size_t)&(((TYPE *)0)->ELEMENT))

typedef struct stack
{
	size_t elem_size;
	size_t size;
	size_t capacity;
	char array[1];
}stack_ty;

stack_ty *StackCreate(size_t capacity, size_t elem_size);
void StackPush(stack_ty *stack, void *element);
void StackPop(stack_ty *stack);
void *StackPeek(stack_ty *stack);
void StackDestroy(stack_ty *stack);

int main(void)
{
	size_t i = 0;
	size_t capacity = 5;
	size_t elem_size = 4;
	int array[5] = {1, 2, 3, 4, 5};

	stack_ty *new_stack = StackCreate(capacity, elem_size);

	for(i = 0; i < capacity; ++i)
	{
		StackPush(new_stack, &array[i]);
	}

	printf("Peek: %d\n", *(int *)StackPeek(new_stack));

	StackPop(new_stack);

	printf("Peek: %d\n", *(int *)StackPeek(new_stack));

	StackDestroy(new_stack);

	return 0;
}

stack_ty *StackCreate(size_t capacity, size_t elem_size)
{
	stack_ty *new_stack = (stack_ty *)malloc(OFFSETOF(stack_ty, array) + 
	                                                    (capacity * elem_size));

	if(!new_stack)
	{
		return NULL;
	}

	new_stack->elem_size = elem_size;
	new_stack->size = 0;
	new_stack->capacity = capacity * elem_size;

	return new_stack;
}

void StackPush(stack_ty *stack, void *element)
{
	assert(stack);
	assert(element);
	
	if(stack->size < stack->capacity)
	{
		memcpy(&stack->array[stack->size], (char *)element, stack->elem_size);
		stack->size += stack->elem_size;
	}
}

void StackPop(stack_ty *stack)
{
	assert(stack);
	assert(0 != stack->size);

	stack->size -= stack->elem_size;
}

void *StackPeek(stack_ty *stack)
{
	assert(stack);
	assert(0 != stack->size);

	return &stack->array[stack->size - stack->elem_size];
}



/********* Helper Functions ***************************************************/

void StackDestroy(stack_ty *stack)
{
	assert(stack);
	
	free(stack);
	stack = NULL;
}


