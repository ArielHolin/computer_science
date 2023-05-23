/*******************************************************************************
*  Queue_test.c                                                                *
*  Author: Ariel                                                               *
*  Reviewer: Nisan                                                             *
*******************************************************************************/
#include <stdio.h>  /* printf */
#include <stddef.h> /* size_t */

#include "../include/queue.h"

#define SUCCESS 0
#define EMPTY   1
#define QSIZE   5


static void TestQueueCreateDestroy(void);
static void TestQueueEnqueuePeekSize(void);
static void TestQueueDequeueIsEmpty(void);
static void TestQueueAppend(void);
static void Test(size_t expected_res, size_t res, const char *test_name, 
                 const char *filename, size_t line_num);

int main(void)
{
	TestQueueCreateDestroy();
	printf("\n----------\n");
	TestQueueEnqueuePeekSize();
	printf("\n----------\n");
	TestQueueDequeueIsEmpty();
	printf("\n----------\n");
	TestQueueAppend();
	return 0;
}

/***** TestQueueCreate ********************************************************/

static void TestQueueCreateDestroy(void)
{
	queue_ty *new_queue = QueueCreate();
	
	Test(EMPTY, QueueIsEmpty(new_queue), 
	     "TestQueueCreateDestroy()", __FILE__, __LINE__);
	
	QueueDestroy(new_queue);
}

/***** TestQueueEnqueue *******************************************************/

static void TestQueueEnqueuePeekSize(void)
{
	queue_ty *new_queue = QueueCreate();
	size_t q_elements[QSIZE] = {1, 2, 3, 4, 5};
	size_t i = 0;
	int enqueue_res = 0;
	
	for( i = 0; i < QSIZE; ++i )
	{
		enqueue_res = QueueEnqueue(new_queue, &q_elements[i]);
		Test(SUCCESS, enqueue_res, "TestEnqueue()", __FILE__, __LINE__);
	}
	
	Test(q_elements[0], *(size_t *)QueuePeek(new_queue), 
	     "TestQueuePeek()", __FILE__, __LINE__);
	     
	Test(QSIZE, QueueSize(new_queue), "TestQueueSize()", __FILE__, __LINE__);
	
	QueueDestroy(new_queue);
}

/***** TestQueueDequeueIsEmpty ************************************************/

static void TestQueueDequeueIsEmpty(void)
{
	queue_ty *new_queue = QueueCreate();
	size_t q_elements[QSIZE] = {1, 2, 3, 4, 5};
	size_t i = 0;
	
	for( i = 0; i < QSIZE; ++i )
	{
		QueueEnqueue(new_queue, &q_elements[i]);
	}
	
	for( i = 0; i < QSIZE; ++i )
	{
		if( i >= 1)
		{
			Test(q_elements[i], *(size_t *)QueuePeek(new_queue), 
			     "TestQueueDequeue()", __FILE__, __LINE__);
		}
		
		QueueDequeue(new_queue);
	}
	
	Test(EMPTY, QueueIsEmpty(new_queue), 
	     "TestQueueIsEmpty()", __FILE__, __LINE__);
	
	QueueDestroy(new_queue);
}

/***** TestQueueAppend ********************************************************/

static void TestQueueAppend(void)
{
	queue_ty *dst_queue = QueueCreate();
	queue_ty *src_queue = QueueCreate();
	
	size_t dst_elements[QSIZE] = {1, 2, 3, 4, 5};
	size_t src_elements[QSIZE] = {6, 7, 8, 9, 10};
	size_t i = 0;
	
	for( i = 0; i < QSIZE; ++i )
	{
		QueueEnqueue(dst_queue, &dst_elements[i]);
		QueueEnqueue(src_queue, &src_elements[i]);
	}
	
	dst_queue = QueueAppend(dst_queue, src_queue);
	
	Test(2 * QSIZE, QueueSize(dst_queue), "TestQueueAppend()", __FILE__, __LINE__);
	Test(EMPTY, QueueIsEmpty(src_queue), "TestQueueAppend()", __FILE__, __LINE__);
	
	QueueDestroy(dst_queue);
	QueueDestroy(src_queue);
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
