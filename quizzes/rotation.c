/*******************************************************************************
*  Quiz Rotation
*  Author: Ariel
*******************************************************************************/
#include <stddef.h>  /* size_t          */
#include <stdio.h>   /* printf          */
#include <string.h>  /* strcmp, strncmp */

size_t IsRotation1(char *string1, char *string2, size_t str_len);
void Swap(char *chr1, char *chr2);
size_t IsRotation(const char *string1, const char *string2);

int main(void)
{
	/*char string1[6] = {'1', '2', '3', '4', '5'};
	char string2[6] = {'5', '1', '2', '3', '4'};
	
	IsRotation(string1, string2, 5);*/
	
	IsRotation("aabcd", "abcda");
	return 0;
}

/* Receives two strings, and their size, and checks whether string2 is a 
   rotation of string2 */
size_t IsRotation1(char *string1, char *string2, size_t str_len)
{
	size_t i = 0;
	size_t j = 0;
	
	for ( i = 0; i < str_len; ++i)
	{
		for ( j = 0; j < str_len - 1; ++j)
		{
			Swap(&string1[j], &string1[j+1]);
		}
		
		if (0 == strcmp(string1, string2))
		{
			printf("String2 is a rotation of string1 :)\n");
			return 0;
		}	
	}
	
	printf("String2 is not a rotation of string1 :(\n");
	return 0;
}

/* Swaps two characters */
void Swap(char *chr1, char *chr2)
{
	char tmp = *chr1;
	*chr1 = *chr2;
	*chr2 = tmp;
}

/* My implemantation for idea from class */
size_t IsRotation(const char *string1, const char *string2)
{
	size_t block1_size;
	size_t block2_size;
	size_t string_len = strlen(string1);
	char *mid_string = NULL;
	char *start = (char *)string1;
	
	if ( string_len != strlen(string2) )
	{
		printf("String2 is not a rotation of string1 :(\n");
		return 1;
	}
	
	do
	{
		mid_string = strchr(start, *string2);
		
		if ( NULL == mid_string ) continue;
	
		block1_size = mid_string - string1;
		block2_size = string_len - block1_size;
		
		if ( 0 == strncmp(string1, string2 + block2_size, block1_size) &&
		     0 == strncmp(string1 + block1_size, string2, block2_size))
		{
			printf("String2 is a rotation of string1 :)\n");
			return 0;
		}
		++start;
	}
	while (mid_string);
	
	printf("String2 is not a rotation of string1 :(\n");
	return 1;
}
