 /******************************************************************************
 *  dlist_test.c                                                               *
 *  Author: Ariel                                                              *
 *  Reviewer: Maayan                                                           *
 ******************************************************************************/
 #include <stdio.h>  /* printf */
 #include <stddef.h> /* size_t */
 
 #include "dlist.h"
 
#define NON_EMPTY 0
#define EMPTY     1

#define LIST_SIZE 5

enum ilrd_status
{
	ILRD_SUCCESS = 0,
	ILRD_FAILURE = 1
};
 
static void TestDListCreateDestroy(void);
static void TestDListInsert(void);
static void TestDListRemoveSizeIsEmpty(void);
static void TestDListBeginNextPrevEnd(void);
static void TestDListGetSetData(void);
static void TestDListIsEqual(void);
static void TestDListFind(void);
static int match(const void *data, void *param);
static void TestDListForEach(void);
static int action(void *data, void *param); 
static void TestDListPushFrontBack(void); 
static void TestDListPopFrontBack(void);
static void TestDListMultiFind(void);
static void TestDListSplice(void);
static void Test(size_t expected_res, size_t res, const char *test_name, 
                 const char *filename, size_t line_num);

int main(void)
{
	TestDListCreateDestroy();
	TestDListInsert();
	TestDListRemoveSizeIsEmpty();
	TestDListBeginNextPrevEnd();
	TestDListGetSetData();
	TestDListIsEqual();
	TestDListFind();
	TestDListForEach();
	TestDListPushFrontBack();
	TestDListPopFrontBack();
	TestDListMultiFind();
	TestDListSplice();
	return 0;
}
 
/***** TestDListCreateDestroy *************************************************/

static void TestDListCreateDestroy(void)
{
	dlist_ty *new_dlist = DListCreate();
	
	Test(EMPTY, DListIsEmpty(new_dlist), 
	     "TestDListCreateDestroy()", __FILE__, __LINE__);
	
	DListDestroy(new_dlist);
	
	printf("----------\n");
}

/***** TestDListInsert ********************************************************/

static void TestDListInsert(void)
{
	dlist_ty *new_dlist = DListCreate();
	dlist_iter_ty iter = NULL;
	size_t elements[LIST_SIZE] = {1, 2, 3, 4, 5};
	size_t i = 0;
	
	for( i = 0; i < LIST_SIZE; ++i )
	{
		DListInsert(DListEnd(new_dlist), &elements[i]);
	}
	
	iter = DListBegin(new_dlist);
	
	for( i = 0; i < LIST_SIZE; ++i )
	{
		Test(elements[i], *(size_t *)DListGetData(iter), "TestDListInsert()",
		     __FILE__, __LINE__);
		
		iter = DListNext(iter);
	}
	
	DListDestroy(new_dlist);
	
	printf("----------\n");
}

/******* TestDListRemoveSizeIsEmpty *******************************************/

static void TestDListRemoveSizeIsEmpty(void)
{
	dlist_ty *new_dlist = DListCreate();
	size_t elements[LIST_SIZE] = {1, 2, 3, 4, 5};
	size_t i = 0;
	
	for( i = 0; i < LIST_SIZE; ++i )
	{
		DListInsert(DListEnd(new_dlist), &elements[i]);
	}
	
	for( i = 0; i < LIST_SIZE; ++i )
	{
		Test(elements[LIST_SIZE - i - 1], DListSize(new_dlist), 
		     "TestDListRemove()", __FILE__, __LINE__);
		     
		Test(elements[LIST_SIZE - i - 1], DListSize(new_dlist), 
		     "TestDListSize()", __FILE__, __LINE__);
		     
		Test(NON_EMPTY, DListIsEmpty(new_dlist), "TestDListIsEmpty()",
		     __FILE__, __LINE__);
		
		DListRemove(DListBegin(new_dlist));
	}
	
	Test(EMPTY, DListIsEmpty(new_dlist), "TestDListIsEmpty()", 
	     __FILE__, __LINE__);
	
	DListDestroy(new_dlist);
	
	printf("----------\n");
}

/******* TestDListBeginNextPrevEnd ********************************************/

static void TestDListBeginNextPrevEnd(void)
{
	dlist_ty *new_dlist = DListCreate();
	dlist_iter_ty iter = NULL;
	size_t elements[LIST_SIZE] = {1, 2, 3, 4, 5};
	size_t i = 0;
	
	for( i = 0; i < LIST_SIZE; ++i )
	{
		DListInsert(DListEnd(new_dlist), &elements[i]);
	}
	
	iter = DListBegin(new_dlist);
	
	Test(elements[0], *(size_t *)DListGetData(iter), "TestDListBegin()", 
	     __FILE__, __LINE__);
	
	for( i = 0; i < LIST_SIZE - 1; ++i )
	{
		iter = DListNext(iter);
		
		Test(elements[i+1], *(size_t *)DListGetData(iter), "TestDListNext()",
		     __FILE__, __LINE__);
		     
		if( i >= 1 )
		{
			iter = DListPrev(iter);
			
			Test(elements[i], *(size_t *)DListGetData(iter), "TestDListPrev()",
		     __FILE__, __LINE__);
		     
		    iter = DListNext(iter);
		}
	}     
	
	if ( (LIST_SIZE == *(size_t *)DListGetData(iter)) && DListNext(iter) )
	{
		printf("TestDListEnd() Success\n");
	}
	
	DListDestroy(new_dlist);
	
	printf("----------\n");
}

