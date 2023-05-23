/*******************************************************************************
*  circular_buffer.c                                                           *
*  Author: Ariel                                                               *
*  Reviewer: Philip                                                            *
*******************************************************************************/
#include <stdlib.h>    /* malloc, free, abs */
#include <assert.h>    /* assert            */
#include <stddef.h>    /* size_t            */
#include <sys/types.h> /* ssize_t           */

#include "circular_buffer.h"

#define ILRD_FAILURE -1

#define OFFSETOF(TYPE, ELEMENT) ((size_t)&(((TYPE *)0)->ELEMENT))

struct cbuf
{
    char *read;
    char *write;
    size_t capacity;
    char arr[1];
};

/***** CircBuffCreate *********************************************************/

cbuf_ty *CircBuffCreate(size_t capacity)
{
	cbuf_ty *new_cbuf = (cbuf_ty *)malloc(OFFSETOF(cbuf_ty, arr) + 
	                                     (capacity * sizeof(char) + 1));
	
	if( !new_cbuf )
	{
		return NULL;
	}
	
	new_cbuf->capacity = capacity;
	new_cbuf->arr[0] = '\0';
	new_cbuf->read = &new_cbuf->arr[0];
	new_cbuf->write = &new_cbuf->arr[0];
	
	return new_cbuf;
}

/***** CircBuffDestroy ********************************************************/

void CircBuffDestroy(cbuf_ty *cbuf)
{
	assert(cbuf);
	
	free(cbuf);
}

/***** CircBuffFreeSpace ******************************************************/

size_t CircBuffFreeSpace(const cbuf_ty *cbuf)
{
	ssize_t diff = 0;
	
	assert(cbuf);
	
	diff = cbuf->write - cbuf->read;
	
	if( diff >= 0 )
	{
		return cbuf->capacity - diff;
	}
	
	return -(diff + 1);
}

/***** CircBuffBufsiz *********************************************************/

size_t CircBuffBufsiz(const cbuf_ty *cbuf)
{
	size_t free_space = 0;
	
	assert(cbuf);
	
	free_space = CircBuffFreeSpace(cbuf);
	
	return cbuf->capacity - free_space;
}

/***** CircBuffIsEmpty ********************************************************/

int CircBuffIsEmpty(const cbuf_ty *cbuf)
{
	size_t free_space = 0;
	
	assert(cbuf);
	
	free_space = CircBuffFreeSpace(cbuf);
	
	return free_space == cbuf->capacity;
}

/***** Helper Function - CircBuffGetNext **************************************/

static char *CircBuffGetNext(char *runner, size_t capacity, char *start_arr)
{
	return start_arr + ((runner - start_arr + 1) % (capacity + 1));
}

/***** CircBuffRead ***********************************************************/

ssize_t CircBuffRead(cbuf_ty *cbuf, void *dest, size_t num_bytes)
{
	size_t counter = 0;
	size_t cbuf_capacity = 0;
	
	/* Validate cbuf */
	assert(cbuf);
	
	cbuf_capacity = cbuf->capacity;
	
	/* If cbuf is empty */
	if( CircBuffIsEmpty(cbuf) )
	{
		return ILRD_FAILURE;
	}
	
	/* As long as cbuf is not empty, and we haven't reached num_bytes */
	while( !CircBuffIsEmpty(cbuf) && (counter != num_bytes))
	{
		/* Read from cbuf into dest */
		*(char *)dest = *cbuf->read;
		
		/* Update counter */
		++counter;
		/* Update dest */
		dest = (char *)dest + 1;
		/* Update next reading location */
		cbuf->read = CircBuffGetNext(cbuf->read, cbuf_capacity, &cbuf->arr[0]);
	}
	
	return counter;
}

/***** CircBuffWrite **********************************************************/

ssize_t CircBuffWrite(cbuf_ty *cbuf, const void *src, size_t num_bytes)
{
	size_t counter = 0;
	size_t write_ind = 0;
	size_t cbuf_capacity = 0;
	char *cbuf_next_write = NULL;
	
	/* Validate cbuf */
	assert(cbuf);
	
	/* Initialize writing index */
	write_ind = cbuf->write - &cbuf->arr[0];
	cbuf_capacity = cbuf->capacity;
	/* Initialize first cell next to current write pointer */
	cbuf_next_write = CircBuffGetNext(cbuf->write, cbuf_capacity, &cbuf->arr[0]);
	
	/* If cbuf is full */
	if( cbuf_next_write == cbuf->read )
	{
		return ILRD_FAILURE;
	}
	
	/* As long as cbuf isn't full, and we haven't reached num_bytes */
	while( (cbuf_next_write != cbuf->read) && (counter != num_bytes) )
	{
		/* Write into buffer from src */
		cbuf->arr[write_ind] = *(char *)src;
		
		/* Update counter */
		++counter;
		/* Update src */
		src = (char *)src + 1;
		/* Update location to write into */
		cbuf->write = CircBuffGetNext(cbuf->write, cbuf_capacity, 
		                              &cbuf->arr[0]);
		/* Update first cell next to current write pointer */		                              
		cbuf_next_write = CircBuffGetNext(cbuf->write, cbuf_capacity, 
		                                  &cbuf->arr[0]);
		/* Update writing index */
		write_ind = cbuf->write - &cbuf->arr[0];          
	}
	
	return counter;	
}
