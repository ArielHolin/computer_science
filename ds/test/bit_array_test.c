/*******************************************************************************
*  bit_array_test.c                                                            *
*  Author: Ariel                                                               *
*  Reviewer: Bnaya                                                             *
*******************************************************************************/
#include <stdio.h>  /* printf   */
#include <string.h> /* strcmp   */
#include <limits.h> /* CHAR_BIT */
#include <stddef.h> /* size_t   */

#include "../include/bit_array.h"

#define HEXA_ONES 0xffffffffffffffff
#define NUM_OF_BITS (sizeof(bit_arr_ty) * CHAR_BIT)

#define R2(n)     n,     n + 2*64,     n + 1*64,     n + 3*64
#define R4(n) R2(n), R2(n + 2*16), R2(n + 1*16), R2(n + 3*16)
#define R6(n) R4(n), R4(n + 2*4 ), R4(n + 1*4 ), R4(n + 3*4 )

#define FOUR_ELEMENTS  4
#define THREE_ELEMENTS 3

static void TestBitsArrResetAll(void);
static void TestBitsArrSetAll(void);
static void TestBitsArrSetOn(void);
static void TestBitsArrSetOff(void);
static void TestBitsArrGetVal(void);
static void TestBitsArrToString(void);
static void TestBitsArrRotR(void);
static void TestBitsArrRotL(void);
static void TestBitsArrCountOn(void);
static void TestBitsArrCountOff(void);
static void TestBitsArrFlip(void);
static void TestBitsArrSetBit(void);
static void TestBitsArrMirror(void);

int main(void)
{
	TestBitsArrResetAll();
	TestBitsArrSetAll();
	TestBitsArrSetOn();
	TestBitsArrSetOff();
	TestBitsArrGetVal();
	TestBitsArrToString();
	TestBitsArrRotR();
	TestBitsArrRotL();
	TestBitsArrCountOn();
	TestBitsArrCountOff();
	TestBitsArrFlip();
	TestBitsArrSetBit();
	TestBitsArrMirror();
	return 0;
}

/*********** Test ResetAll ****************************************************/

static void TestBitsArrResetAll(void)
{
	bit_arr_ty all_set_bits= HEXA_ONES;
	
	if ( 0 == BitsArrResetAll(all_set_bits) )
	{
		printf("TestBitsArrResetAll() Success!\n----------\n");
	}
	else
	{
		printf("TestBitsArrResetAll() Fail!\n----------\n");
	}
}

/********* Test SetAll ********************************************************/

static void TestBitsArrSetAll(void)
{
	bit_arr_ty all_off_bits = (bit_arr_ty)0;
	
	if ( HEXA_ONES == BitsArrSetAll(all_off_bits) )
	{
		printf("TestBitsArrSetAll() Success!\n----------\n");
	}
	else
	{
		printf("TestBitsArrSetAll() Fail!\n----------\n");
	}
}

/************ Test SetOn ******************************************************/

static void TestBitsArrSetOn(void)
{
	bit_arr_ty zero_mask = (bit_arr_ty)0;
	bit_arr_ty results[] = {0x0000000000000001, 0x1000000000000000, 
	                        0x8000000000000000};
	size_t positions[] = {0, 60, 63};
	size_t i = 0;
	
	for ( i = 0; i < THREE_ELEMENTS; ++i )
	{
		if ( BitsArrSetOn(zero_mask, positions[i]) != results[i] )
		{
			printf("TestBitsArrSetOn() Fail!\n----------\n");
			return;
		}
	}
	
	printf("TestBitsArrSetOn() Success!\n----------\n");
}

/************ Test SetOff *****************************************************/

