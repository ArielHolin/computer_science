/*******************************************************************************
*  vector.c                                                                    *
*  Author: Ariel                                                               * 
*  Reviewer:                                                                   *
*******************************************************************************/
#include <stddef.h> /* size_t                */
#include <stdlib.h> /* malloc, realloc, free */
#include <assert.h> /* assert                */

#include "../include/vector.h"

#define GF 2

#define MAX(a, b) ( a > b ? a : b )

enum return_status
{
	FAILURE = -1,
	SUCCESS = 0
};

struct vector 
{
	void **data;           /* data is saved by reference  */
 	size_t size;           /* number of occupied elements */
	size_t capacity;     
	size_t init_capacity;  /* minimal possible capacity. initialized by user. */
};

/********** VectorCreate ******************************************************/

vector_ty *VectorCreate(size_t capacity)
{
	vector_ty *new_vector = (vector_ty *)malloc(sizeof(vector_ty));
	
	if ( !new_vector )
	{
		return NULL;
	}
	
	new_vector->data = (void **)malloc(capacity * sizeof(void *));
	
	if ( !new_vector->data )
	{
		free(new_vector);
		new_vector = NULL;
		
		return NULL;
	}
	
	*new_vector->data = NULL;
	new_vector->capacity = capacity;
	new_vector->init_capacity = capacity;
	new_vector->size = 0;
	
	return new_vector;
}

/********** Vector Destroy ****************************************************/

void VectorDestroy(vector_ty *vector)
{
	assert(vector);
	
	free(vector->data);
	vector->data = NULL;
	
	free(vector);
	vector = NULL;
}

/******** Vector Size *********************************************************/

size_t VectorSize(const vector_ty *vector)
{
	assert(vector);
	
	return vector->size;
}

/******** VectorCapacity ******************************************************/

size_t VectorCapacity(const vector_ty *vector)
{
	assert(vector);
	
	return vector->capacity;
}

/******** VectorShrinkToFit ***************************************************/

status_ty VectorShrinkToFit(vector_ty *vector)
{
	void **old_address = vector->data;
	
	assert(vector);
	
	vector->data = (void **)realloc(vector->data, 
	                                (vector->size) * sizeof(void *));
	
	if ( NULL == vector->data )
	{
		vector->data = old_address;
		return FAILURE;
	}
	 
	vector->capacity = vector->size;
	vector->init_capacity = vector->size;
	return SUCCESS;
}

/********** VectorGetVal ******************************************************/

void *VectorGetVal (const vector_ty *vector, size_t index)
{
	assert(vector);
	assert(index <= vector->size);
	
	return vector->data[index];
}

/********* VectorSetVal *******************************************************/

void *VectorSetVal (vector_ty *vector, size_t index, void *element )
{
	assert(vector);
	assert(element);
	assert(index <= vector->size);
	
	vector->data[index] = element;
	return vector->data[index];
}

/********* VectorPushBack *****************************************************/

status_ty VectorPushBack(vector_ty *vector, void *element)
{
	assert(vector);
	assert(element);
	
	if ( 0 == vector->capacity)
	{
		vector->capacity = 1;
	}
	
	if ( vector->size == vector->capacity )
	{
		void **old_address = vector->data;
		vector->capacity = (vector->capacity) * GF;
		vector->data = (void **)realloc(vector->data, 
		                               (vector->capacity) * sizeof(void *));
		
		if ( NULL == vector->data )
		{
			vector->data = old_address;
			return FAILURE;
		}
	}
	
	vector->data[vector->size] = element;
	++vector->size;
	return SUCCESS;
}

/********** VectorPopBack ****************************************************/

status_ty VectorPopBack(vector_ty *vector)
{	
	assert(vector);
	assert( vector->size > 0 );
	
	if ( vector->size <= (vector->capacity / (GF*GF)) )
	{
		void *old_address = vector->data;
		vector->capacity = MAX(((vector->capacity) / GF), vector->init_capacity);
		vector->data = (void **)realloc(vector->data, 
		                               (vector->capacity) * sizeof(void *));
		
		if ( NULL == vector->data )
		{
			vector->data = old_address;
			return FAILURE;
		}
	}
	
	--vector->size;
	return SUCCESS;
}

/********* VectorReserve ******************************************************/

status_ty VectorReserve(vector_ty *vector, size_t new_capacity)
{
	void **old_address = vector->data;
	
	assert(vector);

	if ( new_capacity > vector->capacity )
	{
		vector->capacity = new_capacity;
		vector->init_capacity = new_capacity;
		vector->data = (void **)realloc(vector->data, 
	    	                           (vector->capacity) * sizeof(void *));
		
		if ( NULL == vector->data )
		{
			vector->data = old_address;
			return FAILURE;
		}
	}
	return SUCCESS;
}

