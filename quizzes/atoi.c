/*******************************************************************************
*  Quiz - Atoi                                                                 *
*  Author: Ariel                                                               *
*******************************************************************************/
#include <stddef.h>  /* size_t */
#include <string.h>  /* strlen */
#include <stdio.h>   /* printf */

#define TEN             10
#define NON_BASE_DIGIT -1

enum sgn_values
{
	NEGATIVE = -1,
	POSITIVE
};

int Atoi(const char *str, size_t base);
size_t GetDigit(size_t chr, size_t base);
long PowOfTen(size_t number);

int main(void)
{
	char str[7] = "-305607";
	
	printf("%d\n", Atoi(str, 10));
	return 0;
}

int Atoi(const char *str, size_t base)
{
	int sgn_flag = POSITIVE;
	size_t curr_digit;
	size_t str_len = strlen(str);
	int result = 0;
	
	if ('-' == *str)
	{
		sgn_flag = NEGATIVE;
		++str;
		str_len -= 1;
	}	
	
	while ( *str )
	{
		curr_digit = GetDigit(*str, base);
		result += curr_digit * PowOfTen(str_len - 1);
		++str;
		str_len -= 1;
	}
	
	if ( NEGATIVE == sgn_flag )
	{
		result = -result;
	}
	
	return result;
}

size_t GetDigit(size_t chr, size_t base)
{
	size_t max_digit;
	
	if ( base <= TEN )
	{
		max_digit = base + '0';
	}
	else
	{
		max_digit = base - TEN + 'a';
	}
	
	if ( (chr >= '0' && chr <= '9') && (chr < max_digit) )
	{
		return chr - '0';
	}
	
	if ( (chr >= 'a' && chr <= 'z') && (chr < max_digit) )
	{
		return chr - 'a' + TEN;
	}
	
	return NON_BASE_DIGIT;
}

long PowOfTen(size_t number)
{
	long result = 1;
	size_t i = 0;
	
	for ( i = 0; i < number; ++i )
	{
		result *= TEN;
	}
	
	return result;
}