/****** TestSlistGetSetData ***************************************************/

static void TestDListGetSetData(void)
{
	dlist_ty *new_dlist = DListCreate();
	dlist_iter_ty iter = NULL;
	size_t elements[LIST_SIZE] = {1, 2, 3, 4, 5};
	size_t set_elements[LIST_SIZE] = {6, 7, 8, 9 ,10};
	size_t i = 0;
	
	for( i = 0; i < LIST_SIZE; ++i )
	{
		DListInsert(DListEnd(new_dlist), &elements[i]);
	}
	
	iter = DListBegin(new_dlist);
	
	for( i = 0; i < LIST_SIZE; ++i )
	{
		Test(elements[i], *(size_t *)DListGetData(iter), "TestDListGetdata()",
		     __FILE__, __LINE__);
		
		iter = DListNext(iter);
	}
	
	iter = DListBegin(new_dlist);
	
	for( i = 0; i < LIST_SIZE; ++i )
	{
		DListSetData(iter, &set_elements[i]);
		Test(set_elements[i], *(size_t *)DListGetData(iter), 
		     "TestDListSetData()", __FILE__, __LINE__);
		     
		iter = DListNext(iter);
	}
	
	DListDestroy(new_dlist);
	
	printf("----------\n");
}

/****** TestDListIsEqual ******************************************************/

static void TestDListIsEqual(void)
{
	dlist_ty *new_dlist = DListCreate();
	dlist_iter_ty begin = NULL;
	size_t element = 1;
	
	Test((size_t)DListEnd(new_dlist), (size_t)DListBegin(new_dlist), 
	     "TestDListIsEqual()", __FILE__, __LINE__);
	
	DListInsert(DListEnd(new_dlist), &element);
	
	begin = DListBegin(new_dlist);
	
	Test((size_t)DListEnd(new_dlist), (size_t)DListNext(begin), 
	     "TestDListIsEqual()", __FILE__, __LINE__);
	     
	DListDestroy(new_dlist);
	
	printf("----------\n");
}

/******** TestDListFind *******************************************************/

static void TestDListFind(void)
{
	dlist_ty *new_dlist = DListCreate();
	dlist_iter_ty begin = NULL;
	dlist_iter_ty end = NULL;
	size_t param = 3;
	size_t elements[LIST_SIZE] = {1, 2, 3, 4, 5};
	size_t i = 0;
	
	for( i = 0; i < LIST_SIZE; ++i )
	{
		DListInsert(DListEnd(new_dlist), &elements[i]);
	}
	
	begin = DListBegin(new_dlist);
	end = DListEnd(new_dlist);
	
	Test(elements[2], *(size_t *)DListGetData(DListFind(begin, end, match, &param)),
	     "TestDListFind()", __FILE__, __LINE__);
	     
	Test(elements[2], *(size_t *)DListGetData(DListFind(begin, DListNext(DListNext(begin)), match, &param)), 
	     "TestDListFind()", __FILE__, __LINE__);
	     
	DListDestroy(new_dlist);
	
	printf("----------\n");
}

/* match function to use inside SlistFind */
static int match(const void *data, void *param)  
{
	return *(size_t *)data == *(size_t *)param;
}

/******* TestDListForEach *****************************************************/

static void TestDListForEach(void)
{
	dlist_ty *new_dlist = DListCreate();
	dlist_iter_ty begin = NULL;
	dlist_iter_ty end = NULL;
	size_t param = 3;
	size_t elements[LIST_SIZE] = {1, 2, 3, 4, 5};
	size_t i = 0;
	
	for( i = 0; i < LIST_SIZE; ++i )
	{
		DListInsert(DListEnd(new_dlist), &elements[i]);
	}
	
	begin = DListBegin(new_dlist);
	end = DListEnd(new_dlist);
	
	Test(ILRD_SUCCESS, (size_t)DListForEach(begin, end, action, &param), 
	     "TestDListForEach()", __FILE__, __LINE__);
	     
	DListDestroy(new_dlist);
	
	printf("----------\n");
}

static int action(void *data, void *param)
{
	*(size_t *)data += *(size_t *)param;
	
	return ILRD_SUCCESS;
}

/***** TestDListPushFrontBack *************************************************/

