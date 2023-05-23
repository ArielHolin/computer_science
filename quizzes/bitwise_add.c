/*******************************************************************************
*  Bitwise_add.c Quiz                                                          *
*  Author: Ariel                                                               *
*******************************************************************************/
#include <stddef.h> /* size_t */
#include <stdio.h>  /* printf */

size_t BitwiseAdd(size_t number);

int main(void)
{
	size_t numbers[] = {0, 12, 153, 3526};
	size_t results[] = {1, 13, 154, 3527};
	size_t i = 0;
	
	for ( i = 0; i < 4; ++i)
	{
		if ( BitwiseAdd(numbers[i]) != results[i] )
		{
			printf("BitwiseAdd() Fails!\n----------\n");
			return 1;
		}
	}
	
	printf("BitwiseAdd() Success!\n----------\n");
	return 0;	
}

size_t BitwiseAdd(size_t number)
{
	size_t mask = 1UL;
	
	while ( mask & number)
	{
		number ^= mask;
		mask <<= 1UL;
	}
	
	return number ^ mask;
}
