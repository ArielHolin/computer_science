/*******************************************************************************
*  ws6.c
*  Author: Ariel
*  Reviewer: Bnaya
*******************************************************************************/
#include <stdio.h>   /* printf */
#include <assert.h>  /* assert */
#include <stddef.h>  /* size_t */
#include "ws6.h"

static unsigned int IsBitOn(int number, unsigned int bit);
static unsigned int FindMostLeftSetBit(unsigned int number);
static int PrintIntBits(unsigned int number);

/************************** long Pow2() ***************************************/

/* Receives two unsigned integers, and return x*(2^y) */
long Pow2(unsigned int x, unsigned int y)
{
	return x << y;
}

/*************************** Is Power Of 2 ************************************/

/* Receives unsigned int, return 1 if n is power of 2, 0 otherwise.
   Implemantation using while loop. */
int IsPowOf2Loop(unsigned int number)
{
	int set_bits = CountSetBits(number);
	
	if ( 1 == set_bits )
	{
		return 1;
	}
	
	return 0;
}

/* Same as function above, without using loop. */
int IsPowOf2NoLoop(unsigned int number)
{
	if ( 0 == number )
	{
		return 0;
	}
	
	if ( 0 == (number & (number-1)) )
	{
		return 1;
	}
	
	return 0;
}

/********************** Add 1 Without Artithmetic *****************************/

/* Adding one to number */
int AddOneNoArithmetic(int number)
{
	unsigned int cmp = 1;
	
	while ( number & cmp )
	{
		number = (number ^ cmp);
		cmp <<= 1;
	}
	
	number = number ^ cmp;
	
	return number;
}

/*********************** Array Of Ints ****************************************/

/* Receives array of unsigned ints and the array length, and prints only
   unsigned ints which has 3 set bits */
void Print3SetBitsUnsignedInts(unsigned int array[], size_t array_len)
{
	size_t i = 0;
	
	for ( i = 0; i < array_len; ++i)
	{
		if ( 3 == CountSetBits(array[i]) )
		{
			printf("%d\n", array[i]);
		}
	}
}

/********************* Byte Mirror ********************************************/

/* Reversing bits of an unsigned integer */
unsigned int ByteMirrorLoop(unsigned int number)
{
	unsigned int reverse_num = 0;
	unsigned int most_left_set_bit;
	unsigned int i = 0;
	
	if ( 0 == number )
	{
		return number;
	}
	
	most_left_set_bit = FindMostLeftSetBit(number);
	
	for ( i = 0; i < most_left_set_bit + 1; ++i)
	{
		if ( number & (1 << i) )
			{
				reverse_num |= ( 1 << (most_left_set_bit - i) );
			}
	}
	
	return reverse_num;
}

/* Reversing string of an unsigned integer, using lookup table */
unsigned int ByteMirrorLUT(unsigned int number)
{
    unsigned int lookuptable[256] = { R6(0), R6(2), R6(1), R6(3) };
    
    int reverse_num = 0;
  
     /* Reverse and then rearrange */ 
  
                   /* first chunk of 8 bits from right */
     reverse_num = lookuptable[ number & 0xff ]<<24 | 
  
                   /* second chunk of 8 bits from  right */ 
                   lookuptable[ (number >> 8) & 0xff ]<<16 | 
  
                   lookuptable[ (number >> 16 ) & 0xff ]<< 8 |
                   lookuptable[ (number >> 24 ) & 0xff ] ;
    
    return reverse_num;
}

/*********************  Bits Checking *****************************************/

/* checks if bits 2 and 6 are on, return 1 if yes, 0 otherwise */
int TwoAndSix(unsigned char chr)
{	
	return ( IsBitOn(chr, 2) & IsBitOn(chr, 6) );
}

/* checks if bits 2 or 6 are on, return 1 if yes, 0 otherwise */
int TwoOrSix(unsigned char chr)
{
	return (  IsBitOn(chr, 2) | IsBitOn(chr, 6) );
}

/* Switch bits number 3 and 5 */
int SwapBit3AndBit5(unsigned char chr)
{
	unsigned int buffer;
	unsigned int bit3 = (chr >> 2) & 1;
	unsigned int bit5 = (chr >> 4) & 1;
	
	buffer = bit3 ^ bit5;
	
	buffer = (buffer << 2) | (buffer << 4);
	
	return chr ^ buffer;
}

/******************** Finding Closest Divisible by 16 *************************/

/* Finds closest number (from bottom) that is divisible by 16 */
unsigned int FindClosestDivBy16(unsigned int number)
{
	return ((number >> 4) << 4);
}

/***************** Swap Two Variables *****************************************/

void Swap(int *number1, int *number2)
{
	*number1 = *number1 ^ *number2;
	*number2 = *number1 ^ *number2;
	*number1 = *number1 ^ *number2;
}

/******************* Count Set Bits *******************************************/

/* Receives a number and return the number of turned on bits. */
int CountSetBits(unsigned int number)
{
	int bit_counter = 0;
	
	while ( number )
	{
		bit_counter += ( number & 1 );
		number >>= 1;
	}
	
	return bit_counter;
}

int CountSetBitsNoLoop(unsigned int number)
{
	if ( number == 0 )
	{
		return 0;
	}
	
	return (number & 1) + CountSetBitsNoLoop( number >> 1 );
}

/*********************** Float Analysis ***************************************/

/* Receives float from user, and print its bits */
void PrintFloatBits(void)
{
	float user_input;
	int *user_input_add = NULL;
	
	printf("Insert Input: ");
	scanf("%f", &user_input);
	
	user_input_add = (int *)&user_input;
	
	PrintIntBits(*user_input_add);
}

/************************** Helper Functions **********************************/

/* Receives a number and bit number, return 1 if bit is on, 0 otherwise. */
static unsigned int IsBitOn(int number, unsigned int bit)
{
	return ( (number >> (bit - 1)) & 1 );
}

static unsigned int FindMostLeftSetBit(unsigned int number) /* number shouldn't be 0 */
{
	int location = 0;
	
	while (0 != CountSetBits(number))
	{
		++location;
		number >>= 1;
	}
	
	return location - 1;
}

/* Printing bits of an integer. */ 
static int PrintIntBits(unsigned int number)
{
	unsigned int most_left_set_bit;
	unsigned int i = 0;
	unsigned int byte_mirrored_number = ByteMirrorLoop(number);
	
	if ( 0 == number )
	{
		printf("0\n");
		return 0;
	}
	
	most_left_set_bit = FindMostLeftSetBit(number);
	
	for ( i = 0; i < most_left_set_bit + 1; ++i)
	{
		printf("%d", byte_mirrored_number&1);
		byte_mirrored_number >>= 1;
	}
	printf("\n");
	
	return 0;
}
