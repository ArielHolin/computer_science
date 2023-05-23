/******************************************************************************
*  heap_test.c                                                                *
*  Author: Ariel                                                              *
*  Reviewer: Philip                                                           *
******************************************************************************/ 
#include <stdio.h> /* size_t */
#include <assert.h> /* assert */

#include "heap.h"
#include "utils.h"
#include "vector.h"

#define COUNTER_EMPTY         0 
#define NUM_OF_ELEMENTS      10
#define IRRELEVANT            0

typedef struct results
{  
	int is_empty;
	size_t size;
	int status_from_push;
	int status_from_pop;		
   void *data_from_peek;
   void *data_from_remove;
	
} results_ty;

struct heap
{
   heap_cmp_func_ty cmp_func;
   vector_ty *vector;
};

/* test functions */
void TestHeapCreate(void);
void TestHeapPush(void);
void TestHeapPop(void);
void TestHeapRemove(void);

/* print start & end of tests functions */
static void BeginingOfTests(const char *test_name);
static void EndOfTests(void);
static void Remainder(void);

/* copmpare functions */
static void TestResultComper(results_ty results, results_ty expected_results,
                                            const char *test_name, size_t line);
static int TestResultComperMulti(results_ty results, results_ty expected_results,
                                            const char *test_name, size_t line);
static void TestPrintResultComperMulti(int test_is_successful_flag, 
	                                                     const char *test_name);

/* helper */
static void HeapMultiInsert(heap_ty *heap, size_t num_of_insert, int *array);

/* action & match functions */
static int Cmp(const void *data, const void *param);
static int MatchFunc(const void *data, const void *param);

/*******************************************************************************
************************************ The Main  ********************************/

int main ()
{  
	const char *tests_name = "Heap Data Structre Tests";

	BeginingOfTests(tests_name);

	/* The main test functions */
	TestHeapCreate();
	TestHeapPush();
	TestHeapPop();
	TestHeapRemove();

	Remainder();

	EndOfTests();
	
	return 0; 
}

/*******************************************************************************
*********************** Test Initialize Priority Queue ***********************/

void TestHeapCreate()
{ 
	const char *test_name = "CREATE";
	int null = 0; 
	void *ptr_to_null = &null;
	size_t capacity = 10;

	heap_ty *heap = HeapCreate(Cmp, capacity);
	
	results_ty expected_results;
	results_ty results;

	expected_results.is_empty = EMPTY;
	expected_results.size = COUNTER_EMPTY;
	expected_results.status_from_push  = IRRELEVANT;
	expected_results.status_from_pop = IRRELEVANT;
	expected_results.data_from_peek = ptr_to_null;
	expected_results.data_from_remove = ptr_to_null;

	results.is_empty = HeapIsEmpty(heap);
	results.size = HeapSize(heap);
	results.status_from_push  = IRRELEVANT;
	results.status_from_pop = IRRELEVANT;
	results.data_from_peek = ptr_to_null;
	results.data_from_remove = ptr_to_null;
		
	TestResultComper(results, expected_results, test_name, __LINE__);

	HeapDestroy(heap);
}
/*******************************************************************************
********************************* Test PQEnqueue ******************************/

void TestHeapPush()
{ 
	const char *test_name = "PUSH";
	int test_flag = ILRD_TRUE;
	int null = 0; 
	void *ptr_to_null = &null;
	size_t capacity = 20;

	heap_ty *heap = HeapCreate(Cmp, capacity);
	
	results_ty expected_results;
	results_ty results;

	int array_of_data[NUM_OF_ELEMENTS] = {6,7,8,9,10,1,2,3,4,5};
	int array_of_expected[NUM_OF_ELEMENTS] = {6,7,8,9,10,10,10,10,10,10};
	
	int i = 0;

	for(i = 0; i < NUM_OF_ELEMENTS; i++)
	{
		results.status_from_push  = HeapPush(heap, (void *)(array_of_data + i));

		expected_results.is_empty = NOT_EMPTY;
		expected_results.size = i + 1;
		expected_results.status_from_push = SUCSSES;
		expected_results.status_from_pop = IRRELEVANT;
		expected_results.data_from_peek = (void *)&array_of_expected[i];
		expected_results.data_from_remove = ptr_to_null;

		results.is_empty = HeapIsEmpty(heap);
		results.size = HeapSize(heap);
		results.status_from_pop = IRRELEVANT;
		results.data_from_peek = HeapPeek(heap);
		results.data_from_remove = ptr_to_null;

		test_flag += TestResultComperMulti(results, expected_results, 
			                               test_name, __LINE__);		                  
	}

	TestPrintResultComperMulti(test_flag/NUM_OF_ELEMENTS, test_name);

	HeapDestroy(heap);
}

