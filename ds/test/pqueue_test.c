/*******************************************************************************
*  pqueue_test.c                                                               *
*  Author: Ariel                                                               *
*  Reviewer:                                                                   *
*******************************************************************************/
#include <stddef.h> /* size_t */
#include <stdio.h>  /* printf */

#include "sorted_list.h"
#include "pqueue.h"

#define NON_EMPTY 0
#define EMPTY     1

#define LIST_SIZE 5

enum ilrd_status
{
	ILRD_SUCCESS = 0,
	ILRD_FAILURE = 1
};

void TestPQCreateDestroy(void);
void TestPQEnqueue(void);
void TestPQPeek(void);
void TestPQSizeIsEmptyClear(void);
void TestPQErase(void);
static void Test(size_t expected_res, size_t res, const char *test_name, 
                 const char *filename, size_t line_num);

int main(void)
{
	TestPQCreateDestroy();
	TestPQEnqueue();
	TestPQPeek();
	TestPQSizeIsEmptyClear();
	TestPQErase();
	return 0;
}

/***** type functions *********************************************************/

static int cmp_func(const void *data, const void *param)
{	
	return *(int *)data - *(int *)param;
}

int match(const void *data1, const void *data2)
{
	return *(size_t *)data1 == *(size_t *)data2;
}

/***** TestPQCreateDestroy ****************************************************/

void TestPQCreateDestroy(void)
{
	pqueue_ty *new_pq = PQCreate(cmp_func);
	
	Test(EMPTY, PQIsEmpty(new_pq), 
	     "TestPQCreateDestroy()", __FILE__, __LINE__);
	     
	PQDestroy(new_pq);
	
	printf("----------\n");
}

/***** TestPQEnqueue **********************************************************/

void TestPQEnqueue(void)
{
	pqueue_ty *new_pq = PQCreate(cmp_func);
	size_t elements[LIST_SIZE] = {4, 1, 2, 5, 3};
	size_t dequeue_results[LIST_SIZE] = {5, 4, 3, 2, 1};
	size_t i = 0;
	int enqueue_res = ILRD_SUCCESS;
	
	for( i = 0; i < LIST_SIZE; ++i )
	{
		enqueue_res = PQEnqueue(new_pq, &elements[i]);
		
		Test(ILRD_SUCCESS, enqueue_res, "TestPQEnqueue()", __FILE__, __LINE__);
	}
	
	printf("----------\n");
	
	for( i = 0; i < LIST_SIZE; ++i )
	{
		Test(dequeue_results[i], *(size_t *)PQDequeue(new_pq), "TestPQDequeue()",
		     __FILE__, __LINE__);
	}
	
	PQDestroy(new_pq);
	
	printf("----------\n");
}

/***** TestPQPeek *************************************************************/

void TestPQPeek(void)
{
	pqueue_ty *new_pq = PQCreate(cmp_func);
	size_t elements[LIST_SIZE] = {4, 1, 2, 5, 3};
	size_t peek_results[LIST_SIZE] = {4, 4, 4, 5, 5};
	size_t i = 0;
	
	for( i = 0; i < LIST_SIZE; ++i )
	{	
		PQEnqueue(new_pq, &elements[i]);
		
		Test(peek_results[i], *(size_t *)PQPeek(new_pq), "PQPeek()", 
		     __FILE__, __LINE__);
	}
	
	PQDestroy(new_pq);
	
	printf("----------\n");
}

/***** TestPQSizeIsEmptyClear *************************************************/

void TestPQSizeIsEmptyClear(void)
{
	pqueue_ty *new_pq = PQCreate(cmp_func);
	size_t elements[LIST_SIZE] = {4, 1, 2, 5, 3};
	size_t i = 0;
	
	Test(EMPTY, PQIsEmpty(new_pq), "TestPQIsempty()", __FILE__, __LINE__);
	
	for( i = 0; i < LIST_SIZE; ++i )
	{	
		PQEnqueue(new_pq, &elements[i]);
	}
	
	Test(LIST_SIZE, PQSize(new_pq), "TestPQSize()", __FILE__, __LINE__);
	
	Test(NON_EMPTY, PQIsEmpty(new_pq), "TestPQIsEmpty()", __FILE__, __LINE__);
	
	PQClear(new_pq);
	
	Test(EMPTY, PQIsEmpty(new_pq), "TestPQClear()", __FILE__, __LINE__);
	
	PQDestroy(new_pq);
	
	printf("----------\n");
}

/***** TestPQErase ************************************************************/

void TestPQErase(void)
{
	pqueue_ty *new_pq = PQCreate(cmp_func);
	size_t elements[LIST_SIZE] = {4, 1, 2, 5, 3};
	size_t param1 = 5;
	size_t param2 = 1;
	size_t param3 = 3;
	size_t i = 0;
	
	for( i = 0; i < LIST_SIZE; ++i )
	{	
		PQEnqueue(new_pq, &elements[i]);
	}
	
	Test(param1, *(size_t *)PQErease(new_pq, match, &param1), "TestPQErase()",
	     __FILE__, __LINE__ );
	     
	Test(param2, *(size_t *)PQErease(new_pq, match, &param2), "TestPQErase()",
	     __FILE__, __LINE__ );
	     
	Test(param3, *(size_t *)PQErease(new_pq, match, &param3), "TestPQErase()",
	     __FILE__, __LINE__ );
	     
	PQDestroy(new_pq);
	
	printf("----------\n");
}

/***** Test Template **********************************************************/

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
