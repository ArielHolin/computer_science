/*******************************************************************************
*  vector_test.c                                                               *
*  Author: Ariel                                                               *
*  Reviewer:                                                                   *
*******************************************************************************/
#include <stddef.h> /* size_t */
#include <stdio.h>  /* printf */

#include "../include/vector.h"

#define CAPACITY     5
#define MAX_CAPACITY 8

static void TestVectorCreate(void);
static void TestVectorPushValSizeCap(void);
static void TestVectorPopSetShrinkReserve(void);
static void Test(size_t expected_res, size_t res, const char *test_name, 
                 const char *filename, size_t line_num);

int main(void)
{
	TestVectorCreate();
	TestVectorPushValSizeCap();
	TestVectorPopSetShrinkReserve();
	return 0;
}

/******* TestVectorCreate *****************************************************/

static void TestVectorCreate(void)
{
	size_t capacities[CAPACITY] = {1, 2, 3, 4, 5};
	size_t void_ptr_size = sizeof(void *);
	size_t i = 0;
	
	for ( i = 0; i < CAPACITY; ++i )
	{
		vector_ty *test_vector = VectorCreate(capacities[i]);
		
		Test(capacities[i], VectorCapacity(test_vector), 
		     "TestStackCreateAndCapacity()", __FILE__, __LINE__);
		Test(void_ptr_size, sizeof(VectorGetVal(test_vector, 0)), 
		     "TestStackCreateAndCapacity()", __FILE__, __LINE__);
		
		VectorDestroy(test_vector);
	}
}

/******* TestVectorPushValSizeCap *********************************************/

static void TestVectorPushValSizeCap(void)
{
	size_t capacity = 1;
	size_t push_vals[] = {1, 2, 3, 4, 5, 6, 7, 8};
	size_t sizes[] = {1, 2, 3, 4, 5, 6, 7, 8};
	size_t capacity_vals[] = {1, 2, 4, 4, 8, 8, 8, 8};
	size_t i = 0;
	
	vector_ty *test_vector = VectorCreate(capacity);
	
	for ( i = 0; i < 8; ++i )
	{
		VectorPushBack(test_vector, &push_vals[i]);
		
		Test(push_vals[i], *(size_t *)VectorGetVal(test_vector, i),
		     "TestVectorGetVal()", __FILE__, __LINE__);
		Test(sizes[i], VectorSize(test_vector), 
			 "TestVectorSize()", __FILE__, __LINE__);
	    Test(capacity_vals[i], VectorCapacity(test_vector),
	    	 "TestVectorCapacity()", __FILE__, __LINE__);
	}
	
	VectorDestroy(test_vector);
}

/****** TestVectorPopSetShrinkReserve *****************************************/

static void TestVectorPopSetShrinkReserve(void)
{
	size_t capacity = 1;
	size_t push_vals[] = {1, 2, 3, 4, 5, 6, 7, 8};
	size_t set_vals[] = {9, 10, 11, 12, 13, 14, 15, 16};
	size_t after_set = 0;
	size_t i = 0;
	
	vector_ty *test_vector = VectorCreate(capacity);
	
	for ( i = 0; i < MAX_CAPACITY; ++i )
	{
		VectorPushBack(test_vector, &push_vals[i]);
	}
	
	for ( i = 0; i < MAX_CAPACITY; ++i)
	{
		after_set = *(size_t *)VectorSetVal(test_vector, i, &set_vals[i]);
		Test(after_set, *(size_t *)VectorGetVal(test_vector, i),
		     "TestVectorSetVal()", __FILE__, __LINE__);
	}
	
	for ( i = 0; i < MAX_CAPACITY; ++i )
	{
		VectorPopBack(test_vector);
		
		if ( i == 2 )
		{
			VectorShrinkToFit(test_vector);
			Test(5, VectorCapacity(test_vector),
			     "TestVectorShrinkToFit()", __FILE__, __LINE__);
			VectorReserve(test_vector, MAX_CAPACITY);
		}
		
		if ( i == 6 )
		{
			Test(8, VectorCapacity(test_vector),
			     "TestVectorPopBack()", __FILE__, __LINE__);
			     
			VectorReserve(test_vector, MAX_CAPACITY);
			
			Test(MAX_CAPACITY, VectorCapacity(test_vector),
			     "TestVectorReserve()", __FILE__, __LINE__);
			
			Test(set_vals[MAX_CAPACITY - i - 1], 
			     *(size_t *)VectorGetVal(test_vector, MAX_CAPACITY - i - 1),
			     "TestVectorPopBack()", __FILE__, __LINE__);
		}
	}
	
	VectorDestroy(test_vector);
}

/********** Test Template *****************************************************/

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
