/*******************************************************************************
*  sorted_list_test.c                                                          *
*  Author: Ariel                                                               *
*  Reviewer: Nasrat                                                            *
*******************************************************************************/
#include <stdio.h>  /* printf */
#include <stddef.h> /* size_t */

#include "sorted_list.h"

#define NON_EMPTY 0
#define EMPTY     1

#define LIST_SIZE 5

enum ilrd_status
{
	ILRD_SUCCESS = 0,
	ILRD_FAILURE = 1
};

static void TestSortedListCreateDestroy(void);
static void TestSortedListInsertGetData(void);
static void TestSortedListRemoveSizeIsEmpty(void);
static void TestSortedListBeginNextPrevEnd(void);
static void TestSortedListIsEqual(void);
static void TestSortedListFindAndFindIf(void);
static void TestSortedListForEach(void);
static void TestSortedListPopFrontBack(void);
static void TestSortedListMerge(void);
static void Test(size_t expected_res, size_t res, const char *test_name, 
                 const char *filename, size_t line_num);

int main(void)
{
	TestSortedListCreateDestroy();
	TestSortedListInsertGetData();
	TestSortedListRemoveSizeIsEmpty();
	TestSortedListBeginNextPrevEnd();
	TestSortedListIsEqual();
	TestSortedListFindAndFindIf();
	TestSortedListForEach();
	TestSortedListPopFrontBack();
	TestSortedListMerge();
	return 0;
}

/***** type functions *********************************************************/

static int cmp_func(const void *data, const void *param)
{	
	return *(int *)data - *(int *)param;
}

static int action(void *data, void *param)
{
	*(size_t *)data += *(size_t *)param;
	
	return ILRD_SUCCESS;
}

/***** TestSortedListCreateDestroy ********************************************/

static void TestSortedListCreateDestroy(void)
{
	sorted_list_ty *new_sl = SortedListCreate(cmp_func);
	
	Test(EMPTY, SortedListIsEmpty(new_sl), 
	     "TestSortedListCreateDestroy()", __FILE__, __LINE__);
	     
	SortedListDestroy(new_sl);
	
	printf("----------\n");
}

/***** TestSortedListInsert ***************************************************/

static void TestSortedListInsertGetData(void)
{
	sorted_list_ty *new_sl = SortedListCreate(cmp_func);
	sorted_list_iter_ty iter = {0};
	size_t elements[LIST_SIZE - 1] = {4, 1, 5, 2};
	size_t results[LIST_SIZE - 1] = {1, 2, 4, 5};
	size_t middle_param = 3;
	size_t start_param = 0;
	size_t i = 0;
	
	for( i = 0; i < LIST_SIZE - 1; ++i )
	{
		SortedListInsert(new_sl, &elements[i]);
	}
	
	iter = SortedListBegin(new_sl);
	
	for( i = 0; i < LIST_SIZE - 1; ++i )
	{
		Test(results[i], *(size_t *)SortedListGetData(iter), 
		     "TestSortedListInsert()", __FILE__, __LINE__);
		
		iter = SortedListNext(iter);
	}
	
	SortedListInsert(new_sl, &middle_param);
	SortedListInsert(new_sl, &start_param);
	
	iter = SortedListBegin(new_sl);
	
	for( i = 0; i < LIST_SIZE + 1; ++i )
	{
		if( i == 0 )
		{
			Test(start_param, *(size_t *)SortedListGetData(iter), 
		     "TestSortedListInsert()", __FILE__, __LINE__);
		}
		
		if( i == 3 )
		{
			Test(middle_param, *(size_t *)SortedListGetData(iter), 
		     "TestSortedListInsert()", __FILE__, __LINE__);
		}
		
		iter = SortedListNext(iter);
	}
	
	printf("TestSortedListGetData() success\n");
	
	SortedListDestroy(new_sl);
	
	printf("----------\n");
}

/***** TestSortedListRemoveSizeIsEmpty ****************************************/

static void TestSortedListRemoveSizeIsEmpty(void)
{
	sorted_list_ty *new_sl = SortedListCreate(cmp_func);
	size_t elements[LIST_SIZE] = {1, 2, 3, 4, 5};
	size_t i = 0;
	
	for( i = 0; i < LIST_SIZE; ++i )
	{
		SortedListInsert(new_sl, &elements[i]);
	}
	
	for( i = 0; i < LIST_SIZE; ++i )
	{
		Test(elements[LIST_SIZE - i - 1], SortedListSize(new_sl), 
		     "TestSortedListRemove()", __FILE__, __LINE__);
		     
		Test(elements[LIST_SIZE - i - 1], SortedListSize(new_sl), 
		     "TestSortedListSize()", __FILE__, __LINE__);
		     
		Test(NON_EMPTY, SortedListIsEmpty(new_sl), "TestSortedListIsEmpty()",
		     __FILE__, __LINE__);
		
		SortedListRemove(SortedListBegin(new_sl));
	}
	
	Test(EMPTY, SortedListIsEmpty(new_sl), "TestSortedListIsEmpty()", 
	     __FILE__, __LINE__);
	     
    SortedListDestroy(new_sl);
    
    printf("----------\n");
}

