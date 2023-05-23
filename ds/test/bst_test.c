/*******************************************************************************
*  bst_test.c                                                                  *
*  Author: Ariel                                                               *
*  Reviewer: Eva                                                               *
*******************************************************************************/
#include <stddef.h> /* size_t */
#include <stdio.h>  /* printf */

#include "bst.h"

#define NON_EMPTY 0
#define EMPTY     1

#define EQUAL     1
#define NOT_EQUAL 0

#define TREE_MAX_SIZE 10

#define UNVALID_ADD 0XDEADBEAF

enum ilrd_status
{
	ILRD_SUCCESS = 0,
	ILRD_FAILURE = 1
};

static void Test(size_t expected_res, size_t res, const char *test_name, 
                 const char *filename, size_t line_num);
void TestBSTCreateIsEmpty(void);
void TestBSTInsertSizeDestroy(void);
void TestBSTBeginNextEnd(void);
void TestBSTPrevGetData(void);
void TestBSTFindIterIsEqual(void);
void TestBSTForEach(void);
void TestBSTRemove(void);

/***** type functions *********************************************************/

static int cmp_func(void *tree_data, void *new_data)
{
	return ((*(int *)new_data) - (*(int *)tree_data));
}

static int op(void *data, void *param)
{
	++*(int *)param;
	
	return ILRD_SUCCESS;
}

/******************************************************************************/

int main(void)
{
	TestBSTCreateIsEmpty();
	TestBSTInsertSizeDestroy();
	TestBSTBeginNextEnd();
	TestBSTPrevGetData();
	TestBSTFindIterIsEqual();
	TestBSTForEach();
	TestBSTRemove();
	return 0;
}

/***** TestBSTCreateIsEmpty ***************************************************/

void TestBSTCreateIsEmpty(void)
{
	bst_ty *new_bst = BSTCreate(cmp_func);
	int element = 0;
	
	Test(EMPTY, BSTIsEmpty(new_bst), "TestBSTCreateIsEmpty()", 
	                                                        __FILE__, __LINE__);
	     
	BSTInsert(new_bst, &element);
	
	Test(NON_EMPTY, BSTIsEmpty(new_bst), "TestBSTCreateIsEmpty()", 
	                                                        __FILE__, __LINE__);
	     
	BSTDestroy(new_bst);
	
	printf("----------\n");	
}

/***** TestBSTInsertSizeDestroy ***********************************************/

void TestBSTInsertSizeDestroy(void)
{
	bst_ty *new_bst = BSTCreate(cmp_func);
	int elements[TREE_MAX_SIZE] = {6, 2, 8, 0, 5, 3, 9, 4, 1, 7};
	size_t i = 0;
	
	for(i = 0; i < TREE_MAX_SIZE; ++i)
	{
		BSTInsert(new_bst, &elements[i]);
		Test(i+1, BSTSize(new_bst), "TestBSTInsertSizeDestroy()",
		                                                    __FILE__, __LINE__);
	}
	
	BSTDestroy(new_bst);
	
	printf("----------\n");
}

/***** TestBSTBeginNextEnd ************************************************/

void TestBSTBeginNextEnd(void)
{
	bst_ty *new_bst = BSTCreate(cmp_func);
	bst_iter_ty iter = NULL;
	bst_iter_ty end_iter = NULL;
	int elements[TREE_MAX_SIZE] = {6, 2, 8, 0, 5, 3, 9, 4, 1, 7};
	int sorted_elements[TREE_MAX_SIZE] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
	size_t i = 0;
	
	for(i = 0; i < TREE_MAX_SIZE; ++i)
	{
		BSTInsert(new_bst, &elements[i]);
	}
	
	iter = BSTBegin(new_bst);
	end_iter = BSTEnd(new_bst);
	
	Test(sorted_elements[0], *(int *)BSTGetData(iter), "TestBSTBegin()", 
	                                                        __FILE__, __LINE__);
	                                                        
	for(i = 1; i < TREE_MAX_SIZE; ++i)
	{
		iter = BSTNext(iter);
		
		Test(sorted_elements[i], *(int *)BSTGetData(iter), "TestBSTNext()", 
	                                                        __FILE__, __LINE__);
	}                                                        
     
    iter = BSTNext(iter);
    
    if(iter == end_iter)
    {
    	printf("TestBSTEnd() Success\n");
    }
    
    else
    {
    	printf("TestBSTEnd() fail\n");
    }
                                                  
	BSTDestroy(new_bst);
	
	printf("----------\n");
}

/***** TestBSTPrev ************************************************************/

