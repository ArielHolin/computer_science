/************************************************
*  String.h
*  Author: Ariel Holin
*  Reviewer: Eli
*************************************************/

#ifndef __STRING_H__
#define __STRING_H__

/* Receives string and return its length */
size_t StrLen(const char *s);

/* Receives 2 strings and return 0 if they are same, int>0 if s1>s2, int<0 if
   s1<s2 */
int StrCmp(const char *s1, const char *s2);

/* Copies the string pointed to by src, including '\0' */
char *StrCpy(char *dest, const char *src);

/* Same as StrCpy, except that at most n bytes of src are copied. */
char *StrnCpy(char *dest, const char *src, size_t n);

/* Performs byte-by-byte comparison between 2 strings, ignoring the case of the
   characters. return int>0 if s1>s2, int<0 if s1<s2, 0 if s1=s2.
   s1<s2 or s2<s1 determined by alphabetical order. */
int StrCaseCmp(const char *s1, const char *s2);

/* Returns a pointer to the first occurence of char c in s. */
char *StrChr(const char *s, int c);

/* Returns a pointer to a new string which is a duplicate of s */
char *StrDup(const char *s);

/* appends the src string to the dest string, overwriting the terminating null 
   byte ('\0') at the end of dest, and then adds a terminating null byte. */
char *StrCat(char *dest, const char *src);

/* Same as StrCat but will use at most n bytes from src, and doesn't need to
   be null terminated. */
char *StrnCat(char *dest, const char *src, size_t n);

/* The strstr() function finds the first occurrence of the substring needle 
   in the string haystack. */
char *StrStr(const char *haystack, const char *needle);

/* calculates the length (in bytes) of the initial segment of s which 
   consists entirely of bytes in accept. */
size_t StrSpn(const char *s, const char *accept);

#endif  /* __STRING_H__ */