/***** TestSortedListBeginNextPrevEnd *****************************************/

static void TestSortedListBeginNextPrevEnd(void)
{
	sorted_list_ty *new_sl = SortedListCreate(cmp_func);
	sorted_list_iter_ty iter = {0};
	sorted_list_iter_ty end_iter = {0};
	size_t elements[LIST_SIZE] = {1, 2, 3, 4, 5};
	size_t i = 0;
	
	for( i = 0; i < LIST_SIZE; ++i )
	{
		SortedListInsert(new_sl, &elements[i]);
	}
	
	iter = SortedListBegin(new_sl);
	end_iter = SortedListEnd(new_sl);
	
	Test(elements[0], *(size_t *)SortedListGetData(iter), "TestSortedListBegin()", 
	     __FILE__, __LINE__);
	
	for( i = 0; i < LIST_SIZE - 1; ++i )
	{
		iter = SortedListNext(iter);
		
		Test(elements[i+1], *(size_t *)SortedListGetData(iter), 
		     "TestSortedListNext()", __FILE__, __LINE__);
		     
		if( i >= 1 )
		{
			iter = SortedListPrev(iter);
			
			Test(elements[i], *(size_t *)SortedListGetData(iter), 
			     "TestSortedListPrev()", __FILE__, __LINE__);
		     
		    iter = SortedListNext(iter);
		}
	}     
	
	if ( SortedListIsEqual(iter, SortedListPrev(end_iter)) )
	{
		printf("TestSortedListEnd() success\n");
	}
	
	else
	{
		printf("TestSortedListEnd fail\n");
	}
	
	SortedListDestroy(new_sl);
	
	printf("----------\n");
}

/***** TestSortedListIsEqual **************************************************/

static void TestSortedListIsEqual(void)
{
	sorted_list_ty *new_sl = SortedListCreate(cmp_func);
	sorted_list_iter_ty begin = {0};
	sorted_list_iter_ty end = {0};
	size_t element = 1;
	
	begin = SortedListBegin(new_sl);
	end = SortedListEnd(new_sl);
	
	if( SortedListIsEqual(begin, end) )
	{
		printf("SortedListIsEqual() success\n");
	}
	
	else
	{
		printf("SortedListIsEqual() fail in line 210\n)");
	}
	
	SortedListInsert(new_sl, &element);
	
	begin = SortedListBegin(new_sl);
	
	if( SortedListIsEqual(end, SortedListNext(begin)) )
	{
		printf("SortedListIsEqual() success\n");
	}
	
	else
	{
		printf("SortedListIsEqual() fail in line 224\n");
	}
	     
	SortedListDestroy(new_sl);
	
	printf("----------\n");
}

/***** TestSortedListFind *****************************************************/

static void TestSortedListFindAndFindIf(void)
{
	sorted_list_ty *new_sl = SortedListCreate(cmp_func);
	sorted_list_iter_ty begin = {0};
	sorted_list_iter_ty end = {0};
	size_t param = 3;
	size_t elements[LIST_SIZE] = {1, 2, 3, 4, 5};
	size_t i = 0;
	
	for( i = 0; i < LIST_SIZE; ++i )
	{
		SortedListInsert(new_sl, &elements[i]);
	}
	
	begin = SortedListBegin(new_sl);
	end = SortedListEnd(new_sl);
	
	Test(elements[2], *(size_t *)SortedListGetData(SortedListFind(new_sl, 
	     begin, end, &param)), "TestSortedListFindAndFindIf()", __FILE__, __LINE__);
	     
	Test(elements[2], *(size_t *)SortedListGetData(SortedListFind(new_sl, begin, 
	     SortedListNext(SortedListNext(begin)), &param)), 
	     "TestSortedListFindAndFindIf()", __FILE__, __LINE__);
	     
	SortedListDestroy(new_sl);
	
	printf("----------\n");
}

/***** SortedListForEach ******************************************************/

