/*******************************************************************************
*  circular_buffer_test.c                                                      *
*  Author: Ariel                                                               *
*  Reviewer: Philip                                                            *
*******************************************************************************/
#include <stddef.h> /* size_t */
#include <stdio.h>  /* printf */

#include "circular_buffer.h"

#define CAPACITY 5

enum empty_status
{
	NON_EMPTY = 0,
	EMPTY = 1
};

static void TestCircBufferCreateDestroy(void);
static void TestCircBuffFreeSpaceBufSizeIsEmp(void);
static void TestCircBuffWriteRead(void);
static void Test(size_t expected_res, size_t res, const char *test_name, 
                 const char *filename, size_t line_num);

int main(void)
{
	TestCircBufferCreateDestroy();
	TestCircBuffFreeSpaceBufSizeIsEmp();
	TestCircBuffWriteRead();
	return 0;
}

/***** TestCircBufferCreateDestroy ********************************************/

static void TestCircBufferCreateDestroy(void)
{
	cbuf_ty *new_cbuf = CircBuffCreate(CAPACITY);
	
	Test(EMPTY, CircBuffIsEmpty(new_cbuf), "TestCircBuffCreateDestroy()", 
	     __FILE__, __LINE__);
	     
	printf("----------\n");
	     
	CircBuffDestroy(new_cbuf);
	
}

/***** TestCircBuffFreeSpaceBufSizeIsEmp **************************************/

static void TestCircBuffFreeSpaceBufSizeIsEmp(void)
{
	cbuf_ty *new_cbuf = CircBuffCreate(CAPACITY);
	char src[] = "hello";
	char dest[CAPACITY];
	size_t chars_to_read = 3;
	size_t write_count = 0;
	size_t read_count = 0;
	
	Test(CAPACITY, CircBuffFreeSpace(new_cbuf), "TestCircBuffFreeSpaceBufSizeIsEmp()",
	     __FILE__, __LINE__);
	
	Test(0, CircBuffBufsiz(new_cbuf), "TestCircBuffBufsiz()",
	     __FILE__, __LINE__);
	     
	Test(EMPTY, CircBuffIsEmpty(new_cbuf), "TestCircBuffIsEmpty()", 
	     __FILE__, __LINE__);
	     
	printf("----------\n"); 
	     
	write_count = CircBuffWrite(new_cbuf, (void *)src, CAPACITY);
	
	Test(CAPACITY - write_count, CircBuffFreeSpace(new_cbuf), 
	     "TestCircBuffFreeSpaceBufSizeIsEmp()", __FILE__, __LINE__);
	
	Test(write_count, CircBuffBufsiz(new_cbuf), "TestCircBuffBufsiz()",
	     __FILE__, __LINE__);
	     
	Test(NON_EMPTY, CircBuffIsEmpty(new_cbuf), "TestCircBuffIsEmpty()", 
	     __FILE__, __LINE__);
	     
	printf("----------\n"); 
	     
	read_count = CircBuffRead(new_cbuf, (void *)dest, chars_to_read);
	
	Test(read_count, CircBuffFreeSpace(new_cbuf), "TestCircBuffFreeSpaceBufSizeIsEmp()",
	     __FILE__, __LINE__);
	     
	Test(CAPACITY - read_count, CircBuffBufsiz(new_cbuf), "TestCircBuffBufsiz()",
	     __FILE__, __LINE__);
	     
	Test(NON_EMPTY, CircBuffIsEmpty(new_cbuf), "TestCircBuffIsEmpty()", 
	     __FILE__, __LINE__);
	     
	printf("----------\n");     
	     
	CircBuffDestroy(new_cbuf);
}

/***** TestCircBuffWriteRead **************************************************/

static void TestCircBuffWriteRead(void)
{
	cbuf_ty *new_cbuf = CircBuffCreate(CAPACITY);
	cbuf_ty *new_cbuf2 = CircBuffCreate(CAPACITY);
	char src[] = "hello";
	char dest[CAPACITY];
	size_t word_count2 = 0;
	
	CircBuffWrite(new_cbuf, (void *)src, CAPACITY);
	CircBuffRead(new_cbuf, (void *)dest, 2);
	CircBuffWrite(new_cbuf, (void *)src, 1);
	
	Test(1, CircBuffFreeSpace(new_cbuf), "TestCircBuffWriteRead()",
	     __FILE__, __LINE__);
	
	Test(4, CircBuffBufsiz(new_cbuf), "TestCircBuffWriteRead()",
	     __FILE__, __LINE__);
	
	CircBuffRead(new_cbuf, (void *)dest, 2);
	CircBuffWrite(new_cbuf, (void *)src, 1);
	
	Test(2, CircBuffFreeSpace(new_cbuf), "TestCircBuffWriteRead()",
	     __FILE__, __LINE__);
	
	Test(3, CircBuffBufsiz(new_cbuf), "TestCircBuffWriteRead()",
	     __FILE__, __LINE__);
	     
	word_count2 = CircBuffWrite(new_cbuf2, (void *)src, CAPACITY + 1);
	
	Test(CAPACITY, word_count2, "TestCircBuffWriteRead()",
	     __FILE__, __LINE__);
	     
	printf("----------\n");
	     
	CircBuffDestroy(new_cbuf);
	CircBuffDestroy(new_cbuf2);
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
