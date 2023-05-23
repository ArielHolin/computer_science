/*******************************************************************************
*  Stack_test.c                                                                *
*  Author: Ariel                                                               *
*  Reviewer:                                                                   *
*******************************************************************************/
#include <stddef.h> /* size_t */
#include <stdio.h>  /* printf */

#include "../include/stack.h"

#define CAPACITY 5

static void TestStackCreateCapacity(void);
static void TestStackPushSizePeekPop(void);
static void Test(size_t expected_res, size_t res, const char *test_name, 
                 const char *filename, size_t line_num);

int main(void)
{
	TestStackCreateCapacity();
	TestStackPushSizePeekPop();
	return 0;
}

static void TestStackCreateCapacity(void)
{
	size_t capacities[CAPACITY] = {1, 2, 3, 4, 5};
	size_t void_ptr_size = sizeof(void *);
	size_t i = 0;
	
	for ( i = 0; i < CAPACITY; ++i )
	{
		stack_ty *test_stack = StackCreate(capacities[i]);
		
		Test(capacities[i], StackCapacity(test_stack), 
		     "TestStackCreateAndCapacity()", __FILE__, __LINE__);
		Test(void_ptr_size, sizeof(StackPeek(test_stack)), 
		     "TestStackCreateAndCapacity()", __FILE__, __LINE__);
		
		StackDestroy(test_stack);
	}
}

static void TestStackPushSizePeekPop(void)
{
	size_t i = 0;
	size_t pushed_vals[CAPACITY] = {1, 2, 3, 4, 5};
	
	stack_ty *test_stack = StackCreate(CAPACITY);
	
	for ( i = 0; i < CAPACITY; ++i )
	{
		StackPush(test_stack, &pushed_vals[i]);
		
		Test(pushed_vals[i], *(size_t *)StackPeek(test_stack), 
		     "TestStackPush()", __FILE__, __LINE__);
		Test(pushed_vals[i], *(size_t *)StackPeek(test_stack), 
		     "TestStackPeek()", __FILE__, __LINE__);
		Test(pushed_vals[i], StackSize(test_stack), 
		     "TestStackSize()", __FILE__, __LINE__);
		
		if ( i >= 1 )
		{
			StackPop(test_stack);
			Test(pushed_vals[i-1], *(size_t *)StackPeek(test_stack), 
			     "TestStackPop()", __FILE__, __LINE__);
			StackPush(test_stack, &pushed_vals[i]);
		}
	}
	
	StackDestroy(test_stack);
}

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