static void TestSortedListForEach(void)
{
	sorted_list_ty *new_sl = SortedListCreate(cmp_func);
	sorted_list_iter_ty begin = {0};
	sorted_list_iter_ty end = {0};
	size_t param = 3;
	size_t elements[LIST_SIZE] = {1, 2, 3, 4, 5};
	size_t i = 0;
	
	for( i = 0; i < LIST_SIZE; ++i )
	{
		SortedListInsert(new_sl, &elements[i]);
	}
	
	begin = SortedListBegin(new_sl);
	end = SortedListEnd(new_sl);
	
	Test(ILRD_SUCCESS, (size_t)SortedListForEach(begin, end, action, &param), 
	     "TestSortedListForEach()", __FILE__, __LINE__);
	     
	SortedListDestroy(new_sl);
	
	printf("----------\n");
}

/***** TestSortedListPopFrontBack *********************************************/

static void TestSortedListPopFrontBack(void)
{
	sorted_list_ty *new_sl = SortedListCreate(cmp_func);
	size_t elements[LIST_SIZE] = {1, 2, 3, 4, 5};
	size_t i = 0;
	size_t pop_front = 0;
	size_t pop_back = 0;
	
	for( i = 0; i < LIST_SIZE; ++i )
	{
		SortedListInsert(new_sl, &elements[i]);
	}
	
	pop_front = *(size_t *)SortedListPopFront(new_sl);
	
	Test(elements[1], *(size_t *)SortedListGetData(SortedListBegin(new_sl)),
	     "TestSortedListPopFront()", __FILE__, __LINE__);
	     
	Test(elements[0], pop_front, "TestSortedListPopFront()", __FILE__, __LINE__);
	
	pop_back = *(size_t *)SortedListPopBack(new_sl);
	
	Test(elements[LIST_SIZE - 2], *(size_t *)SortedListGetData(SortedListPrev(SortedListEnd(new_sl))),
	     "TestSortedListPopBack()", __FILE__, __LINE__);
	     
	Test(elements[LIST_SIZE - 1], pop_back, "TestSortedListPopBack()", 
	     __FILE__, __LINE__);
	     
	SortedListDestroy(new_sl);
	
	printf("----------\n");
}

/***** TestSortedListMerge ****************************************************/

static void TestSortedListMerge(void)
{
	sorted_list_ty *dest_list1 = SortedListCreate(cmp_func);
	sorted_list_ty *dest_list2 = SortedListCreate(cmp_func);
	sorted_list_ty *src_list1 = SortedListCreate(cmp_func);
	sorted_list_ty *src_list2 = SortedListCreate(cmp_func);
	sorted_list_iter_ty dest_iter1 = {0};
	sorted_list_iter_ty dest_iter2 = {0};
	size_t dest_elements1[LIST_SIZE] = {3, 6, 7, 9, 11};
	size_t dest_elements2[LIST_SIZE] = {3, 6, 7, 9, 15};
	size_t src_elements1[LIST_SIZE] = {2, 5, 10, 13, 14};
	size_t result1[2 * LIST_SIZE] = { 2, 3, 5, 6, 7, 9, 10, 11, 13, 14};
	size_t result2[2 * LIST_SIZE] = { 2, 3, 5, 6, 7, 9, 10, 13, 14, 15};
	size_t i = 0;
	
	for( i = 0; i < LIST_SIZE; ++i )
	{
		SortedListInsert(dest_list1, &dest_elements1[i]);
		SortedListInsert(dest_list2, &dest_elements2[i]);
		SortedListInsert(src_list1, &src_elements1[i]);
		SortedListInsert(src_list2, &src_elements1[i]);
	}
	
	SortedListMerge(dest_list1, src_list1);
	SortedListMerge(dest_list2, src_list2);
	
	dest_iter1 = SortedListBegin(dest_list1);
	dest_iter2 = SortedListBegin(dest_list2);
	
	for( i = 0; i < 2 * LIST_SIZE; ++i )
	{
		Test(result1[i], *(size_t *)SortedListGetData(dest_iter1), 
		     "SortedListMerge()", __FILE__, __LINE__);
		     
		Test(result2[i], *(size_t *)SortedListGetData(dest_iter2), 
		     "SortedListMerge()", __FILE__, __LINE__);
		     
		dest_iter1 = SortedListNext(dest_iter1);
		dest_iter2 = SortedListNext(dest_iter2);
	}
	
	Test(EMPTY, SortedListIsEmpty(src_list1), "SortedListMerge()", 
	     __FILE__, __LINE__);
	     
	Test(EMPTY, SortedListIsEmpty(src_list2), "SortedListMerge()", 
	     __FILE__, __LINE__);
	
	SortedListDestroy(dest_list1);
	SortedListDestroy(dest_list2);
	SortedListDestroy(src_list1);
	SortedListDestroy(src_list2);
	
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
