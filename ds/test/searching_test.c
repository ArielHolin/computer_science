/*******************************************************************************
*  searching_test.c                                                            *
*  Author: Ariel                                                               *
*  Reviewer:                                                                   *
*******************************************************************************/
#include <stdio.h>  /* printf */
#include <stddef.h> /* size_t */

#include "searching.h"

typedef int (*search_func_ty)(int *sorted_arr, size_t arr_size, int num_to_find);

#define ARR_SIZE 10

#define NOT_FOUND -1

void TestBinarySearch(search_func_ty search_func, char *func_name, int *sorted_arr);

int main(void)
{
	int sorted_arr[ARR_SIZE] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
	TestBinarySearch(RecursiveBinarySearch, "TestRecursiveBinarySearch", sorted_arr);
	TestBinarySearch(IterativeBinarySearch, "TestIterativeBinarySearch", sorted_arr);	
	return 0;
}

/************* TestRecursiveBinarySearch **************************************/

void TestBinarySearch(search_func_ty search_func, char *func_name, int *sorted_arr)
{
	int search_res[ARR_SIZE] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
	int non_exist[2] = {-1, 11};
	size_t i = 0;
	
	for(i = 0; i < ARR_SIZE; ++i)
	{
		if(search_res[i] != search_func(sorted_arr, ARR_SIZE, sorted_arr[i]))
		{
			printf("%s fail at existing values at index: %ld\n", func_name, i);
			printf("----------\n");
			return;
		}
	}
	
	for(i = 0; i < 2; ++i)
	{
		if(NOT_FOUND != search_func(sorted_arr, ARR_SIZE, non_exist[i]))
		{
			printf("%s fail at non existing values at index: %ld\n", func_name, i);
			printf("----------\n");
			return;
		}
	}
	
	printf("%s success\n", func_name);
	printf("----------\n");
}
