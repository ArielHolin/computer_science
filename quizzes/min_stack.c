/*******************************************************************************
*  min_stack.c Quiz                                                            *                                                 
*  Author: Ariel                                                               *
*******************************************************************************/
#include <stddef.h> /* size_t       */
#include <stdlib.h> /* malloc, free */
#include <assert.h> /* assert       */
#include <stdio.h>  /* printf       */

#include "stack.h"

#define ISFULL(stack) (StackSize(stack) == StackCapacity(stack))

#define STACK_SIZE 10

typedef struct stack_min
{
	stack_ty *stack;
	stack_ty *min_stack;
}stack_min_ty;

stack_min_ty *MinStackCreate(size_t capacity);
void MinStackDestroy(stack_min_ty *min_stack, stack_ty *stack, stack_ty *min_stack_min);
void MinStackPush(stack_ty *dest_stack, stack_ty *src_stack, void *element);
void MinStackPop(stack_ty *dest_stack, stack_ty *src_stack);
int MinStackGetMin(stack_ty *stack);
static void Test(size_t expected_res, size_t res, const char *test_name, 
                 const char *filename, size_t line_num);

int main(void)
{
	int elements[STACK_SIZE] = {-1, 6, 3, 7, -5, -10, 34, -12, 8, 16};
	stack_ty *stack = NULL;
	stack_ty *min_stack = NULL;
	size_t i = 0;
	
	stack_min_ty *new_stacks = MinStackCreate(STACK_SIZE);
	
	stack = new_stacks->stack;
	min_stack = new_stacks->min_stack;
	
	for( i = 0; i < STACK_SIZE; ++i )
	{
		MinStackPush(stack, min_stack, &elements[i]);
		
		if( i == 2 )
		{
			Test(-1, MinStackGetMin(min_stack), "TestMinStackGetMin()",
			     __FILE__, __LINE__);
		}
		
		if( i == 4 )
		{
			Test(-5, MinStackGetMin(min_stack), "TestMinStackGetMin()",
			     __FILE__, __LINE__);
		}
		
		if( i == STACK_SIZE - 1 )
		{
			Test(-12, MinStackGetMin(min_stack), "TestMinStackGetMin()",
			     __FILE__, __LINE__);
		}
	}
	
	for( i = 0; i < STACK_SIZE; ++i )
	{
		MinStackPop(stack, min_stack);
		
		if( i == 1 )
		{
			Test(-12, MinStackGetMin(min_stack), "TestMinStackGetMin()",
			     __FILE__, __LINE__);
		}
		
		if( i == 2 )
		{
		Test(-10, MinStackGetMin(min_stack), "TestMinStackGetMin()",
			     __FILE__, __LINE__);
		}
		
		if( i == 5 )
		{
		Test(-1, MinStackGetMin(min_stack), "TestMinStackGetMin()",
			     __FILE__, __LINE__);
		}
		
		if( i == 6 )
		{
		Test(-1, MinStackGetMin(min_stack), "TestMinStackGetMin()",
			     __FILE__, __LINE__);
		}
	}
	 
	MinStackDestroy(new_stacks, stack, min_stack);
	return 0;
}

/***** MinStackCreate *********************************************************/

stack_min_ty *MinStackCreate(size_t capacity)
{
	stack_min_ty *new_stack_min = (stack_min_ty *)malloc(sizeof(stack_min_ty));
	
	if( !new_stack_min ) return NULL;
	
	new_stack_min->stack = StackCreate(capacity);
	
	if( !new_stack_min->stack )
	{
		free(new_stack_min);
		new_stack_min = NULL;
		
		return NULL;
	}
	
	new_stack_min->min_stack = StackCreate(capacity);
	
	if( !new_stack_min->min_stack )
	{
		StackDestroy(new_stack_min->stack);
		
		free(new_stack_min);
		new_stack_min = NULL;
	}
	
	return new_stack_min; 
}

/**** MinStackDestroy *********************************************************/

void MinStackDestroy(stack_min_ty *min_stack, stack_ty *stack, stack_ty *min_stack_min)
{
	assert(min_stack);
	assert(stack);
	assert(min_stack);
	
	StackDestroy(stack);
	
	StackDestroy(min_stack_min);
	
	free(min_stack);
	min_stack = NULL;
}

/***** MinStackPush ***********************************************************/

void MinStackPush(stack_ty *stack, stack_ty *min_stack, void *element)
{
	void *top_min_element = NULL;
	
	assert(stack);
	assert(min_stack);
	assert( !ISFULL(stack) );
	assert( !ISFULL(min_stack) );
	
	StackPush(stack, element);
	
	if( StackIsEmpty(min_stack) )
	{
		StackPush(min_stack, element);
	}
	
	else
	{
		top_min_element = StackPeek(min_stack);
		
		if( *(int *)top_min_element > *(int *)element )
		{
			StackPush(min_stack, element);
		}
		
		else
		{
			StackPush(min_stack, top_min_element);
		}
	}	
}

/***** MinStackPop ************************************************************/

void MinStackPop(stack_ty *stack, stack_ty *min_stack)
{
	assert(stack);
	assert( !StackIsEmpty(stack) );
	
	assert(min_stack);
	assert( !StackIsEmpty(min_stack) );
	
	StackPop(stack);
	StackPop(min_stack);
}

/***** MinStackGetMin *********************************************************/

int MinStackGetMin(stack_ty *min_stack)
{
	return *(int *)StackPeek(min_stack);
}

/******** Test Template *******************************************************/

static void Test(size_t expected_res, size_t res, const char *test_name, 
                 const char *filename, size_t line_num)
{
	if (expected_res == res)
	{
		printf("%s success\n", test_name);
	}
	
	else 
	{
		printf("%s failed in file %s at line %li\n", 
		       test_name, filename, line_num);
	}
}
