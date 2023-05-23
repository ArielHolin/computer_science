/*******************************************************************************
*  vsa_test.c                                                                  *
*  Author: Ariel                                                               *
*  Reviewer: Doron                                                             *
*******************************************************************************/
#include <stddef.h> /* size_t       */
#include <stdio.h>  /* printf       */
#include <stdlib.h> /* malloc, free */

#include "vsa.h"

#ifndef NDEBUG
#define VSA_SIZE 16
#else
#define VSA_SIZE 8 
#endif

void TestVSAInit(void);
void TestVSAAllocFreeLargestFreeBlock(void);
static void Test(size_t expected_res, size_t res, const char *test_name, 
                 const char *filename, size_t line_num);

int main(void)
{
	TestVSAInit();
	TestVSAAllocFreeLargestFreeBlock();
	return 0;
}

/***** TestVSAInit ************************************************************/

void TestVSAInit(void)
{
	vsa_ty *new_vsa1 = NULL;
	vsa_ty *new_vsa2 = NULL;
	vsa_ty *new_vsa3 = NULL;
	
	long *memory_vsa1 = (long *)malloc(100);
	long *memory_vsa2 = NULL;
	long *memory_vsa3 = NULL;
	
	if( !memory_vsa1 )
	{
		return;
	}
	
	new_vsa1 = VSAInit(memory_vsa1, 100);
	
	Test(96 - (2 * VSA_SIZE), VSALargestFreeBlock(new_vsa1), "TestVSAInit()", 
	     __FILE__, __LINE__);
	
	memory_vsa2 = (long *)malloc(2 * VSA_SIZE);
	
	if( !memory_vsa2 )
	{
		free(memory_vsa1);
		memory_vsa1 = NULL;
		
		return;
	}
	
	new_vsa2 = VSAInit(memory_vsa2, 2 * VSA_SIZE);
	
	Test(0 * VSA_SIZE, VSALargestFreeBlock(new_vsa2), "TestVSAInit()", 
	     __FILE__, __LINE__);
	
	memory_vsa3 = (long *)malloc(3 * VSA_SIZE);
	
	if( !memory_vsa3 )
	{
		free(memory_vsa1);
		memory_vsa1 = NULL;
		
		free(memory_vsa2);
		memory_vsa2 = NULL;
		
		return;
	}
	
	new_vsa3 = VSAInit(memory_vsa3, 3 * VSA_SIZE);
	
	Test(1 * VSA_SIZE, VSALargestFreeBlock(new_vsa3), "TestVSAInit()", 
	     __FILE__, __LINE__);
	
	free(memory_vsa1);
	memory_vsa1 = NULL;
	
	free(memory_vsa2);
	memory_vsa2 = NULL;
	
	free(memory_vsa3);
	memory_vsa3 = NULL;
	
	printf("----------\n");
}

/***** TestVSAAlloc ***********************************************************/

void TestVSAAllocFreeLargestFreeBlock(void) 
{
	vsa_ty *new_vsa = NULL;
	void *address1 = NULL;
	void *address2 = NULL;
	void *address3 = NULL;
	void *address4 = NULL;
	
	long *memory_vsa = (long *)malloc(200 + (2 * VSA_SIZE));
	
	if( !memory_vsa )
	{
		return;
	}
	
	new_vsa = VSAInit(memory_vsa, 100 + (2 * VSA_SIZE));
	
	address1 = VSAAlloc(new_vsa, 8);
	
	Test(96 - (8 + VSA_SIZE), VSALargestFreeBlock(new_vsa), "TestVSAAlloc()",
	    __FILE__, __LINE__);
	    
	address2 = VSAAlloc(new_vsa, 12);
	
	Test(72 - (16 + VSA_SIZE), VSALargestFreeBlock(new_vsa), "TestVSAAlloc()",
	     __FILE__, __LINE__);
	     
	address3 = VSAAlloc(new_vsa, 5);
	
	Test(40 - (8 + VSA_SIZE), VSALargestFreeBlock(new_vsa), "TestVSAAlloc()",
	     __FILE__, __LINE__);
	     
	printf("----------\n");
	     
	VSAFree(address1);
	
	address4 = VSAAlloc(new_vsa, 8);
	
	Test((size_t)address1, (size_t)address4, "TestVSAFree()", 
	     __FILE__, __LINE__);
	     
	printf("----------\n");
	     
	VSAFree(address4);
	VSAFree(address2);
	
	Test(40, VSALargestFreeBlock(new_vsa), "TestVSALaregstFreeBlock()", __FILE__, __LINE__);
	
	VSAFree(address3);
	
	Test(96, VSALargestFreeBlock(new_vsa), "TestVSALargestFreeBlock()", __FILE__, __LINE__);
	    
	free(memory_vsa);
	memory_vsa = NULL;
	
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

