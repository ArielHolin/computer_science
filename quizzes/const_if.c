/*******************************************************************************
*  const_if.c Quiz                                                             *
*  Author: Ariel                                                               *
*******************************************************************************/
#include <stddef.h> /* size_t */
#include <stdio.h>  /* printf */

int FindNumInArray(int arr[], int num, size_t array_len);

int main(void)
{
	int numbers[7] = {-5, 3, 1, -2, 10, -6, 7};
	int res = FindNumInArray(numbers, 10, 7);
	
	if( 1 == res )
	{
		printf("The number is in the array! :)\n");
	}
	
	else
	{
		printf("The number is not in the array.. :(\n");
	}
	
	return 0;
}

int FindNumInArray(int arr[], int num, size_t array_len)
{
	size_t i = 0;
	int result = 1;
	
	for( i = 0; i < array_len; ++i )
	{
		result *= (arr[i] - num);
		result = !!result;  /* Avoiding overflow */
	}
	
	return !result;
}
