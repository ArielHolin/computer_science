/*******************************************************************************
*  ht_test.c                                                                   *
*  Author: Ariel                                                               *
*  Reviewer: Phillip                                                           *
*******************************************************************************/
#include <stddef.h> /* size_t       */
#include <ctype.h>  /* tolower      */
#include <string.h> /* strcmp       */
#include <stdio.h>  /* printf       */
#include <stdlib.h> /* malloc, free */

#include "ht.h"
#include "dlist.h"

#define FIRST_LOWER_CHAR 97
#define ENGLISH_CHARS    26

#define NON_EMPTY 0
#define EMPTY     1

#define ILRD_SUCCESS 0

#define MAX_WORD_SIZE 25

typedef struct person
{
	char *name;
	size_t age;
}person_ty;

static void Test(size_t expected_res, size_t res, const char *test_name, 
                 const char *filename, size_t line_num);
void TestHTCreateDestroy(void);
void TestHTInsertSizeIsEmpty(void);
void TestHTFindRemove(void);
void TestHTForEach(void);

void HTSpellChecker(void);
static ht_ty *HTCreateAndUploadDict(size_t capacity, hash_func_ty hash_func, 
                               get_key_ty get_key_func, ht_match_ty match_func);
/*********** typedef functions ************************************************/

void *GetKey(const void *key)
{
	return (void *)((person_ty *)key)->name;
}

void *DictGetKey(const void *key)
{
	return (void *)key;
} 

size_t HashFunc(const void *key)
{
	return tolower(*(char *)key) - FIRST_LOWER_CHAR;
}

int Match(const void *data, void *param)
{
	return strcmp((char *)data, (char *)param);
}

int DictMatch(const void *data, void *param)
{
	return !strcmp((char *)data, (char *)param);
}

int Op(void *data, void *param)
{
	++*(size_t *)param;
	
	return ILRD_SUCCESS;
}

int DictOp(void *data, void *param)
{
	free(data);
	data = NULL;
	
	return 0;
}

/******************************************************************************/
	
int main(void)
{
	TestHTCreateDestroy();
	TestHTInsertSizeIsEmpty();
	TestHTFindRemove();
	TestHTForEach();	
	HTSpellChecker();
	
	return 0;
}

/*********** TestHTCreateDestroy **********************************************/

void TestHTCreateDestroy(void)
{
	ht_ty *new_ht = HTCreate(ENGLISH_CHARS, HashFunc, GetKey, Match);
	
	Test(EMPTY, HTIsEmpty(new_ht), "HTCreateDestroy()", __FILE__, __LINE__);
	
	HTDestroy(new_ht);
	
	printf("----------\n");
}

/*********** TestInsertSizeIsEmpty ********************************************/

void TestHTInsertSizeIsEmpty(void)
{
	ht_ty *new_ht = HTCreate(ENGLISH_CHARS, HashFunc, GetKey, Match);
	int insert_res = ILRD_SUCCESS;
	
	person_ty person1;
	person_ty person2;
	person_ty person3;
	
	person1.name = "Ariel";
	person1.age = 35;
	
	person2.name = "homer";
	person2.age = 50;
	
	person3.name = "Bart";
	person3.age = 10;
	
	Test(EMPTY, HTIsEmpty(new_ht), "TestHTIsEmpty()", __FILE__, __LINE__);
	
	insert_res = HTInsert(new_ht, &person1);
	
	Test(ILRD_SUCCESS, insert_res, "TestHTInsert()", __FILE__, __LINE__);
	Test(1, HTSize(new_ht), "TestHTSize()", __FILE__, __LINE__);
	printf("\n");
	
	insert_res = HTInsert(new_ht, &person2);
	
	Test(ILRD_SUCCESS, insert_res, "TestHTInsert()", __FILE__, __LINE__);
	Test(2, HTSize(new_ht), "TestHTSize()", __FILE__, __LINE__);
	printf("\n");
	
	insert_res = HTInsert(new_ht, &person3);
	
	Test(ILRD_SUCCESS, insert_res, "TestHTInsert()", __FILE__, __LINE__);
	Test(3, HTSize(new_ht), "TestHTSize()", __FILE__, __LINE__);
	Test(NON_EMPTY, HTIsEmpty(new_ht), "TestHTIsEmpty()", __FILE__, __LINE__);
	
	HTDestroy(new_ht);
	
	printf("----------\n");
}

