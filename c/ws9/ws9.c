/*******************************************************************************
*  ws9.c                                                                       * 
*  Author: Ariel                                                               *
*  Reviewer: Maayan                                                            *
*******************************************************************************/
#include <stddef.h>  /* size_t */
#include <stdio.h>   /* printf */
#include <assert.h>  /* assert */

const size_t WORD_SIZE = sizeof(size_t);

void *Memset(void *s, int c, size_t n)
{
	unsigned char *s_runner_c = s;
	size_t *s_runner_sizet = s;
	size_t word_chunk = 0;
	size_t i = 0;
	
	assert (s);
	
	for ( i = 0; i < WORD_SIZE; ++i)
	{
		*((unsigned char *)&word_chunk + i) = (unsigned char)c;
	}
	
	if ( WORD_SIZE <= n )
	{
		while ( (size_t)s_runner_c & (WORD_SIZE - 1) )
		{
			*s_runner_c = (unsigned char)c;
			++s_runner_c;
			--n;
		}
		
		s_runner_sizet = (size_t *)s_runner_c;
		
		while ( WORD_SIZE <= n )
		{
			*s_runner_sizet = word_chunk;
			++s_runner_sizet;
			n -= WORD_SIZE;
		}
		
		s_runner_c = (unsigned char *)s_runner_sizet;
	}
	
	while ( 0 < n )
	{
		*s_runner_c = (unsigned char)c;
		++s_runner_c;
		--n;
	}
	
	return s;
}

void *Memcpy(void *dest, const void *src, size_t n)
{
	unsigned char *src_runner = (void *)src;
	unsigned char *dest_runner_c = dest;
	size_t *dest_runner = dest;
	
	assert (dest);
	assert (src);
	
	if ( WORD_SIZE <= n )
	{
		while ( (size_t)dest_runner_c & (WORD_SIZE - 1) )
		{
			*dest_runner_c = *src_runner;
			++dest_runner_c;
			++src_runner;
			--n;
		}
		
		dest_runner = (size_t *)dest_runner_c;
		
		while ( WORD_SIZE <= n )
		{
			*dest_runner = *((size_t *)src_runner);
			++dest_runner;
			src_runner += WORD_SIZE;
			n -= WORD_SIZE;
		}
	
		dest_runner_c = (unsigned char *)dest_runner;
	}
	
	while ( 0 < n )
	{
		*dest_runner_c = *src_runner;
		++dest_runner_c;
		++src_runner;
		--n;
	}
	
	return dest;
}

void *Memmove(void *dest, const void *src, size_t n)
{
	unsigned char *dest_runner_c = dest;
	unsigned char *src_runner_c = (void *)src;

	assert (dest);
	assert (src);
	
	if ( dest < src )
	{
		return Memcpy(dest, src, n);
	}
	
	dest_runner_c += (unsigned char)n - 1;
	src_runner_c += (unsigned char)n - 1;
	
	while ( 0 < n )
	{	
		*dest_runner_c = *src_runner_c;
		
		--dest_runner_c;
		--src_runner_c;
		--n;
	}
	
	return dest;
}
