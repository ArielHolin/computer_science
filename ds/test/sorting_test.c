/*******************************************************************************
*  sorting_test.c                                                              *
*  Author: Ariel                                                               *
*  Reviewer: Eva                                                               *
*******************************************************************************/
#include <stdio.h>  /* printf                         */
#include <stddef.h> /* size_t                         */
#include <stdlib.h> /* malloc, free, rand, qsort      */
#include <assert.h> /* assert                         */
#include <time.h>   /* clock_t, clock, CLOCKS_PER_SEC */

#include "sorting.h"

#define FIVE_K  5000
#define FIVE_HK 500000

#define ILRD_SUCCESS 0

typedef void (*SortingFuncTy)(int *, size_t);
typedef void (*QuickSortFuncTy)(void *base, size_t nmemb, size_t elem_size, 
                                                          cmp_func_ty cmp_func);

int SortingTest(SortingFuncTy SortingFunc, char *func_name, char *test_name);
int TestQSort(QuickSortFuncTy QuickSFunc, char *func_name, char *test_name);
int TestRadixSort(unsigned int exponent_of_two);
int TestMergeSort(void);

static int *CreateRandomArray(size_t array_len);
static void DestroyRandomArray(int *random_array);
static int cmpfunc (const void *num1, const void *num2);

int main(void)
{
	SortingTest(BubbleSort, "BubbleSort", "TestBubbleSort()");
	SortingTest(InsertionSort, "InsertionSort", "TestInsertionSort()");
	SortingTest(SelectionSort, "SelectionSort", "TestSelectionSort()");
	SortingTest(CountingSort, "CountingSort", "TestCountingSort()");
	TestRadixSort(3);
	TestMergeSort();
	TestQSort(qsort, "Qsort", "TestQsort()");
	TestQSort(QuickSort, "QuickSort", "TestQuickSort()");
	return 0;
}

/**** SortingTest - Generic testing for sorting functions *********************/

int SortingTest(SortingFuncTy SortingFunc, char *func_name, char *test_name)
{
	size_t array_len = FIVE_K;
	int *random_array = CreateRandomArray(array_len);
	int *runner = NULL;
	int *end_random_array = NULL;
	size_t i = 0;
	clock_t start_t;
	clock_t end_t;
	double total_t;
	
	if(!random_array)
	{
		printf("Error occured while creating the array\n");
		return -1;
	}
	
	runner = random_array;
	end_random_array = random_array + (array_len - 1);
	
	start_t = clock();
	SortingFunc(random_array, array_len);
	end_t = clock();
	
	total_t = (double)(end_t - start_t) / CLOCKS_PER_SEC;
	
	while(runner != end_random_array)
	{
		if(*runner > *(runner + 1))
		{
			printf("Error occured at index: %li\n", i);
			printf("%s fail!\n", test_name);
			printf("----------\n");
			return -1;
		}
		
		++i;
		++runner;
	}
	
	DestroyRandomArray(random_array);
	
	printf("Total time taken to execute %s: %f\n", func_name, total_t);
	printf("%s Success!\n", test_name);
	printf("----------\n");
	return 0;
}

/***** TestQSort **************************************************************/

int TestQSort(QuickSortFuncTy QuickSFunc, char *func_name, char *test_name)
{
	size_t array_len = FIVE_K;
	int *random_array = CreateRandomArray(array_len);
	int *runner = NULL;
	int *end_random_array = NULL;
	size_t i = 0;
	clock_t start_t;
	clock_t end_t;
	double total_t;
	
	if(!random_array)
	{
		printf("Error occured while creating the array\n");
		return -1;
	}
	
	runner = random_array;
	end_random_array = random_array + (array_len - 1);
	
	start_t = clock();
	QuickSFunc(random_array, array_len, sizeof(int), cmpfunc);
	end_t = clock();
	
	total_t = (double)(end_t - start_t) / CLOCKS_PER_SEC;
	
	while(runner != end_random_array)
	{
		if(*runner > *(runner + 1))
		{
			printf("Error occured at index: %li\n", i);
			printf("%s fail!\n", test_name);
			printf("----------\n");
			return -1;
		}
		
		++i;
		++runner;
	}
	
	DestroyRandomArray(random_array);
	
	printf("Total time taken to execute %s: %f\n", func_name, total_t);
	printf("%s Success!\n", test_name);
	printf("----------\n");
	return 0;
}