/*******************************************************************************
******************************** Test PQDqueue ********************************/

void TestHeapPop(void)
{ 
	const char *test_name = "POP";
	int test_flag = ILRD_TRUE;
	int null = 0; 
	void *ptr_to_null = &null;
	size_t capacity = 20;

	heap_ty *heap = HeapCreate(Cmp, capacity);
	
	results_ty expected_results;
	results_ty results;

	int array_of_data[NUM_OF_ELEMENTS] = {6,7,8,9,10,1,2,3,4,5};
	int array_of_expected[NUM_OF_ELEMENTS] = {10,9,8,7,6,5,4,3,2,1};

	int i = 0;

	HeapMultiInsert(heap, NUM_OF_ELEMENTS, array_of_data);

	for(i = 0; i < NUM_OF_ELEMENTS; i++)
	{
		expected_results.is_empty = NOT_EMPTY;
		expected_results.size = NUM_OF_ELEMENTS - i;
		expected_results.status_from_push = IRRELEVANT;
		expected_results.status_from_pop = SUCSSES;
		expected_results.data_from_peek = (void *)&array_of_expected[i];
		expected_results.data_from_remove = ptr_to_null;

		results.is_empty = HeapIsEmpty(heap);
		results.size = HeapSize(heap);
		results.status_from_push = IRRELEVANT;
		results.data_from_peek = HeapPeek(heap);
		results.status_from_pop = HeapPop(heap);
		results.data_from_remove = ptr_to_null;

		test_flag += TestResultComperMulti(results, expected_results, 
			                                test_name, __LINE__);	                  
	}

	TestPrintResultComperMulti(test_flag/NUM_OF_ELEMENTS, test_name);

	HeapDestroy(heap);
}

/*******************************************************************************
******************************** Test PQ Empty ********************************/

void TestHeapRemove()
{ 
	const char *test_name = "REMOVE";
	int test_flag = ILRD_TRUE;
	int null = 0; 
	void *ptr_to_null = &null;
	size_t capacity = 20;

	heap_ty *heap = HeapCreate(Cmp, capacity);
	
	results_ty expected_results;
	results_ty results;

	int array_of_data[NUM_OF_ELEMENTS] = {6,7,8,9,10,1,2,3,4,5};
	int array_of_expected[NUM_OF_ELEMENTS] = {10,10,10,10,10,5,5,5,5,5};

	void *param = (void *)&array_of_data[9];

	int i = 0;

	HeapMultiInsert(heap, NUM_OF_ELEMENTS, array_of_data);

	for(i = 0; i < NUM_OF_ELEMENTS; i++)
	{

		param = (void *)&array_of_data[i];

		expected_results.is_empty = NOT_EMPTY;
		expected_results.size = NUM_OF_ELEMENTS - i;
		expected_results.status_from_push = IRRELEVANT;
		expected_results.status_from_pop = IRRELEVANT;
		expected_results.data_from_peek = (void *)&array_of_expected[i];
		expected_results.data_from_remove = (void *)&array_of_data[i];

		results.is_empty = HeapIsEmpty(heap);
		results.size = HeapSize(heap);
		results.status_from_push = IRRELEVANT;
		results.status_from_pop = IRRELEVANT;
		results.data_from_peek = HeapPeek(heap);
		results.data_from_remove = HeapRemove(heap, param, MatchFunc);

		test_flag += TestResultComperMulti(results, expected_results, 
			                                test_name, __LINE__);	                  
	}

	TestPrintResultComperMulti(test_flag/NUM_OF_ELEMENTS, test_name);

	HeapDestroy(heap);
}


/*******************************************************************************
************************************** Cmp ************************************/

static int Cmp(const void *data, const void *param)
{
	assert(param);
	assert(data);

	return -(*(int *)param - *(int *)data);
}

/*******************************************************************************
********************************** Match Func *********************************/

static int MatchFunc(const void *data, const void *param)
{
	if((*(int *)param == *(int *)data))
	{
		return 1;
	}

	return 0;
}

/*******************************************************************************
****************************** dlist Multi Insert *****************************/

static void HeapMultiInsert(heap_ty *heap, size_t num_of_insert, int *array)
{
	size_t i = 0;
	
	for(i = 0; i < num_of_insert; i++)
	{
		HeapPush(heap, (void *)(array + i));
	}
}

/*******************************************************************************
******************************* Test Result Comper ****************************/

