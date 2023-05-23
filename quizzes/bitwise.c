/*******************************************************************************
*  Bitwise Quiz
*  Author: Ariel
*******************************************************************************/
#include <stddef.h>  /* size_t */
#include <assert.h>  /* assert */
#include <stdio.h>   /* printf */

int CountSetBitCouples(unsigned int number);
void TestCountSetBitCouples(void);

void Swap1(int *number1, int *number2);
void Swap2(int *number1, int *number2);
void Swap3(int *number1, int *number2);

int CountSetBits(unsigned long number);

int main(void)
{
	TestCountSetBitCouples();
	return 0;
}

/************************** Question 1 ****************************************/

/* Counting set bits couples in 1 byte */
int CountSetBitCouples(unsigned int number)
{
	unsigned int right_most_couple = 3;
	size_t i = 0;
	int counter = 0;
	
	for ( i = 0; i < 6; ++i)
	{
		if ( number == (number | right_most_couple ) )
		{
			++counter;
		}
		
		right_most_couple <<= 1;
	}
	
	return counter;
}

void TestCountSetBitCouples(void)
{
	assert ( 1 == CountSetBitCouples(11) );
	assert ( 3 == CountSetBitCouples(15) );
	assert ( 0 == CountSetBitCouples(18) );
	assert ( 2 == CountSetBitCouples(29) );
	assert ( 4 == CountSetBitCouples(95) );
	
	printf("TestCountSetBitCouples() Success!\n----------\n");
}

/************************* Question 2 *****************************************/

void Swap1(int *number1, int *number2)
{
	*number1 = *number1 ^ *number2;
	*number2 = *number1 ^ *number2;
	*number1 = *number1 ^ *number2;
}

void Swap2(int *number1, int *number2)
{
	int tmp = *number1;
	*number1 = *number2;
	*number2 = tmp;
}

void Swap3(int *number1, int *number2)
{
	*number1 = *number1 - *number2;
	*number2 = *number1 + *number2;
	*number1 = *number2 - *number1;
}

/************************ Question 3 ******************************************/

/* Counting set bits using a loop, such that the loop executes exactly the 
   the number of times as the set bits (and not loop through the whole number)*/
int CountSetBits(unsigned long number)
{
	int counter = 0;
	
	while ( number )
	{
		++counter;
		number = number & ( number - 1 );
	}
	
	
	return counter;
}