/***** TestRadixSort **********************************************************/

int TestRadixSort(unsigned int exponent_of_two)
{
	size_t array_len = FIVE_K;
	int *random_array = CreateRandomArray(array_len);
	int *runner = NULL;
	int *end_random_array = NULL;
	size_t i = 0;
	clock_t start_t;
	clock_t end_t;
	double total_t;
	
	if(!random_array)
	{
		printf("Error occured while creating the array\n");
		return -1;
	}
	
	runner = random_array;
	end_random_array = random_array + (array_len - 1);
	
	start_t = clock();
	RadixSort((unsigned int *)random_array, array_len, exponent_of_two);
	end_t = clock();
	
	total_t = (double)(end_t - start_t) / CLOCKS_PER_SEC;
	
	while(runner != end_random_array)
	{
		if(*runner > *(runner + 1))
		{
			printf("Error occured at index: %li\n", i);
			printf("TestRadixSort() fail!\n");
			printf("----------\n");
			return -1;
		}
		
		++i;
		++runner;
	}
	
	DestroyRandomArray(random_array);
	
	printf("Total time taken to execute RadixSort: %f\n", total_t);
	printf("TestRadixSort() Success!\n");
	printf("----------\n");
	return 0;
}

/***** TestMergeSort **********************************************************/

int TestMergeSort(void)
{
	size_t array_len = FIVE_K;
	int *random_array = CreateRandomArray(array_len);
	int *runner = NULL;
	int *end_random_array = NULL;
	size_t i = 0;
	clock_t start_t;
	clock_t end_t;
	double total_t;
	int ret = ILRD_SUCCESS;
	
	if(!random_array)
	{
		printf("Error occured while creating the array\n");
		return -1;
	}
	
	runner = random_array;
	end_random_array = random_array + (array_len - 1);
	
	start_t = clock();
	ret = MergeSort(random_array, array_len);
	end_t = clock();
	
	total_t = (double)(end_t - start_t) / CLOCKS_PER_SEC;
	
	if(ILRD_SUCCESS != ret)
	{
		printf("MergeSort system error\n");
		return ret;
	}
	
	while(runner != end_random_array)
	{
		if(*runner > *(runner + 1))
		{
			printf("Error occured at index: %li\n", i);
			printf("TestRadixSort() fail!\n");
			printf("----------\n");
			return -1;
		}
		
		++i;
		++runner;
	}
	
	DestroyRandomArray(random_array);
	
	printf("Total time taken to execute MergeSort: %f\n", total_t);
	printf("TestMergeSort() Success!\n");
	printf("----------\n");
	return 0;
}

/***** Helper Functions *******************************************************/

/* Creating array of length array_len of random integers between 0 and 500K.
   The range of integers chose randomly, mainly for CountingSort utilization.*/
static int *CreateRandomArray(size_t array_len)
{
	int *random_array = NULL;
	int *end_random_array = NULL;
	int *runner = NULL;
	
	assert(array_len > 0);
	
	random_array = (int *)malloc(array_len * sizeof(int));
	
	if(!random_array)
	{
		return NULL;
	}
	
	end_random_array = random_array + array_len;
	runner = random_array;
	
	while(runner != end_random_array)
	{
		*runner = rand() % FIVE_HK;
		++runner;
	}
	
	return random_array;
}

/* Destroying the array of random integers */
static void DestroyRandomArray(int *random_array)
{
	assert(random_array);
	
	free(random_array);
	random_array = NULL;
}

/* Function to use as paramter inside qsort */
static int cmpfunc (const void *num1, const void *num2)
{
   return ( *(int *)num1 - *(int *)num2 );
}
