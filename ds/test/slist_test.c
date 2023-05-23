/*******************************************************************************
*  slist_test.c                                                                *
*  Author: Ariel                                                               *
*  Reviewer: Nisan                                                             *
*******************************************************************************/
#include <stdio.h>  /* printf */
#include <stddef.h> /* size_t */

#include "../include/slist.h"

#define NON_EMPTY 0
#define EMPTY     1

#define LIST_SIZE 5

enum status
{
	SUCCESS = 0,
	FAILURE = 1
};

static void TestSlistCreateDestroy(void);
static void TestSlistInsert(void);
static void TestSlistRemoveCountIsEmpty(void);
static void TestSlistBeginNextEnd(void);
static void TestSlistGetSetData(void);
static void TestSlistIsEqual(void);
static void TestSlistFind(void);
static bool_ty match(const void *data, void *param);
static void TestSlistForEach(void);
static int action(void *data, void *param);
static void TestSlistMerge(void);
static void Test(size_t expected_res, size_t res, const char *test_name, 
                 const char *filename, size_t line_num);

/****** Main ******************************************************************/

int main(void)
{
	TestSlistCreateDestroy();
	printf("----------\n");
	TestSlistInsert();
	printf("----------\n");
	TestSlistRemoveCountIsEmpty();
	printf("----------\n");
	TestSlistBeginNextEnd();
	printf("----------\n");
	TestSlistGetSetData();
	printf("----------\n");
	TestSlistIsEqual();
	printf("----------\n");
	TestSlistFind();
	printf("----------\n");
	TestSlistForEach();
	printf("----------\n");
	TestSlistMerge();
	return 0;
}

/******* TestSlistCreateDestroy ***********************************************/

static void TestSlistCreateDestroy(void)
{
	slist_ty *new_slist = SlistCreate();
	
	Test(EMPTY, SlistIsEmpty(new_slist), 
	     "TestSlistCreateDestroy()", __FILE__, __LINE__);
	
	SlistDestroy(new_slist);
	
}

/******* TestSlistInsert ******************************************************/

static void TestSlistInsert(void)
{
	slist_ty *new_slist = SlistCreate();
	slist_iter_ty iter = NULL;
	size_t elements[LIST_SIZE] = {1, 2, 3, 4, 5};
	size_t i = 0;
	
	for( i = 0; i < LIST_SIZE; ++i )
	{
		SlistInsert(&elements[i], SlistEnd(new_slist));
	}
	
	iter = SlistBegin(new_slist);
	
	for( i = 0; i < LIST_SIZE; ++i )
	{
		Test(elements[i], *(size_t *)SlistGetData(iter), "TestSlistInsert()",
		     __FILE__, __LINE__);
		
		iter = SlistNext(iter);
	}
	
	SlistDestroy(new_slist);
}

/******* TestSlistRemoveCountIsEmpty ******************************************************/

static void TestSlistRemoveCountIsEmpty(void)
{
	slist_ty *new_slist = SlistCreate();
	size_t elements[LIST_SIZE] = {1, 2, 3, 4, 5};
	size_t i = 0;
	
	for( i = 0; i < LIST_SIZE; ++i )
	{
		SlistInsert(&elements[i], SlistEnd(new_slist));
	}
	
	for( i = 0; i < LIST_SIZE; ++i )
	{
		Test(elements[LIST_SIZE - i - 1], SlistCount(new_slist), 
		     "TestSlistRemoveCountIsEmpty()", __FILE__, __LINE__);
		     
		Test(elements[LIST_SIZE - i - 1], SlistCount(new_slist), 
		     "TestSlistCount()", __FILE__, __LINE__);
		     
		Test(NON_EMPTY, SlistIsEmpty(new_slist), "TestSlistIsEmpty()",
		     __FILE__, __LINE__);
		
		SlistRemove(SlistBegin(new_slist));
	}
	
	Test(EMPTY, SlistIsEmpty(new_slist), "TestSlistIsEmpty()", 
	     __FILE__, __LINE__);
	
	SlistDestroy(new_slist);
}

/******* TestSlistBeginNextEnd *******************************************************/

static void TestSlistBeginNextEnd(void)
{
	slist_ty *new_slist = SlistCreate();
	slist_iter_ty iter = NULL;
	size_t elements[LIST_SIZE] = {1, 2, 3, 4, 5};
	size_t i = 0;
	
	for( i = 0; i < LIST_SIZE; ++i )
	{
		SlistInsert(&elements[i], SlistEnd(new_slist));
	}
	
	iter = SlistBegin(new_slist);
	
	Test(elements[0], *(size_t *)SlistGetData(iter), "TestSlistBegin()", 
	     __FILE__, __LINE__);
	
	for( i = 0; i < LIST_SIZE - 1; ++i )
	{
		
		iter = SlistNext(iter);
		
		Test(elements[i+1], *(size_t *)SlistGetData(iter), "TestSlistNext()",
		     __FILE__, __LINE__);
	}     
	
	if ( (LIST_SIZE == *(size_t *)SlistGetData(iter)) && SlistNext(iter) )
	{
		printf("TestSlistEnd() Success\n");
	}
	
	SlistDestroy(new_slist);
}

/****** TestSlistGetSetData ***************************************************/