static void TestBitsArrSetOff(void)
{
	bit_arr_ty bit_arrays[] = {0x0000000000000001, 0x1000000000000000, 
	                        0x8000000000000000};                  
	size_t positions[] = {0, 60, 63};
	size_t i = 0;
	
	for ( i = 0; i < THREE_ELEMENTS; ++i )
	{
		if ( 0 != BitsArrSetOff(bit_arrays[i], positions[i]) )
		{
			printf("TestBitsArrSetOff() Fail!\n----------\n");
			return;
		}
	}
	
	printf("TestBitsArrSetOn() Success!\n----------\n");
}

/************ Test GetVal *****************************************************/

static void TestBitsArrGetVal(void)
{
	bit_arr_ty bit_arrays[] = {0x0000000000000001, 0x1000000000000000, 
	                        0x8000000000000000};                  
	size_t positions[] = {0, 60, 63};
	size_t zero_positions[] = {45, 12, 29};
	size_t i = 0;
	
	for ( i = 0; i < THREE_ELEMENTS; ++i )
	{
		if ( (1 != BitsArrGetVal(bit_arrays[i], positions[i])) ||  
		     (0 != BitsArrGetVal(bit_arrays[i], zero_positions[i])) )
		{
			printf("TestBitsArrGetVal() Fail!\n----------\n");
			return;
		}
	}
	
	printf("TestBitsArrGetVal() Success!\n----------\n");
}

/************ Test ToString ***************************************************/

static void TestBitsArrToString(void)
{
	bit_arr_ty bit_array = 0xce99d8f7ce99d8f7;
	char dest[NUM_OF_BITS];
	
	if ( 0 != strcmp(BitsArrToString(bit_array, dest), 
	                 "1100111010011001110110001111011111001110100110011101100011110111"))
	{
		printf("TestBitsArrToString() Fail!\n----------\n");
	}
	else
	{
		printf("TestBitsArrToString() Success!\n----------\n");
	}                 
}

/*********** Test RotR ********************************************************/

static void TestBitsArrRotR(void)
{
	bit_arr_ty bit_array = 0xce99d8f7ce99d8f7;
	size_t i = 0;
	size_t num_of_rots[] = {0, 11, 27, 64};
	char dest[NUM_OF_BITS];
	char results[][NUM_OF_BITS + 1] = 
		{"1100111010011001110110001111011111001110100110011101100011110111\0",
         "0001111011111001110100110011101100011110111110011101001100111011\0",
         "1101001100111011000111101111100111010011001110110001111011111001\0",
         "1100111010011001110110001111011111001110100110011101100011110111\0"};
	
	for ( i = 0; i < FOUR_ELEMENTS; ++i )
	{
		if ( 0 != strcmp(BitsArrToString(BitsArrRotR(bit_array, num_of_rots[i]), dest),
		             	results[i]))
		{
			printf("TestBitsArrRotR() Fail!\n----------\n");	
			return;
		}
	}
	
	printf("TestBitsArrRotR() Success!\n----------\n");
}

/************* TestRotL *******************************************************/

static void TestBitsArrRotL(void)
{
	bit_arr_ty bit_array = 0xce99d8f7ce99d8f7;
	size_t i = 0;
	size_t num_of_rots[] = {0, 11, 27, 64};
	char dest[NUM_OF_BITS];
	char results[][NUM_OF_BITS + 1] = 
		{"1100111010011001110110001111011111001110100110011101100011110111\0",
         "1100111011000111101111100111010011001110110001111011111001110100\0",
         "1011111001110100110011101100011110111110011101001100111011000111\0",
         "1100111010011001110110001111011111001110100110011101100011110111\0"};

	for ( i = 0; i < FOUR_ELEMENTS; ++i )
	{
		if ( 0 != strcmp(BitsArrToString(BitsArrRotL(bit_array, num_of_rots[i]), dest),
		             	results[i]))
		{
			printf("TestBitsArrRotL() Fail!\n----------\n");	
			return;
		}
	}
	
	printf("TestBitsArrRotL() Success!\n----------\n");
}

/********* Test CountOn *******************************************************/