void TestBSTPrevGetData(void)
{
	bst_ty *new_bst = BSTCreate(cmp_func);
	bst_iter_ty iter = NULL;
	bst_iter_ty end_iter = NULL;
	int elements[TREE_MAX_SIZE] = {6, 2, 8, 0, 5, 3, 9, 4, 1, 7};
	int sorted_elements[TREE_MAX_SIZE] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
	size_t i = 0;
	
	for(i = 0; i < TREE_MAX_SIZE; ++i)
	{
		BSTInsert(new_bst, &elements[i]);
	}
	
	iter = BSTBegin(new_bst);
	end_iter = BSTEnd(new_bst);
	                                                        
	for(i = 1; i < TREE_MAX_SIZE; ++i)
	{
		iter = BSTNext(iter);
	}
	
	for(i = TREE_MAX_SIZE - 1; i > 0; --i)
	{
		iter = BSTPrev(iter);
		
		Test(sorted_elements[i-1], *(int *)BSTGetData(iter), 
		                            "TestBSTPrevGetData()", __FILE__, __LINE__);	
	}                                                        
     
    iter = BSTPrev(iter);
    
    if(iter == end_iter)
    {
    	printf("TestBSTPrevGetData() Success\n");
    }
    
    else
    {
    	printf("TestBSTPrevGetData() fail\n");
    }
                                                  
	BSTDestroy(new_bst);
	
	printf("----------\n");	
}

/***** TestBSTFindIterIsEqual *************************************************/

void TestBSTFindIterIsEqual(void)
{
	bst_ty *new_bst = BSTCreate(cmp_func);
	bst_iter_ty iter = NULL;
	bst_iter_ty end_iter = NULL;
	bst_iter_ty ret_iter = NULL;
	int elements[TREE_MAX_SIZE] = {6, 2, 8, 0, 5, 3, 9, 4, 1, 7};
	int non_exist_element = 10;
	size_t i = 0;
	
	for(i = 0; i < TREE_MAX_SIZE; ++i)
	{
		BSTInsert(new_bst, &elements[i]);
	}
	
	iter = BSTBegin(new_bst);
	end_iter = BSTEnd(new_bst);	
	
	ret_iter = BSTFind(new_bst, &elements[3]);
	
	Test(EQUAL, BSTIterIsEqual(iter, ret_iter), "TestBSTFind()", 
	                                                        __FILE__, __LINE__);
	                                                        
	iter = BSTNext(iter);
	
	ret_iter = BSTFind(new_bst, &elements[8]);
	
	Test(EQUAL, BSTIterIsEqual(iter, ret_iter), "TestBSTIterIsEqual()", 
	                                                        __FILE__, __LINE__);
	                                                        
	iter = BSTPrev(BSTPrev(iter));
	
	ret_iter = BSTFind(new_bst, &non_exist_element);
	
	if((ret_iter == iter) && (ret_iter == end_iter))
	{
		printf("TestBSTFind() Success\n");
	}
	
	else
	{
		printf("TestBSTFind fail\n");
	}
	                                                                   
	BSTDestroy(new_bst);
	
	printf("----------\n");
}

/***** TestBSTForEach *********************************************************/

void TestBSTForEach(void)
{
	bst_ty *new_bst = BSTCreate(cmp_func);
	bst_iter_ty from = NULL;
	bst_iter_ty to = NULL;
	int elements[TREE_MAX_SIZE] = {6, 2, 8, 0, 5, 3, 9, 4, 1, 7};
	size_t i = 0;
	static int op_counter = 0;
	
	for(i = 0; i < TREE_MAX_SIZE; ++i)
	{
		BSTInsert(new_bst, &elements[i]);
	}
	
	from = BSTBegin(new_bst);
	to = BSTEnd(new_bst);
	
	BSTForEach(from, to, op, &op_counter);
	
	Test(TREE_MAX_SIZE, op_counter, "TestBSTForEach()", __FILE__, __LINE__);
	
	BSTDestroy(new_bst);
	
	printf("----------\n");
}

/***** TestBSTRemove **********************************************************/

void TestBSTRemove(void)
{
	bst_ty *new_bst = BSTCreate(cmp_func);
	bst_iter_ty begin_iter = NULL;
	bst_iter_ty iter = NULL;
	int elements[TREE_MAX_SIZE] = {6, 2, 8, 0, 5, 3, 9, 4, 1, 7};
	int sorted_elements[TREE_MAX_SIZE - 1] = {0, 1, 2, 3, 4, 5, 7, 8, 9};
	size_t i = 0;
	size_t bst_size = TREE_MAX_SIZE;
	
	for(i = 0; i < TREE_MAX_SIZE; ++i)
	{
		BSTInsert(new_bst, &elements[i]);
	}	
	
	begin_iter = BSTBegin(new_bst);
	iter = begin_iter;
	
	for(i = 0; i < 6; ++i)
	{
		iter = BSTNext(iter);
	}
	
	BSTRemove(iter);
	--bst_size;
	
	Test(bst_size, BSTSize(new_bst), "TestBSTRemove()", __FILE__, __LINE__);
	
	begin_iter = BSTBegin(new_bst);
	
	for(i = 0; i < TREE_MAX_SIZE - 2; ++i)
	{	
		BSTRemove(begin_iter);
		--bst_size;
		
		begin_iter = BSTBegin(new_bst);
		
		Test(sorted_elements[i+1], *(int *)BSTGetData(begin_iter), 
		                                 "TestBSTRemove()", __FILE__, __LINE__);
		                                 
		Test(bst_size, BSTSize(new_bst), "TestBSTRemove()", __FILE__, __LINE__);
	}
	
	BSTDestroy(new_bst);
	
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
