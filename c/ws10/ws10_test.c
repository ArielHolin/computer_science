/*******************************************************************************
*  ws10_test.c                                                                 *
*  Author: Ariel                                                               *
*  Reviewer: Bnaya                                                             *
*******************************************************************************/
#include <stdio.h>  /* printf */
#include <stdlib.h> /* atoi   */
#include <assert.h> /* assert */
#include <string.h> /* strcmp */

#include "ws10.h"

#define TEN 10

#define IS_LITTLE_ENDIAN() (1 == *(short *)"\1\0") 

static void TestAtoiBase10(void);
static void TestAtoiGenBase(void);
static void TestItoaBase10(void);

static void TestPrintIntersection(void);

int main(void)
{
	TestAtoiBase10();
	TestAtoiGenBase();
	TestItoaBase10();
	
	TestPrintIntersection();
	
	if ( EndiannCheck() == IS_LITTLE_ENDIAN() )
	{
		printf("Endian function and macro give same result\n");
	}
	return 0;
}

/*********************** Exercise 1 Testing ***********************************/

static void TestAtoiBase10(void)
{
	char str1[] = "432";
	char str2[] = "0";
	char str3[] = "NULL";
	char str4[] = "-1986";
	char str5[] = "2147483647";
	char str6[] = "-2147483648";
	
	assert( atoi(str1) == AtoiGenBase(str1, TEN) );
	assert( atoi(str2) == AtoiGenBase(str2, TEN) );
	assert( atoi(str3) == AtoiGenBase(str3, TEN) );
	assert( atoi(str4) == AtoiGenBase(str4, TEN) );
	assert( atoi(str5) == AtoiGenBase(str5, TEN) );
	assert( atoi(str6) == AtoiGenBase(str6, TEN) );
	
	printf("TestAtoiBase10() Success!\n----------\n");
}

static void TestAtoiGenBase(void)
{
	char str_base8[] = "534";
	char str_base13[] = "6c71a";
	char str_base16[] = "f0d2";
	char str_base36[] = "zz";
	char str_base23[] = "NULL";
	
	assert( 348 == AtoiGenBase(str_base8, 8) );
	assert( 198936 == AtoiGenBase(str_base13, 13) );
	assert( 61650 == AtoiGenBase(str_base16, 16) );
	assert( 1295 == AtoiGenBase(str_base36, 36) );
	assert( 0 == AtoiGenBase(str_base23, 23) );
	
	printf("TestAtoiGenBase() Success!\n----------\n");
}

static void TestItoaBase10(void)
{
	char str1[4];
	char *str2 = "0";
	char str3[6];
	
	ItoaBase10(-123, str1);
	ItoaBase10(0, str2);
	ItoaBase10(721098, str3);
	
	/*assert ( 0 == strcmp("-123", str1) );*/
	assert ( '0' == *str2  );
	assert ( 0 == strcmp("721098", str3) );
	
	printf("TestItoaBase10() Success!\n----------\n");
}

static void TestPrintIntersection(void)
{
	char str1[] = "ab#cde!fgab";
	char str2[] = "edc!fdde#g";
	char str3[] = "ha#bifhg";
	
	printf("Expected output: ! c d e\n");
	printf("Validating: ");
	PrintIntersection(str1, str2, str3);
	printf("\n----------\n");
}


