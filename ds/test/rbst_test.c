/*******************************************************************************
*  rbst_test.c                                                                 *
*  Author: Ariel                                                               *
*  Reviewer: Nisan                                                             *
*******************************************************************************/
#include <stddef.h> /* size_t */
#include <stdio.h>  /* printf */

#include "rbst.h"

#define NON_EMPTY 0
#define EMPTY     1

#define TREE_MAX_SIZE 10

struct node
{
    void *data;
    size_t height;
    node_ty *children[2];
};
 
struct rbst
{
    node_ty *root;
    cmp_func_ty cmp_func;
};

enum ilrd_status
{
	ILRD_SUCCESS = 0,
	ILRD_FAILURE = 1
};

static void Test(size_t expected_res, size_t res, const char *test_name, 
                 const char *filename, size_t line_num);
void TestRBSTCreateIsEmpty(void);
void TestRBSTInsertSizeHeightDestroy(void);
void TestRBSTFind(void);
void TestRBSTForEach(void);
void TestRBSTRemove(void);
                 
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

static int op_fail(void *data, void *param)
{
	return ILRD_FAILURE;
}

/******************************************************************************/

int main(void)
{
	TestRBSTCreateIsEmpty();
	TestRBSTInsertSizeHeightDestroy();
	TestRBSTFind();
	TestRBSTForEach();
	TestRBSTRemove();
	return 0;
}

/***** TestRBSTCreateIsEmpty **************************************************/

void TestRBSTCreateIsEmpty(void)
{
	rbst_ty *new_rbst = RBSTCreate(cmp_func);
	int element = 0;
	
	Test(EMPTY, RBSTIsEmpty(new_rbst), "TestRBSTCreateIsEmpty()", 
	                                                        __FILE__, __LINE__);
	RBSTInsert(new_rbst, &element);
	
	Test(NON_EMPTY, RBSTIsEmpty(new_rbst), "TestRBSTCreateIsEmpty()", 
	                                                        __FILE__, __LINE__);        
	RBSTDestroy(new_rbst);
	
	printf("----------\n");	
}

/***** TestRBSTInsertSizeHeightDestroy ****************************************/

void TestRBSTInsertSizeHeightDestroy(void)
{
	rbst_ty *new_rbst = RBSTCreate(cmp_func);
	int new_elements[TREE_MAX_SIZE - 1] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
	size_t i = 0;
	
	for(i = 0; i < TREE_MAX_SIZE - 1; ++i)
	{
		RBSTInsert(new_rbst, &new_elements[i]);
		Test(i+1, RBSTSize(new_rbst), "TestRBSTInsertSizeHeightDestroy()",
		                                                    __FILE__, __LINE__);
	}
		                                                    
	/*Test(4, RBSTHeight(new_rbst), "TestRBSTInsertSizeHeightDestroy()",
		                                                    __FILE__, __LINE__);*/
		                                                    
	printf("The Height of the tree: %ld\n", RBSTHeight(new_rbst));
	printf("Tree: \n");
	printf("%d\n", *(int *)new_rbst->root->data);
	printf("%d\n", *(int *)new_rbst->root->children[1]->data);
	
	printf("%d\n", *(int *)new_rbst->root->children[1]->children[1]->data);
	
	printf("%d\n", *(int *)new_rbst->root->children[1]->children[1]->children[1]->data);
	
	printf("%d\n", *(int *)new_rbst->root->children[1]->children[0]->data);
	
	printf("%d\n", *(int *)new_rbst->root->children[1]->children[1]->children[0]->data);
	
	printf("\n");
	printf("%d\n", *(int *)new_rbst->root->children[0]->data);
	
	printf("%d\n", *(int *)new_rbst->root->children[0]->children[0]->data);
	
	printf("%d\n", *(int *)new_rbst->root->children[0]->children[1]->data);
	
	RBSTDestroy(new_rbst);
	
	printf("----------\n");
}

/***** TestRBSTRemove *********************************************************/

