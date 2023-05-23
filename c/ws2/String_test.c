/**************************************************
*  String_test.c
*  Author: Ariel Holin
*  Reviewer: Eli
**************************************************/

#include <stddef.h>  /* size_t */
#include "String.h"  /* StrLen, StrCmp, StrCpy */
#include <assert.h>  /* assert */
#include <stdio.h>   /* puts */
#include <stdlib.h>  /* malloc, free */
#include <string.h>

void TestStrLen(void);
void TestStrCmp(void);
void TestStrCpy(void);
void TestStrnCpy(void);
void TestStrCaseCmp(void);
void TestStrChr(void);
void TestStrDup(void);
void TestStrCat(void);
void TestStrnCat(void);
void TestStrStr(void);
void TestStrSpn(void);

int main(void)
{
	/*TestStrLen();
	TestStrCmp(); 
	TestStrCpy();
	TestStrnCpy();
	TestStrCaseCmp();
	TestStrChr();
	TestStrDup();*/
	TestStrCat();
	/*TestStrnCat();
	TestStrStr();
	TestStrSpn();*/
	return 0;
}

void TestStrLen(void)
{
	assert(5 == StrLen("Hello"));
	assert(14 == StrLen("dkj^& 9g $#@ae"));
	assert(0 == StrLen(""));
	puts("TestStrLen() Success!");
}

void TestStrCmp(void)
{
	assert(0 == StrCmp("Hello", "Hello"));
	assert(0 < StrCmp("hi", "Hi"));
	assert(0 > StrCmp("dkjcD^24^*!@", "vlkkv(*@!21 "));
	puts("TestStrCmp() Success!");
}

void TestStrCpy(void)
{
	const char *src1 = "Hello";
	char *dst1 = (char *)malloc(StrLen(src1) + 1);
	
	assert(0 == StrCmp(StrCpy(dst1, src1), src1));
	
	free(dst1);
	
	puts("TestStrCpy() Success!");
}

void TestStrnCpy(void)
{
	const char *src1 = "Hello!!!!";
	char *dst1 = (char *)malloc(sizeof(char)*4 + 1);
	char *dst2 = (char *)malloc(sizeof(char)*12 + 1);
	
	assert(StrnCpy(dst1, src1, 4) == strncpy(dst1, src1, 4));
	assert(StrnCpy(dst2, src1, 12) == strncpy(dst2, src1, 12));
	
	puts("TestStrnCpy() Success!");
	
	free(dst1);
	free(dst2);
}

void TestStrCaseCmp(void)
{
	const char *s1_tst = "hElLO";
	const char *s2_tst = "HeLLo";
	
	const char *s1_tst1 = "aRIel";
	const char *s2_tst1 = "NIsaN";
	
	const char *s1_tst2 = "H&$I!";
	const char *s2_tst2 = "h&$i!";
	
	assert(0 == StrCaseCmp(s1_tst, s2_tst));
	assert(0 > StrCaseCmp(s1_tst1, s2_tst1));
	assert(0 == StrCaseCmp(s1_tst2, s2_tst2));
	
	puts("TestStrCaseCmp() Success!");
}

void TestStrChr(void)
{
	const char *s1_tst = "abcbad";
	int a = 97;
	int b = 98;
	int c = 99;
	int d = 100;

	char *res1 = StrChr(s1_tst, a);
	char *res2 = StrChr(s1_tst, b);
	char *res3 = StrChr(s1_tst, c);
	char *res4 = StrChr(s1_tst, d);
	
	assert(res1 == (char *)s1_tst);
	assert(res2 == (char *)(s1_tst + 1));
	assert(res3 == (char *)(s1_tst + 2));
	assert(res4 == (char *)(s1_tst + 5));
	
	puts("TestStrChr() Success!");
}

void TestStrDup(void)
{
	const char *s = "Hello";
	char *res = StrDup(s);
	
	printf("Input string: %s\n", s);
	printf("Output string: %s\n\n", res);
	
	assert(s!=res);
	
	puts("TestStrDup() Success!");
	
	free(res);
}

void TestStrCat(void)
{
	char *dest1 = "Hello, ";
	const char *src1 = "World!";
	char *res = (char *)malloc(StrLen(dest1) + 2*StrLen(src1) + 1);
	size_t i = 0;
	
	for (i = 0; i < StrLen(dest1) + 2*StrLen(src1) + 1; ++i)
	{
		res[i] = 0;
	}
	
	StrCpy(res, dest1);
	assert(StrCat(res, src1) == strcat(res, src1));
	
	puts("TestStrCat() Success!");
	
	free(res);
}


void TestStrnCat(void)
{
	char *dest1 = "Hello, ";
	const char *src1 = "World!";
	char *res = (char *)malloc(StrLen(dest1) + StrLen(src1) + 1);
	size_t i = 0;
	
	for (i = 0; i < StrLen(dest1) + StrLen(src1) + 1; ++i)
	{
		res[i] = 0;
	}
	
	StrCpy(res, dest1);
	assert(StrnCat(res, src1, 3) == strncat(res, src1, 3));
	
	puts("TestStrnCat() Success!");
	
	free(res);	
}

void TestStrStr(void)
{
	const char *hay = "Hello, World!";
	const char *need = "lo, W!";
	char *res = StrStr(hay, need);
	
	assert(res == strstr(hay, need));
	
	puts("TestStrStr() Success!");
}

void TestStrSpn(void)
{
	char *s1 = "Aticleworld";
    char *accept1 = "Atic";
    
    char *s2 = "ABCDEF";
    char *accept2 = "0A245BFC19ED";
    
    char *s3 = "ZBCDEF";
    char *accept3 = "0A245BFC19ED";

    
    assert(StrSpn(s1, accept1) == strspn(s1, accept1));
    assert(StrSpn(s2, accept2) == strspn(s2, accept2));
    assert(StrSpn(s3, accept3) == strspn(s3, accept3));
    
    puts("TestStrSpn() Success!");
}