static void TestSlistGetSetData(void)
{
	slist_ty *new_slist = SlistCreate();
	slist_iter_ty iter = NULL;
	size_t elements[LIST_SIZE] = {1, 2, 3, 4, 5};
	size_t set_elements[LIST_SIZE] = {6, 7, 8, 9 ,10};
	size_t i = 0;
	
	for( i = 0; i < LIST_SIZE; ++i )
	{
		SlistInsert(&elements[i], SlistEnd(new_slist));
	}
	
	iter = SlistBegin(new_slist);
	
	for( i = 0; i < LIST_SIZE; ++i )
	{
		Test(elements[i], *(size_t *)SlistGetData(iter), "TestSlistGetdata()",
		     __FILE__, __LINE__);
		
		iter = SlistNext(iter);
	}
	
	iter = SlistBegin(new_slist);
	
	for( i = 0; i < LIST_SIZE; ++i )
	{
		SlistSetData(iter, &set_elements[i]);
		Test(set_elements[i], *(size_t *)SlistGetData(iter), 
		     "TestSlistSetData()", __FILE__, __LINE__);
		     
		iter = SlistNext(iter);
	}
	
	SlistDestroy(new_slist);
}

/****** TestSlistIsEqual ******************************************************/

static void TestSlistIsEqual(void)
{
	slist_ty *new_slist = SlistCreate();
	slist_iter_ty begin = NULL;
	size_t element = 1;
	
	begin = SlistBegin(new_slist);
	
	SlistInsert(&element, SlistEnd(new_slist));
	
	Test((size_t)SlistEnd(new_slist), (size_t)SlistNext(begin), 
	     "TestSlistIsEqual()", __FILE__, __LINE__);
	     
	SlistDestroy(new_slist);
}

/******** TestSlistFind *******************************************************/

static void TestSlistFind(void)
{
	slist_ty *new_slist = SlistCreate();
	slist_iter_ty begin = NULL;
	slist_iter_ty end = NULL;
	size_t param = 3;
	size_t elements[LIST_SIZE] = {1, 2, 3, 4, 5};
	size_t i = 0;
	
	for( i = 0; i < LIST_SIZE; ++i )
	{
		SlistInsert(&elements[i], SlistEnd(new_slist));
	}
	
	begin = SlistBegin(new_slist);
	end = SlistEnd(new_slist);
	
	Test(elements[2], *(size_t *)SlistGetData(SlistFind(begin, end, match, &param)),
	     "TestSlistFind()", __FILE__, __LINE__);
	     
	Test(elements[2], *(size_t *)SlistGetData(SlistFind(begin, SlistNext(SlistNext(begin)), match, &param)), 
	     "TestSlistFind()", __FILE__, __LINE__);
	     
	SlistDestroy(new_slist);
}

/* match function to use inside SlistFind */
static bool_ty match(const void *data, void *param)  
{
	return *(size_t *)data == *(size_t *)param;
}

/******* TestSlistForEach *****************************************************/

static void TestSlistForEach(void)
{
	slist_ty *new_slist = SlistCreate();
	slist_iter_ty begin = NULL;
	slist_iter_ty end = NULL;
	size_t param = 3;
	size_t elements[LIST_SIZE] = {1, 2, 3, 4, 5};
	size_t i = 0;
	
	for( i = 0; i < LIST_SIZE; ++i )
	{
		SlistInsert(&elements[i], SlistEnd(new_slist));
	}
	
	begin = SlistBegin(new_slist);
	end = SlistEnd(new_slist);
	
	Test(SUCCESS, (size_t)SlistForEach(begin, end, action, &param), 
	     "TestSlistForEach()", __FILE__, __LINE__);
	     
	SlistDestroy(new_slist);
}

static int action(void *data, void *param)
{
	*(size_t *)data += *(size_t *)param;
	
	return SUCCESS;
}

/******* TestSlistMerge *******************************************************/

static void TestSlistMerge(void)
{
	slist_ty *dst_slist = SlistCreate();
	slist_ty *src_slist = SlistCreate();
	slist_iter_ty iter = NULL;
	
	size_t dst_elements[LIST_SIZE] = {1, 2, 3, 4, 5};
	size_t src_elements[LIST_SIZE] = {6, 7, 8, 9, 10};
	size_t res_elements[2*LIST_SIZE] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
	size_t i = 0;
	
	for( i = 0; i < LIST_SIZE; ++i )
	{
		SlistInsert(&dst_elements[i], SlistEnd(dst_slist));
		SlistInsert(&src_elements[i], SlistEnd(src_slist));
	}
	
	SlistMerge(dst_slist, src_slist);
	
	Test(2 * LIST_SIZE, SlistCount(dst_slist), "TestSlistMerge()", 
	     __FILE__, __LINE__);
	Test(0, SlistCount(src_slist), "TestSlistMerge()", __FILE__, __LINE__);
	
	iter = SlistBegin(dst_slist);
	
	for( i = 0; i < 2 * LIST_SIZE; ++i )
	{
		Test(res_elements[i], *(size_t *)SlistGetData(iter), 
		     "TestSlistMerge()", __FILE__, __LINE__);
		iter = SlistNext(iter);
	}
	
	SlistDestroy(dst_slist);
	SlistDestroy(src_slist);
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
