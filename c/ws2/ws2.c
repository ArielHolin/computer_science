/************************************************************************
*  ws2.c
*  Author: Ariel
*  Reviewer: Eli
*************************************************************************/

#include <stdio.h>     /* printf  */
#include <stdlib.h>    /* malloc, exit  */
#include <string.h>    /* memcmp  */
#include <assert.h>    /* assert  */
#include <ctype.h>     /* isspace */

void SwapInts(int *ptr_1, int *ptr_2);
int *CopyArray(int *arr, int arr_size);
void SwapSizeT(size_t *ptr_1, size_t *ptr_2);
void SwapSizeTPtr(size_t **ptr_ptr_1, size_t **ptr_ptr_2);
void TestSwapSizeTPtr(void);
int RecursivePal(char *start_ptr, char *end_ptr);
int IsPalindrome(const char *word);
void *RmWhiteSpace(char *string);

void TestCopyArray(void);
void TestSwapInts(void);
void TestSwapSizeT(void);
void TestSwapSizeTPtr(void);
void TestIsPal(void);
void TestRmWhiteSpace(void);

int main(void)
{
    /*TestSwapInts();
    TestCopyArray(); 
	TestSwapSizeT();
	TestSwapSizeTPtr();
	TestIsPal();*/
	TestRmWhiteSpace();
	return 0;
}

/*********************Swap Integers********************************************/

/* Receives addresses of two integer values, and then swap the values */
void SwapInts (int *ptr_1, int *ptr_2)
{
	int tmp = *ptr_1;
	*ptr_1 = *ptr_2;
	*ptr_2 = tmp;
}

void TestSwapInts(void)
{
	int before_swp1 = 42;
	int before_swp2 = 17;
	
	int after_swp1 = 17;
	int after_swp2 = 42;
	
	SwapInts(&before_swp1, &before_swp2);
	
	assert(before_swp1==after_swp1 && before_swp2==after_swp2);
	
	printf("TestSwapInts() Success!\n----------\n");
} 

/*******************Copy Arrays************************************************/

/* Receives array and array size, and return a copy of array */
int *CopyArray(int *arr, int arr_size)
{
	int i = 0;
	int *dst_arr = malloc(arr_size*sizeof(int));
	
	if (NULL == dst_arr)
	{
		printf("Segmentation fault.\n");
		exit(1);
	}
		
	for (i = 0; i < arr_size; i++)
	{
		dst_arr[i] = arr[i];
	}
	
	return dst_arr;
}

void TestCopyArray(void)
{
	int arr_s1 = 5;
	int arr_s2 = 0;
	
	int arr1[] = {1, 2, 3, 4, 5};
	int *arr2 = NULL;
	
	int *res1 = CopyArray(arr1, arr_s1);
	int *res2 = CopyArray(arr2, arr_s2);
	
	if ((0!=memcmp(arr1, res1, arr_s1)) || (0!=memcmp(arr2, res2, arr_s2)))
	{
		printf("CopyArray() is incorrect!\n");
		exit(1);
	}
	
	printf("TestCopyArray() Success!\n----------\n");
	
	free(res1);
	free(res2);
}

/*********************SwapSizeT************************************************/

/* Receives addresses of two size_t values, and then swap the values */
void SwapSizeT(size_t *ptr_1, size_t *ptr_2)
{
	size_t tmp = *ptr_1;
	*ptr_1 = *ptr_2;
	*ptr_2 = tmp;
} 

void TestSwapSizeT(void)
{
	size_t before_swp1 = 42;
	size_t before_swp2 = 17;
	
	size_t after_swp1 = 17;
	size_t after_swp2 = 42;
	
	SwapSizeT(&before_swp1, &before_swp2);
	
	assert(before_swp1==after_swp1 && before_swp2==after_swp2);
	
	printf("TestSwapInts() Success!\n----------\n");
} 

/*****************SwapSizeTPtr*************************************************/

/* Receives two size_t double pointers, and then swap the values.
   addresses should be swapped and values should remain the same. */
void SwapSizeTPtr(size_t **ptr_ptr_1, size_t **ptr_ptr_2)
{
	SwapSizeT((size_t *) ptr_ptr_1, (size_t *) ptr_ptr_2);
}

void TestSwapSizeTPtr(void)
{
	size_t val1 = 42;
	size_t *val1_adds = &val1;
	
	size_t val2 = 17;
	size_t *val2_adds = &val2;
	
	printf("TestSwapSizeTPtr() validation check: \n");
	printf("Before Swap: \n val1 = %d, val2 = %d \n add_val1 = %x, \
	        add_val2 = %x\n", (int) val1, (int) val2, (int)(long) val1_adds, \
	        (int)(long) val2_adds);
	
	SwapSizeTPtr(&val1_adds, &val2_adds);
	
	printf("After Swap: \n val1 = %d, val2 = %d \n add_val1 = %x, \
	        add_val2 = %x\n\n", (int) val1, (int) val2, \
	        (int)(long) val1_adds, (int)(long) val2_adds);
	
	assert(val1_adds==&val2 && val2_adds==&val1);
	assert(val1==42 && val2==17);
	
	printf("TestSwapSizeTPtr() Success!\n----------\n");	
} 

/*********************Is Palindrome********************************************/

/* Checks recursively if between start_ptr and end_ptr there's a Palindrome. */
/* Valid to single words only. */
int RecursivePal(char *start_ptr, char *end_ptr)
{
	if (start_ptr == end_ptr)
	{
		puts("Input is Palindrome! :)");
		return 0;
	}
	
	if (tolower(*start_ptr) == tolower(*end_ptr))
	{
		RecursivePal(++start_ptr, --end_ptr);
	}
	
	else
	{
		puts("Input is not Palindrome.. :(");
		return 1;
	}
}

/* Validates that a string is a Palindrome. */
int IsPalindrome(const char *word)
{
	size_t word_len = strlen(word) - 1;
	RecursivePal((char *)word, (char *)word + word_len);
}

void TestIsPal(void)
{
	const char *word1 = "Rotator";
	const char *word2 = "kAYaK";
	const char *word3 = "Palindrome";
	
	assert(0 == IsPalindrome(word1));
	assert(0 == IsPalindrome(word2));
	assert(1 == IsPalindrome(word3));
	
	puts("TestIsPal() Success!");
}

/********************************Remove White spaces***************************/

/* Removes whitespaces from beginning and end of string, and removes extra
   whitespaces within a string. */
void *RmWhiteSpace(char *str)
{
	size_t adj = 0;
	size_t curr = 0;
	
	for (adj=0, curr=0; *(str+curr); ++curr)
	{
		if (!isspace(*(str+curr)) || (0<curr && !isspace(*(str+curr-1))))
		{
			*(str + adj) = *(str + curr);
			++adj;
		} 
	}
	
	*(str + adj) = '\0';
}

void TestRmWhiteSpace(void)
{
	char string[] = "   Hello,		world!    ";
	/*printf("%li\n", strlen(string));*/
	printf("%li\n", strlen(string));
	puts(string);
	RmWhiteSpace(string);
	puts(string);
	printf("%li\n", strlen(string));
	/*printf("%s\n", string);
	printf("%li\n", strlen(string));*/
}
