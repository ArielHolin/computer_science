/*******************************************************************************
*  reverse_words.c quiz                                                        *
*  Author: Ariel                                                               *
*******************************************************************************/
#include <stddef.h>  /* size_t */
#include <string.h>  /* strlen */
#include <stdio.h>   /* printf */

void ReverseWords(char *str);
static void ReverseStr(char *str);
static void ReverseSingleStr(char *str_start, char *str_end);
static void SwapChar(char *chr1, char *chr2);

/********* Main ***************************************************************/

int main(void)
{
	char str1[] = "Hello world";
	char str2[] = "My name is Ariel";
	
	ReverseWords(str1);
	ReverseWords(str2);
	return 0;
}

/********** Function Implementations ******************************************/

void ReverseWords(char *str)
{
		size_t str_len = strlen(str);
		size_t i = 0;
		char *str_start = str;
		char *str_end = str;
		
		ReverseStr(str);
		
		for( i = 0; i < str_len; ++i )
		{
			if( ' ' == *str_end )
			{
				ReverseSingleStr(str_start, str_end - 1);
				
				++str_end;
				str_start = str_end;
			}
			
			else
			{
				++str_end;
			}
		}
		
		ReverseSingleStr(str_start, str_end - 1);
		
		printf("%s\n", str);
}

static void ReverseStr(char *str)
{
	size_t str_len = strlen(str);
	char *str_start = str;
	char *str_end = str + str_len - 1;
	
	while( str_start < str_end )
	{
		SwapChar(str_start, str_end);
		++str_start;
		--str_end;
	}
}

static void ReverseSingleStr(char *str_start, char *str_end)
{
	while( str_start < str_end )
	{
		SwapChar(str_start, str_end);
		++str_start;
		--str_end;
	}
}

static void SwapChar(char *chr1, char *chr2)
{
	char tmp = *chr1;
	*chr1 = *chr2;
	*chr2 = tmp;
}
