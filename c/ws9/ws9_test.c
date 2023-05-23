/*******************************************************************************
*  ws9_test.c                                                                  *
*  Author: Ariel                                                               *
*  Reviewer: Maayan                                                            *
*******************************************************************************/
#include <string.h> /* memset, memcpy, memmove, strcmp */
#include <stdio.h>  /* printf                          */ 
#include <assert.h> /* assert                          */

#include "ws9.h"

static void TestMemset(void);
static void TestMemcpy(void);
static void TestMemmove(void);

int main(void)
{
	TestMemset();
	TestMemcpy();
	TestMemmove();
	return 0;
}

static void TestMemset(void)
{	
	char str[] = "Hello, world! This is a string to test Memset functions!";
	char str1[] = "Hello, world! This is a string to test Memset functions!";
	char str2[] = "Hello, world! This is a string to test Memset functions!";
	char str3[] = "Hello, world! This is a string to test Memset functions!";
	
	
	assert (0 == strcmp(Memset(str, 5, 10), memset(str1, 5, 10)));
	assert (0 == strcmp(Memset(&str2[4], 't', 7), memset(&str3[4], 't', 7))); 
	
	printf("TestMemset() Success!\n-----------\n");
}

static void TestMemcpy(void)
{
	char str[] = "Hello, world! This is a string to test Memcpy functions!";
	char str1[]= "Hello, world! This is a string to test Memcpy functions!";
	char str2[]= "Hello, world! This is a string to test Memcpy functions!";
	
	assert (0 == strcmp(Memcpy(str1, &str[6], 12), memcpy(str2, &str[6], 12)));
	
	printf("TestMemcpy() Success!\n-----------\n");
}

static void TestMemmove(void)
{
	char str[] = "Hello, world! This is a string to test Memmove functions!";
	char str1[]= "Hello, world! This is a string to test Memmove functions!";
	char str2[]= "Hello, world! This is a string to test Memmove functions!";
	
	assert (0 == strcmp(Memmove(&str1[6], str, 12), memmove(&str2[6], str, 12)));
	
	printf("TestMemmove() Success!\n-----------\n");
}