static void TestDListPushFrontBack(void)
{
	dlist_ty *new_dlist = DListCreate();
	size_t elements[LIST_SIZE] = {1, 2, 3, 4, 5};
	size_t i = 0;
	size_t front_element = 0;
	size_t back_element = 6;
	
	for( i = 0; i < LIST_SIZE; ++i )
	{
		DListInsert(DListEnd(new_dlist), &elements[i]);
	}
	
	DListPushFront(new_dlist, (void *)&front_element);
	
	Test(front_element, *(size_t *)DListGetData(DListBegin(new_dlist)), 
	     "TestDListPushFront()", __FILE__, __LINE__);
	     
	DListPushBack(new_dlist, (void *)&back_element);
	
	Test(back_element, *(size_t *)DListGetData(DListPrev(DListEnd(new_dlist))), 
	     "TestDListPushBack()", __FILE__, __LINE__);
	     
	DListDestroy(new_dlist);
	
	printf("----------\n");
}

/***** TestDListPopFrontBack **************************************************/

static void TestDListPopFrontBack(void)
{
	dlist_ty *new_dlist = DListCreate();
	size_t elements[LIST_SIZE] = {1, 2, 3, 4, 5};
	size_t i = 0;
	size_t pop_front = 0;
	size_t pop_back = 0;
	
	for( i = 0; i < LIST_SIZE; ++i )
	{
		DListInsert(DListEnd(new_dlist), &elements[i]);
	}
	
	pop_front = *(size_t *)DListPopFront(new_dlist);
	
	Test(elements[1], *(size_t *)DListGetData(DListBegin(new_dlist)),
	     "TestDListPopFront()", __FILE__, __LINE__);
	     
	Test(elements[0], pop_front, "TestDListPopFront()", __FILE__, __LINE__);
	
	pop_back = *(size_t *)DListPopBack(new_dlist);
	
	Test(elements[LIST_SIZE - 2], *(size_t *)DListGetData(DListPrev(DListEnd(new_dlist))),
	     "TestDListPopBack()", __FILE__, __LINE__);
	     
	Test(elements[LIST_SIZE - 1], pop_back, "TestDListPopBack()", 
	     __FILE__, __LINE__);
	     
	DListDestroy(new_dlist);
	
	printf("----------\n");
}

/***** TestDListMultiFind *****************************************************/

static void TestDListMultiFind(void) 
{
	dlist_ty *new_dlist = DListCreate();
	dlist_ty *output_dlist = DListCreate();
	dlist_iter_ty begin = NULL;
	dlist_iter_ty end = NULL;
	size_t param = 3;
	size_t output_dlist_size = 2;
	size_t elements[LIST_SIZE] = {3, 2, 3, 4, 5};
	size_t i = 0;
	int res = ILRD_FAILURE;
	
	for( i = 0; i < LIST_SIZE; ++i )
	{
		DListInsert(DListEnd(new_dlist), &elements[i]);
	}
	
	begin = DListBegin(new_dlist);
	end = DListEnd(new_dlist);
	
	res = DListMultiFind(begin, end, match, &param, output_dlist);
	
	Test(ILRD_SUCCESS, res, "TestDListMultiFind()", __FILE__, __LINE__);
	
	Test(output_dlist_size, DListSize(output_dlist), "TestDListMultiFind()", 
	     __FILE__, __LINE__);
	     
	DListDestroy(new_dlist);
	DListDestroy(output_dlist);
	
	printf("----------\n");
}

/***** TestDListSplice ********************************************************/

static void TestDListSplice(void)
{
	dlist_ty *new_dlist = DListCreate();
	dlist_iter_ty from = NULL;
	dlist_iter_ty to = NULL;
	dlist_iter_ty dest = NULL;
	dlist_iter_ty iter_res = NULL;
	dlist_iter_ty runner_iter_res = NULL;
	size_t elements[LIST_SIZE] = {1, 2, 3, 4, 5};
	size_t result[LIST_SIZE] = {3, 4, 1, 2, 5};
	size_t i = 0;
	
	for( i = 0; i < LIST_SIZE; ++i )
	{
		DListInsert(DListEnd(new_dlist), &elements[i]);
	}
	
	from = DListBegin(new_dlist);
	to = DListNext(DListNext(from));
	dest = DListPrev(DListPrev(DListEnd(new_dlist)));
	
	iter_res = DListSplice(from, to, dest);
	
	runner_iter_res = DListBegin(new_dlist);
	
	Test((size_t)iter_res, (size_t)from, "TestDListSplice()", __FILE__, __LINE__);
	
	for( i = 0; i < LIST_SIZE; ++i )
	{
		Test(result[i], *(size_t *)DListGetData(runner_iter_res), 
		     "TestDListSplice()", __FILE__, __LINE__);
		
		runner_iter_res = DListNext(runner_iter_res);
	}
	
	DListDestroy(new_dlist);
	
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
