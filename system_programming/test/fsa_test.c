/*******************************************************************************
*  fixed_size_allocator_test.c                                                 *
*  Author: Ariel                                                               *
*  Reviewer: Eli                                                               *
*******************************************************************************/
#include <stddef.h> /* size_t       */
#include <stdlib.h> /* malloc, free */
#include <stdio.h>  /* printf       */

#include "fsa.h"

#define WORD_SIZE sizeof(size_t)

#define FSA_SIZE 40

void TestFSAInit(void);
void TestFSAAllocFreeBlocks(char *func_name);
void TestFSAFree(void);
void TestFSASuggestedSize(void);
static void Test(size_t expected_res, size_t res, const char *test_name, 
                 const char *filename, size_t line_num);

int main(void)
{
	TestFSAInit();
	TestFSAAllocFreeBlocks("TestFSAAlloc()");
	TestFSAAllocFreeBlocks("TestFSAFreeBlocks()");
	TestFSAFree();
	TestFSASuggestedSize();
	return 0;
}

/***** FSAInit ****************************************************************/

void TestFSAInit(void)
{
	fsa_ty *new_fsa1 = NULL;
	fsa_ty *new_fsa2 = NULL;
	fsa_ty *new_fsa3 = NULL;
	
	size_t *memory_fsa1 = (size_t *)malloc(FSA_SIZE);
	size_t *memory_fsa2 = NULL;
	size_t *memory_fsa3 = NULL;
	
	if( !memory_fsa1 ) 
	{
		return;
	}

	new_fsa1 = FSAInit((void *)memory_fsa1, FSA_SIZE, 8);
	
	Test(4, FSAFreeBlocks(new_fsa1), "TestFSAInit()", __FILE__, __LINE__);
	
	memory_fsa2 = (size_t *)malloc(FSA_SIZE);
	
	if( !memory_fsa2 ) 
	{
		free(memory_fsa1);
		memory_fsa1 = NULL;
		return;
	}
	
	new_fsa2 = FSAInit((void *)memory_fsa2, FSA_SIZE, 12);
	
	Test(2, FSAFreeBlocks(new_fsa2), "TestFSAInit()", __FILE__, __LINE__);
	
	memory_fsa3 = (size_t *)malloc(FSA_SIZE);
	
	if( !memory_fsa3 ) 
	{
		free(memory_fsa1);
		memory_fsa1 = NULL;
		
		free(memory_fsa2);
		memory_fsa2 = NULL;
		return;
	}
	
	new_fsa3 = FSAInit((void *)memory_fsa3, FSA_SIZE + WORD_SIZE, FSA_SIZE);
	
	Test(1, FSAFreeBlocks(new_fsa3), "TestFSAInit()", __FILE__, __LINE__);
	
	free(memory_fsa1);
	memory_fsa1 = NULL;
	
	free(memory_fsa2);
	memory_fsa2 = NULL;
	
	free(memory_fsa3);
	memory_fsa3 = NULL;
	
	printf("----------\n");
}

/***** TestFSAAlloc ***********************************************************/

void TestFSAAllocFreeBlocks(char *func_name)
{
	fsa_ty *new_fsa = NULL;
	size_t free_blocks[4] = {4, 3, 2, 1};
	size_t i = 0;
	
	size_t *memory_fsa = (size_t *)malloc(FSA_SIZE);
	
	if( !memory_fsa ) {return;}
	
	new_fsa = FSAInit((void *)memory_fsa, FSA_SIZE, 8);
	
	for( i = 0; i < 4; ++i )
	{
		Test(free_blocks[i], FSAFreeBlocks(new_fsa), func_name, __FILE__,
		     __LINE__);
		     
		FSAAlloc(new_fsa);
	}
	
	free(memory_fsa);
	memory_fsa = NULL;
	
	printf("----------\n");
}

/***** TestFSAFree ************************************************************/

void TestFSAFree(void)
{
	fsa_ty *new_fsa = NULL;
	void *address1 = NULL;
	void *address2 = NULL;
	void *address3 = NULL;
	void *address4 = NULL;
	size_t free_blocks[4] = {1, 2, 3, 4};
	
	size_t *memory_fsa = (size_t *)malloc(FSA_SIZE);
	
	if( !memory_fsa ) {return;}
	
	new_fsa = FSAInit((void *)memory_fsa, FSA_SIZE, 8);
	
	address1 = FSAAlloc(new_fsa);
	address2 = FSAAlloc(new_fsa);
	address3 = FSAAlloc(new_fsa);
	address4 = FSAAlloc(new_fsa);
	
	FSAFree(new_fsa, address3);
	Test(free_blocks[0], FSAFreeBlocks(new_fsa), "TestFSAFree()", __FILE__,
		 __LINE__);
		 
	FSAFree(new_fsa, address2);
	Test(free_blocks[1], FSAFreeBlocks(new_fsa), "TestFSAFree()", __FILE__,
		 __LINE__);
		 
	FSAFree(new_fsa, address4);
	Test(free_blocks[2], FSAFreeBlocks(new_fsa), "TestFSAFree()", __FILE__,
		 __LINE__);
		 
	FSAFree(new_fsa, address1);
	Test(free_blocks[3], FSAFreeBlocks(new_fsa), "TestFSAFree()", __FILE__,
		 __LINE__);

	free(memory_fsa);
	memory_fsa = NULL;
	
	printf("----------\n");
}

/***** TestFSASuggestedSize ***************************************************/

void TestFSASuggestedSize(void)
{
	size_t block_size[5] = {4, 12, 16, 20, 31};
	size_t num_of_blocks[5] = {10, 6, 1, 20, 50};
	size_t suggested_size[5] = {88, 104, 24, 488, 1608};
	size_t i = 0;
	
	for( i = 0; i < 5; ++i )
	{
		Test(suggested_size[i], FSASuggestedSize(block_size[i], num_of_blocks[i]),
		     "TestFSASuggestedSize()", __FILE__, __LINE__);
	}
	
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