static void TestResultComper(results_ty results, results_ty expected_results,
                                             const char *test_name, size_t line)
{ 
	const char *test_object= "pqueue test";
	int test_is_successful_flag = ILRD_TRUE;

	if(results.is_empty != expected_results.is_empty)
	{
		printf(RED);
		printf("\nThe is_empty test fail for %s %s at line %lu\n",
		                                          test_name, test_object, line);
		test_is_successful_flag = ILRD_FALSE;
	}
	if(results.size != expected_results.size)
	{
		printf(RED);
		printf("\nThe init counter test fail for %s %s at line %lu\n",
		                                          test_name, test_object, line);
		test_is_successful_flag = ILRD_FALSE;
	}

	if(results.status_from_push != expected_results.status_from_push)
	{
		printf(RED);
		printf("\nThe status_from_push test fail for %s %s at line %lu\n",
		                                          test_name, test_object, line);
		test_is_successful_flag = ILRD_FALSE;
	}
	if(results.status_from_pop != expected_results.status_from_pop)
	{
		printf(RED);
		printf("\nThe status_from_pop test fail for %s %s at line %lu\n",
		                                          test_name, test_object, line);
		test_is_successful_flag = ILRD_FALSE;
	}
	if(*(int *)(results.data_from_remove) != *(int *)(expected_results.data_from_remove))
	{
		printf(RED);
		printf("\nThe data_from_remove test fail for %s %s at line %lu\n", 
			                                      test_name, test_object, line);
		test_is_successful_flag = ILRD_FALSE;
	}
	if(*(int *)(results.data_from_peek) != *(int *)(expected_results.data_from_peek))
	{
		printf(RED);
		printf("\nThe data_from_peek test fail for %s %s at line %lu\n",
			                                      test_name, test_object, line);
		test_is_successful_flag = ILRD_FALSE;
	} 

	if(test_is_successful_flag == ILRD_TRUE)
	{
		printf(GREEN);
		printf("\n %s %s passed !\n", test_name ,test_object);
	} 
}

/*******************************************************************************
**************************** Test Result Comper Multi *************************/

static int TestResultComperMulti(results_ty results, results_ty expected_results,
                                             const char *test_name, size_t line)
{ 
	const char *test_object= "heap test";
	int test_is_successful_flag = ILRD_TRUE;

	if(results.is_empty != expected_results.is_empty)
	{
		printf(RED);
		printf("\nThe is_empty test fail for %s %s at line %lu\n",
		                                          test_name, test_object, line);
		test_is_successful_flag = ILRD_FALSE;
	}
	if(results.size != expected_results.size)
	{
		printf(RED);
		printf("\nThe init counter test fail for %s %s at line %lu\n",
		                                          test_name, test_object, line);
		test_is_successful_flag = ILRD_FALSE;
	}
	if(results.status_from_push != expected_results.status_from_push)
	{
		printf(RED);
		printf("\nThe status_from_push test fail for %s %s at line %lu\n",
		                                          test_name, test_object, line);
		test_is_successful_flag = ILRD_FALSE;
	}
	if(results.status_from_pop != expected_results.status_from_pop)
	{
		printf(RED);
		printf("\nThe status_from_pop test fail for %s %s at line %lu\n",
		                                          test_name, test_object, line);
		test_is_successful_flag = ILRD_FALSE;
	}
	if(*(int *)(results.data_from_remove) != *(int *)(expected_results.data_from_remove))
	{
		printf(RED);
		printf("\nThe data_from_remove test fail for %s %s at line %lu\n", 
			                                      test_name, test_object, line);
		test_is_successful_flag = ILRD_FALSE;
	}
	if(*(int *)(results.data_from_peek) != *(int *)(expected_results.data_from_peek))
	{
		printf(RED);
		printf("\nThe Sequence of peek's test fail for %s %s at line %lu\n",
			                                      test_name, test_object, line);
		test_is_successful_flag = ILRD_FALSE;
	} 

	return test_is_successful_flag;
}

/*******************************************************************************
************************ Test Print Result Comper Multi ***********************/

static void TestPrintResultComperMulti(int test_is_successful_flag,
                                       const char *test_name)
{ 
	const char *test_object= "heap test";

	if(test_is_successful_flag == ILRD_TRUE)
	{
		printf(GREEN);
		printf("\n %s %s passed !\n", test_name ,test_object);
	} 
}

/*******************************************************************************
******************************* Begining Of Tests *****************************/

static void BeginingOfTests(const char *tests_name)
{
	printf(YELLOW);
	printf("\n______________________ %s _____________________\n\n", tests_name);
}

/*******************************************************************************
********************************** End Of Tests *******************************/

static void EndOfTests(void)
{
	const char *end = "End Of Tests";

	printf(YELLOW);
	printf("\n_________________________ %s _______________________\n\n", end);
}

/*******************************************************************************
************************************ Remainder ********************************/

static void Remainder(void)
{
	printf(RED);
	puts("\n DESTROY TEST - vlgrain is required \n");
}