/*********** TestHTFindRemove *************************************************/

void TestHTFindRemove(void)
{
	ht_ty *new_ht = HTCreate(ENGLISH_CHARS, HashFunc, GetKey, Match);
	void *find_res = NULL;
	
	person_ty person1;
	person_ty person2;
	person_ty person3;
	person_ty person4;
	
	person1.name = "Ariel";
	person1.age = 35;
	
	person2.name = "homer";
	person2.age = 50;
	
	person3.name = "Bart";
	person3.age = 10;
	
	person4.name = "abe";
	person4.age = 80;
	
	HTInsert(new_ht, &person1);
	HTInsert(new_ht, &person2);
	HTInsert(new_ht, &person3);
	
	find_res = HTFind(new_ht, GetKey(&person1));
	
	if(find_res)
	{
		printf("Key found. ");
		HTRemove(new_ht, GetKey(&person1));
	}
	
	Test(2, HTSize(new_ht), "TestHTFindRemove()", __FILE__, __LINE__);
	
	find_res = HTFind(new_ht, GetKey(&person2));
	
	if(find_res)
	{
		printf("Key found. ");
		HTRemove(new_ht, GetKey(&person2));
	}
	
	Test(1, HTSize(new_ht), "TestFindRemove()", __FILE__, __LINE__);
	
	find_res = HTFind(new_ht, GetKey(&person4));
	
	if(!find_res)
	{
		printf("Key not found. TestFindRemove() success\n");
	}
	
	printf("----------\n");
	
	HTDestroy(new_ht);
}

/*********** TestHTForEach ****************************************************/

void TestHTForEach(void)
{
	ht_ty *new_ht = HTCreate(ENGLISH_CHARS, HashFunc, GetKey, Match);
	size_t counter = 0;
	
	person_ty person1;
	person_ty person2;
	person_ty person3;
	person_ty person4;
	
	person1.name = "Ariel";
	person1.age = 35;
	
	person2.name = "homer";
	person2.age = 50;
	
	person3.name = "Bart";
	person3.age = 10;
	
	person4.name = "abe";
	person4.age = 80;
	
	HTInsert(new_ht, &person1);
	HTInsert(new_ht, &person2);
	HTInsert(new_ht, &person3);
	HTInsert(new_ht, &person4);
	
	HTForEach(new_ht, Op, &counter);
	
	Test(4, counter, "TestHtForEach()", __FILE__, __LINE__);
	
	printf("----------\n");
	
	HTDestroy(new_ht);
} 

/*********** HTSpellChecker ***************************************************/

void HTSpellChecker(void)
{
	char word[MAX_WORD_SIZE];
	int unused = 0;
	void *find_res = NULL;
	ht_ty *new_ht = HTCreateAndUploadDict(ENGLISH_CHARS, HashFunc, DictGetKey, 
	                                                                 DictMatch);
	
	do
	{	
		printf("Insert input: ");
		
		fgets(word, MAX_WORD_SIZE, stdin);
		
		if ( 0 == strcmp(word, "Exit\n"))
		{
			continue;
		}
		
		find_res = HTFind(new_ht, word);
		
		if(!find_res)
		{
			printf("word doesn't exist in dictionary\n\n");
			continue;
		}
		
		printf("word exist in dictionary\n\n");
	}
	while (0 != strcmp(word, "Exit\n"));
	
	HTForEach(new_ht, DictOp, &unused);
	
	HTDestroy(new_ht);
	
}

static ht_ty *HTCreateAndUploadDict(size_t capacity, hash_func_ty hash_func, 
                                get_key_ty get_key_func, ht_match_ty match_func)
{
	ht_ty *new_ht = NULL;
	FILE *fp;
	char word[MAX_WORD_SIZE];
	char *new_str = NULL;
	
	new_ht = HTCreate(capacity, hash_func, get_key_func, match_func);
	
	fp = fopen("american-english", "r+");
	
	if(!fp)
	{
		printf("file fail to open\n");
		return NULL;
	}
	
	while(fgets(word, sizeof(word), fp))
	{
		new_str = (char *)malloc(sizeof(char) * (strlen(word)+1));
		memcpy(new_str, word, strlen(word)+1);
		HTInsert(new_ht, new_str);
	}
	
	fclose(fp);
	
	return new_ht;
}
/*********** Test Template ****************************************************/

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
