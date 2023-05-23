/*******************************************************************************
*  searching.c                                                                 *
*  Author: Ariel                                                               *
*  Reviewer:                                                                   *
*******************************************************************************/
#include <stddef.h> /* size_t */
#include <assert.h> /* assert */

#include "searching.h"

#define NOT_FOUND -1

/************* RecursiveBinarySearch ******************************************/

int RecursiveBinarySearch(int *sorted_arr, size_t arr_size, int num_to_find)
{
	size_t left = 0;
	size_t right = arr_size;
	int mean_val = 0;
	int ret = 0;
	
	assert(sorted_arr);
	
	if((1 == arr_size) && (num_to_find != sorted_arr[mean_val]))
	{
		return NOT_FOUND;
	}
	
	mean_val = (left + right) / 2;
	
	if(num_to_find == sorted_arr[mean_val])
	{
		return mean_val;
	}
	
	if(num_to_find > sorted_arr[mean_val])
	{
		ret = mean_val + RecursiveBinarySearch(sorted_arr + mean_val, 
		                                         right - mean_val, num_to_find);
		
		if(ret < mean_val)	
		{
			return NOT_FOUND;
		}
		
		return ret; 
	}
	 
	return RecursiveBinarySearch(sorted_arr, mean_val - left, num_to_find);
}

/************* IterativeBinarySearch ******************************************/

int IterativeBinarySearch(int *sorted_arr, size_t arr_size, int num_to_find)
{
	size_t curr_arr_size = arr_size;
	int left = 0;
	int right = (int)curr_arr_size;
	int mean_val = (left + right) / 2;
	
	assert(sorted_arr);
	
	while((left < right) && (num_to_find != sorted_arr[mean_val]))
	{
		if(num_to_find > sorted_arr[mean_val])
		{
			left = mean_val + 1;
			mean_val = (left + right) / 2;
		}
		
		else
		{
			right = mean_val - 1;
			mean_val = (left + right) / 2;
		}	
	}
	
	if(num_to_find == sorted_arr[mean_val])
	{
		return mean_val;
	}
	
	return NOT_FOUND;	
}
