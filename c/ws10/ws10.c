/*******************************************************************************
*  ws10.c
*  Author: Ariel
*  Reviewer:
*******************************************************************************/
#include <string.h> /* strlen */
#include <stdio.h>  /* printf */
#include <stddef.h> /* size_t */

#include "ws10.h"

#define ITOA_GAP      48
#define TEN           10
#define NON_BASE_DIG  -1
#define NUM_OF_ASCII  256	

enum sgn_values
{
	NEGATIVE = -1,
	POSITIVE
};

enum num_of_chars
{
	NO_CHARS = 0,
	ONE_CHAR,	
	TWO_CHARS
};

enum endiann_valus
{
	MIDDLE = -1,
	LITTLE,
	BIG
};

/* Helper functions for exercise 1 */
static char *ReverseStr(char *str, size_t str_len);
static void SwapChar(char *str1, char *str2);

static size_t GetDigit(char chr, size_t base);
static size_t PowOfBase(size_t power, size_t base);

/* Helper function for exercise 2 */
static void InitAsciiLut(size_t lut[]);

/******************** Exercise 1 **********************************************/

/*********************** Itoa function, base 10 *******************************/

char *ItoaBase10 (int number, char *str)
{
	char *start_str = str;
	size_t str_len;
	size_t res;
	int sgn_flag = POSITIVE;
		
	if ( 0 > number )
	{
		sgn_flag = NEGATIVE;
		number = -number;
	}
	
	while ( 0 < number )
	{
		res = number % TEN;
		*str = res + ITOA_GAP;
		++str;
		number /= TEN;
	}
	
	if ( NEGATIVE == sgn_flag )
	{
		*str = '-';
	}
	
	str_len = strlen(start_str);
	
	return ReverseStr(start_str, str_len);
}

/* Reverse the order of character appearance in str. */
static char *ReverseStr(char *str, size_t str_len)
{
	char *start_str = str;
	char *end_str = str + (str_len - 1);
	
	while (start_str < end_str)
	{
		SwapChar(start_str, end_str);
		++start_str;
		--end_str;
	}
	
	return str;
}

/* Swapping two chars. */
static void SwapChar(char *str1, char *str2)
{
	char tmp = *str1;
	*str1 = *str2;
	*str2 = tmp;
}

/****************** Atoi function, base up to 36 ******************************/

int AtoiGenBase(const char *str, size_t base)
{
	char *str_runner = (char *)str;
	size_t str_len;
	size_t i = 0;
	int sgn_flag = POSITIVE;
	int result = 0;
	int curr_digit = 0;
	
	if ( '-' == *str_runner )
	{
		sgn_flag = NEGATIVE;
		++str_runner;
	}
	
	str_len = strlen(str_runner);
	
	str_runner = ReverseStr(str_runner, str_len);
	
	for ( i = 0; i < str_len; ++i )
	{
		
		curr_digit = GetDigit(*str_runner, base);
		
		if ( NON_BASE_DIG == curr_digit )
		{
			return 0;
		}
		
		result += curr_digit * PowOfBase(i, base);
		++str_runner;
	}
	
	if ( NEGATIVE == sgn_flag )
	{
		result = -result;
	}
	
	return result;
}

/* Return the digits corresponding to chr according to base. */
static size_t GetDigit(char chr, size_t base)
{
	int max_digit;
	
	if ( TEN >= base )
	{
		max_digit = base + '0';
	}
	else
	{
		max_digit = base - TEN + 'a';
	}
	
	if ( (chr >= '0' && chr <= '9') && (chr < max_digit))
	{
		return chr - '0';
	}
	
	if ( (chr >= 'a' && chr <= 'z') && (chr < max_digit) )
	{
		return chr - 'a' + TEN;
	}
	
	return NON_BASE_DIG;
}

/* Return base ^ number. */
static size_t PowOfBase(size_t power, size_t base)
{
	size_t i = 0;
	size_t result = 1;
	
	for ( i = 0; i < power; ++i)
	{
		result *= base;
	}
	
	return result;
}

/************************** Exercise 2 ****************************************/

void PrintIntersection(char *arr1, char *arr2, char *arr3)
{
	size_t ascii_lut[NUM_OF_ASCII];
	size_t i = 0;
	
	InitAsciiLut(ascii_lut);
	
	while ( *arr1 )
	{
		if ( NO_CHARS == ascii_lut[(int)*arr1] )
		{
			ascii_lut[(int)*arr1] += ONE_CHAR;
		}
		++arr1;
	}
	
	while ( *arr2 )
	{
		if ( ONE_CHAR == ascii_lut[(int)*arr2] )
		{
			ascii_lut[(int)*arr2] += ONE_CHAR;
		}
		++arr2;
	}
	
	while ( *arr3 )
	{
		if ( TWO_CHARS == ascii_lut[(int)*arr3] )
		{
			ascii_lut[(int)*arr3] -= ONE_CHAR;
		}
		++arr3;
	}
	
	for ( i = 0; i < NUM_OF_ASCII; ++i )
	{
		if ( TWO_CHARS == ascii_lut[i] )
		{
			printf("%c ",(char) i);
		}	
	}
}


/* Initializes lut to zeros. */
static void InitAsciiLut(size_t lut[])
{
	size_t i = 0;
	
	for ( i = 0; i < NUM_OF_ASCII; ++i)
	{
		lut[i] = 0;
	}
}

/************************** Exercise 3 ****************************************/

size_t EndiannCheck(void)
{
	int val = 1;
	unsigned char *val_address = (unsigned char *)&val;
	
	if ( 1 == (size_t)*val_address )
	{
		return BIG;
	}
	
	if ( 0 == (size_t)*val_address )
	{
		return LITTLE;
	}
	
	return MIDDLE;
}