static void TestBitsArrCountOn(void)
{
	bit_arr_ty bit_arrays[] = {0xb800a60010000051,
							   0x0000020020008000,
							   0x0000000000000000,
							   0xffffffffffffffff};
	
	size_t counts[] = {12, 3, 0, 64};
	size_t i = 0;
	
	for ( i = 0; i < FOUR_ELEMENTS; ++i )
	{
		if ( BitsArrCountOn(bit_arrays[i]) != counts[i] )
		{
			printf("TestBitsArrCountOn() Fail!\n----------\n");
			return;
		}
	}
							   
	printf("TestBitsArrCountOn() Success!\n----------\n");						
}

/*********** Test CountOff ****************************************************/

static void TestBitsArrCountOff(void)
{
	bit_arr_ty bit_arrays[] = {0xb800a60010000051,
							   0x0000020020008000,
							   0x0000000000000000,
							   0xffffffffffffffff};
	
	size_t counts[] = {52, 61, 64, 0};
	size_t i = 0;
	
	for ( i = 0; i < FOUR_ELEMENTS; ++i )
	{
		if ( BitsArrCountOff(bit_arrays[i]) != counts[i] )
		{
			printf("TestBitsArrCountOff() Fail!\n----------\n");
			return;
		}
	}
							   
	printf("TestBitsArrCountOff() Success!\n----------\n");						
}

/*********** Test Flip ********************************************************/

static void TestBitsArrFlip(void)
{
	bit_arr_ty bit_array = 0xce99d8f7ce99d8f7;
	
	size_t positions[] = {0, 13, 41, 57};
	size_t i = 0;
	char results[][NUM_OF_BITS + 1] = 
		{"1100111010011001110110001111011111001110100110011101100011110110\0",
         "1100111010011001110110001111011111001110100110011111100011110111\0",
         "1100111010011001110110101111011111001110100110011101100011110111\0",
         "1100110010011001110110001111011111001110100110011101100011110111\0"};
	char dest[NUM_OF_BITS];
	
	
	for ( i = 0; i < FOUR_ELEMENTS; ++i )
	{
		if ( 0 != strcmp(BitsArrToString(BitsArrFlip(bit_array, positions[i]), dest),
		                 results[i]))
		{
			printf("TestBitsArrFlip() Fail!\n----------\n");
			return;
		}
	}
	
	printf("TestBitsArrFlip() Success!\n----------\n");
}

/*********** Test SetBit ******************************************************/

static void TestBitsArrSetBit(void)
{
	bit_arr_ty bit_array = 0xce99d8f7ce99d8f7;
	
	size_t positions[] = {0, 13, 41, 57};
	size_t states[] = {0, 1, 1, 1};
	size_t i = 0;
	char results[][NUM_OF_BITS + 1] = 
		{"1100111010011001110110001111011111001110100110011101100011110110\0",
         "1100111010011001110110001111011111001110100110011111100011110111\0",
         "1100111010011001110110101111011111001110100110011101100011110111\0",
         "1100111010011001110110001111011111001110100110011101100011110111\0"};
	char dest[NUM_OF_BITS];
	
	for ( i = 0; i < FOUR_ELEMENTS; ++i )
	{
		if ( 0 != strcmp(BitsArrToString(BitsArrSetBit(bit_array, positions[i], states[i]), dest),
		                 results[i]))
		{
			printf("TestBitsArrSetBit() Fail!\n----------\n");
			return;
		}
	}
	
	printf("TestBitsArrSetBit() Success!\n----------\n");
}

/******* Test Mirror **********************************************************/

static void TestBitsArrMirror(void)
{
	bit_arr_ty bit_array = 0xce99d8f7ce99d8f7;
	char dest[NUM_OF_BITS];
	
	if ( 0 != strcmp(BitsArrToString(BitsArrMirror(bit_array), dest),
	                 "1110111100011011100110010111001111101111000110111001100101110011"))
	{
		printf("TestBitsArrMirror() Fail!\n----------\n");
		return;
	}
	           
	printf("TestBitsArrMirror() Success!\n----------\n");      
}
