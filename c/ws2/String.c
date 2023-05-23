/*********************************************************
*  String.c
*  Author: Ariel Holin
*  Reviewer: Eli
**********************************************************/

#include <stddef.h>  /* size_t */
#include <stdio.h>   /* puts */
#include <ctype.h>   /* tolower */
#include <assert.h>  /* assert */
#include <stdlib.h>  /* free */
#include <string.h>  /* memcmp */
#include "String.h"  

/* Receives const string and return string length */
size_t StrLen(const char *str)
{
	size_t len = 0;
	
	while (*str)
	{
		++str;
		++len;
	} 
	
	return len;
}

/* Receives two strings: if same return 0, else if s1>s2 return int > 0, else
   return int < 0 */
int StrCmp(const char *str1, const char *str2)
{
	while (*str1 && *str1==*str2)
	{
		++str1;
		++str2;
	}
	
	return *str1 - *str2;
}

/* Copies the string pointed to by src, including '\0' */
char *StrCpy(char *dest, const char *src)
{	
	char *dest_cpy = dest;
	
	assert(dest!=NULL && src!= NULL);
	
	while (*src)
	{
		*dest = *src;
		++dest;
		++src;
	}
	
	*dest = '\0';
	
	return dest_cpy;
}

/* Same as StrCpy, except that at most n bytes of src are copied. */
char *StrnCpy(char *dest, const char *src, size_t size)
{
	char *dest_cpy = dest;
	size_t i = 0;
	
	assert(dest!=NULL && src!=NULL);
	
	for (i = 0; i<size || *src=='\0'; ++i)
	{
		*dest = *src;
		++dest;
		++src;
	}
	
	for(; i < size; i++)
	{
		*dest = '\0';
	}
	
	*dest = '\0';
	
	return dest_cpy;
}

/* Performs byte-by-byte comparison between 2 strings, ignoring the case of the
   characters. return int>0 if s1>s2, int<0 if s1<s2, 0 if s1=s2.
   s1<s2 or s2<s1 determined by alphabetical order. */
int StrCaseCmp(const char *str1, const char *str2)
{
	assert(str1!=NULL && str2!=NULL);	
		
	while (*str1 && tolower(*str1)==tolower(*str2))
	{
		++str1;
		++str2;
	}
	
	return tolower(*str1) - tolower(*str2);
}

/* Returns a pointer to the first occurence of char c in s. */
char *StrChr(const char *str, int chr)
{
	char char_c = chr;
	
	assert(str != NULL);
	
	while (*str && *str!=char_c)
	{
		++str;
	}
	
	return (*str == char_c) ? (char *)str : NULL;
}

/* Returns a pointer to a new string which is a duplicate of s */
char *StrDup(const char *str)
{
	char *res = (char *)malloc(StrLen(str) + 1);
	
	assert (str != NULL);

	res = StrCpy(res, str);
	return res;
}

/* appends  the src string to the dest string, overwriting the terminating null byte
   ('\0') at the end of dest, and then adds a terminating null byte. */
char *StrCat(char *dest, const char *src)
{
	size_t dest_size = StrLen(dest);
	char *dest_end_ptr = dest + dest_size;
	
	while (*src)
	{
		*dest_end_ptr = *src;
		++dest_end_ptr;
		++src;
	}
	
	*dest_end_ptr = '\0';
	
	return dest;
}


/* Same as StrCat but will use at most n bytes from src, and doesn't need to
   be null terminated. */
char *StrnCat(char *dest, const char *src, size_t size)
{
	size_t dest_size = StrLen(dest);
	char *dest_end_ptr = dest + dest_size;
	size_t i = 0;
	
	for(i = 0; i<size || *src=='\0'; ++i)
	{
		*dest_end_ptr = *src;
		++dest_end_ptr;
		++src;
	}
	
	for(; i < size; ++i)
	{
		*dest_end_ptr = '\0';
	}
	
	return dest;
}

/* The strstr() function finds the first occurrence of the substring needle 
   in the string haystack. */
char *StrStr(const char *haystack, const char *needle)
{
	size_t needle_size = StrLen(needle);
	
	while (*haystack)
	{
		if (memcmp(haystack++, needle, needle_size) == 0)
		{
			return (char *)haystack - 1;
		}
	}
	
	return NULL;
}

/* calculates the length (in bytes) of the initial segment of s which 
   consists entirely of bytes in accept. */
size_t StrSpn(const char *str, const char *accept)
{
	size_t len = 0;
	
	while (*str && StrChr(accept, *str++))
	{
		++len;
	}
	
	return len;
}

