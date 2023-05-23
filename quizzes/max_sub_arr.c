/*******************************************************************************
*  Quiz Maximum Sub Array                                                      *
*  Author: Ariel                                                               *
*******************************************************************************/
#include <stddef.h>  /* size_t */
#include <stdio.h>   /* printf */

typedef struct sum_and_ind
{
	size_t first_ind;
	size_t last_ind;
	size_t sum;
} sum_and_ind_ty;

sum_and_ind_ty FindMaxSum(int array[], size_t array_len);

/******************************************************************************/

int main(void)
{
	int array[9] = {-2, 1, -3, 4, -1, 2, 3, -5, 4};
	
	sum_and_ind_ty res = FindMaxSum(array, 9);
	
	printf("sum: %li, first ind: %li, last ind: %li\n", 
	        res.sum, res.first_ind, res.last_ind);
	
	return 0;
	
}

/******************************************************************************/

sum_and_ind_ty FindMaxSum(int array[], size_t array_len)
{
	int current_sum = 0;
	size_t max_sum = 0;
	size_t i = 0;
	
	sum_and_ind_ty result;
	result.sum = array[0];
	result.first_ind = 0;
	result.last_ind = 0;
	
	
	for ( i = 0; i < array_len; ++i)
	{
		current_sum += array[i];
		
		if ( current_sum < 0 )
		{
			result.first_ind = i + 1;
			current_sum = 0;
			continue;
		}
		
		if ( current_sum >= max_sum )
		{
			max_sum = current_sum;
			result.sum = max_sum;
			result.last_ind = i;
		}
	}
	
	return result;
}