void TestRBSTRemove(void)
{
	rbst_ty *new_rbst = RBSTCreate(cmp_func);
	int elements[TREE_MAX_SIZE-1] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
	size_t i = 0;
	
	for(i = 0; i < TREE_MAX_SIZE-1; ++i)
	{
		RBSTInsert(new_rbst, &elements[i]);
	}
	
	RBSTRemove(new_rbst, &elements[3]);
	
	Test(8, RBSTSize(new_rbst), "TestRBSTRemove()", __FILE__, __LINE__);
	
	printf("Tree size after removing first node: %ld\n", RBSTSize(new_rbst));
	
	printf("Tree: \n");
	printf("%d\n", *(int *)new_rbst->root->data);
	printf("%d\n", *(int *)new_rbst->root->children[1]->data);
	
	printf("%d\n", *(int *)new_rbst->root->children[1]->children[1]->data);
	
	printf("%d\n", *(int *)new_rbst->root->children[1]->children[0]->data);
	
	printf("%d\n", *(int *)new_rbst->root->children[1]->children[0]->children[1]->data);
	
	printf("\n");
	printf("%d\n", *(int *)new_rbst->root->children[0]->data);
	
	printf("%d\n", *(int *)new_rbst->root->children[0]->children[0]->data);
	
	printf("%d\n", *(int *)new_rbst->root->children[0]->children[1]->data);
	
	printf("----------\n");
	
	RBSTRemove(new_rbst, &elements[0]);
	
	Test(7, RBSTSize(new_rbst), "TestRBSTRemove()", __FILE__, __LINE__);
	
	printf("Tree size after removing second node: %ld\n", RBSTSize(new_rbst));
	
	printf("Tree: \n");
	printf("%d\n", *(int *)new_rbst->root->data);
	printf("%d\n", *(int *)new_rbst->root->children[1]->data);
	
	printf("%d\n", *(int *)new_rbst->root->children[1]->children[1]->data);
	
	printf("%d\n", *(int *)new_rbst->root->children[1]->children[0]->data);
	
	printf("%d\n", *(int *)new_rbst->root->children[1]->children[0]->children[1]->data);
	
	printf("\n");
	printf("%d\n", *(int *)new_rbst->root->children[0]->data);
	
	printf("%d\n", *(int *)new_rbst->root->children[0]->children[1]->data);
	
	printf("----------\n");
	
	RBSTRemove(new_rbst, &elements[1]);
	
	Test(6, RBSTSize(new_rbst), "TestRBSTRemove()", __FILE__, __LINE__);
	
	printf("Tree size after removing third node: %ld\n", RBSTSize(new_rbst));
	
	printf("Tree: \n");
	printf("%d\n", *(int *)new_rbst->root->data);
	printf("%d\n", *(int *)new_rbst->root->children[1]->data);
	
	printf("%d\n", *(int *)new_rbst->root->children[1]->children[1]->data);
	
	printf("%d\n", *(int *)new_rbst->root->children[1]->children[0]->data);
	
	printf("\n");
	printf("%d\n", *(int *)new_rbst->root->children[0]->data);
	
	printf("%d\n", *(int *)new_rbst->root->children[0]->children[0]->data);
	
	printf("----------\n");
	
	RBSTRemove(new_rbst, &elements[4]);
	
	Test(5, RBSTSize(new_rbst), "TestRBSTRemove()", __FILE__, __LINE__);
	
	printf("Tree size after removing fourth node: %ld\n", RBSTSize(new_rbst));
	
	printf("Tree: \n");
	printf("%d\n", *(int *)new_rbst->root->data);
	printf("%d\n", *(int *)new_rbst->root->children[1]->data);
	
	printf("%d\n", *(int *)new_rbst->root->children[1]->children[1]->data);
	
	printf("%d\n", *(int *)new_rbst->root->children[1]->children[0]->data);
	
	printf("\n");
	printf("%d\n", *(int *)new_rbst->root->children[0]->data);
	                  
	RBSTDestroy(new_rbst);
	
	printf("----------\n");
}

/***** TestRBSTFind ***********************************************************/

void TestRBSTFind(void)
{
	rbst_ty *new_rbst = RBSTCreate(cmp_func);
	int elements[TREE_MAX_SIZE] = {6, 2, 8, 0, 5, 3, 9, 4, 1, 7};
	size_t i = 0;
	
	for(i = 0; i < TREE_MAX_SIZE; ++i)
	{
		RBSTInsert(new_rbst, &elements[i]);
	}
	
	Test(0, *(int *)(RBSTFind(new_rbst, &elements[3])), "TestRBSTFind()", 
	                                                        __FILE__, __LINE__);
	                                                        
	RBSTDestroy(new_rbst);
	
	printf("----------\n");
}

/***** TestRBSTForEach ********************************************************/

void TestRBSTForEach(void)
{
	rbst_ty *new_rbst = RBSTCreate(cmp_func);
	int elements[TREE_MAX_SIZE] = {6, 2, 8, 0, 5, 3, 9, 4, 1, 7};
	size_t i = 0;
	static int op_counter = 0;
	int for_each_res = 0;
	
	for(i = 0; i < TREE_MAX_SIZE; ++i)
	{
		RBSTInsert(new_rbst, &elements[i]);
	}
	
	for_each_res = RBSTForEach(new_rbst, op, &op_counter, POST_ORDER);
	
	Test(TREE_MAX_SIZE, op_counter, "TestRBSTForEach()", __FILE__, __LINE__);
	Test(ILRD_SUCCESS, for_each_res, "TestRBSTForEach()", __FILE__, __LINE__);
	
	for_each_res = RBSTForEach(new_rbst, op_fail, &op_counter, IN_ORDER);
	
	Test(ILRD_FAILURE, for_each_res, "TestRBSTForEach()", __FILE__, __LINE__);
	
	RBSTDestroy(new_rbst);
	
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
