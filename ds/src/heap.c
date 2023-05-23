/*******************************************************************************
*  heap.c                                                                      *
*  Author: Ariel                                                               *
*  Reviewer: Philip                                                            *
*******************************************************************************/
#include <stdlib.h> /* malloc, free */
#include <assert.h> /* assert       */
#include <stddef.h> /* size_t       */

#include "heap.h"
#include "vector.h"

enum status
{
	ILRD_FAILURE = -1,
	ILRD_SUCCESS = 0
};

struct heap
{
    heap_cmp_func_ty cmp_func;
    vector_ty *heap_vector;
};

static void HeapifyDown(heap_ty *heap, size_t start_ind);
static void HeapifyUp(heap_ty *heap, size_t limit_ind);
static void SwapVectorVals(vector_ty *vector, void *elem1, size_t ind1, 
                                                      void *elem2, size_t ind2);

/* Function declaration for compilation - Pseuso Code only */                                                      
static void HeapSort(heap_ty *heap);

/************* HeapCreate *****************************************************/

heap_ty *HeapCreate(heap_cmp_func_ty cmp_func, size_t capacity)
{
	heap_ty *new_heap = NULL;
	
	assert(cmp_func);
	
	new_heap = (heap_ty *)malloc(sizeof(heap_ty));
	
	if(!new_heap)
	{
		return NULL;
	}
	
	new_heap->heap_vector = VectorCreate(capacity);
	
	if(!new_heap->heap_vector)
	{
		free(new_heap);
		new_heap = NULL;
		
		return NULL;
	}
	
	new_heap->cmp_func = cmp_func;
	
	return new_heap;
}

/************* HeapDestroy ****************************************************/

void HeapDestroy(heap_ty *heap)
{
	if(!heap)
	{
		return;
	}
	
	VectorDestroy(heap->heap_vector);
	heap->heap_vector = NULL;
	
	free(heap);
	heap = NULL;
}

/************* HeapPush *******************************************************/

int HeapPush(heap_ty *heap, void *data)
{
	int push_status = ILRD_SUCCESS;
	
	assert(heap);
	
	push_status = VectorPushBack(heap->heap_vector, data);
	
	if(ILRD_SUCCESS != push_status)
	{
		return ILRD_FAILURE;
	}
	
	HeapifyUp(heap, 0);
	
	return push_status;
}

/************* HeapPop ********************************************************/

int HeapPop(heap_ty *heap)
{
	size_t heap_size = 0;
	void *top_element = NULL;
	void *last_element = NULL;
	int pop_back_status = ILRD_SUCCESS;
	
	assert(heap);
	assert(!HeapIsEmpty(heap));
	
	heap_size = HeapSize(heap);
	
	top_element = VectorGetVal(heap->heap_vector, 0);
	last_element = VectorGetVal(heap->heap_vector, heap_size - 1);
	
	SwapVectorVals(heap->heap_vector, top_element, 0, last_element, 
	                                                             heap_size - 1);
	
	pop_back_status = VectorPopBack(heap->heap_vector);
	heap_size = HeapSize(heap);
	
	if(ILRD_SUCCESS != pop_back_status)
	{
		return ILRD_FAILURE;
	}
	
	HeapifyDown(heap, 0);
		
	return ILRD_SUCCESS;
}

/************* HeapPeek *******************************************************/

void *HeapPeek(const heap_ty *heap)
{
	assert(heap);
	assert(!HeapIsEmpty(heap));
	
	return VectorGetVal(heap->heap_vector, 0);
}

/************* HeapSize *******************************************************/

size_t HeapSize(const heap_ty *heap)
{
	assert(heap);
	
	return VectorSize(heap->heap_vector);
}

/************* HeapIsEmpty ****************************************************/

int HeapIsEmpty(const heap_ty *heap)
{
	assert(heap);
	
	return (0 == HeapSize(heap));
}

/************* HeapRemove *****************************************************/

void *HeapRemove(heap_ty *heap, void *param, is_match_func_ty match_func)
{
	size_t heap_size = 0;
	size_t i = 0;
	int pop_back_status = ILRD_SUCCESS;
	void *curr_val = NULL;
	void *last_val = NULL;
	
	assert(heap);
	assert(param);
	assert(match_func);
	
	heap_size = HeapSize(heap);
	last_val = VectorGetVal(heap->heap_vector, heap_size - 1);
	
	for(i = 0; i < heap_size; ++i)
	{
		curr_val = VectorGetVal(heap->heap_vector, i);
		
		if(match_func(curr_val, param))
		{
			SwapVectorVals(heap->heap_vector, curr_val, i, last_val, 
			                                                     heap_size - 1);
			break;
		}
	}
	
	if(heap_size == i)
	{
		return NULL;
	}
	
	pop_back_status = VectorPopBack(heap->heap_vector);
	
	if(ILRD_SUCCESS != pop_back_status)
	{
		return NULL;
	}
	
	HeapifyDown(heap, 0);
	
	return curr_val;
}

/************* Helper functions ***********************************************/

static void HeapifyDown(heap_ty *heap, size_t start_ind)
{
	size_t parent_ind = start_ind;
	size_t max_possible_ind = 0;
	size_t heap_size = 0;
	void *parent = NULL;
	void *left_child = NULL;
	void *right_child = NULL;
	
	assert(heap);
	
	heap_size = HeapSize(heap);
	
	if(0 == heap_size)
	{
		return;
	}
	
	/* The max_possible_ind is at one level before the lowest level */
	max_possible_ind = (heap_size - 1) / 2;
	
	while(parent_ind < max_possible_ind)
	{
		parent = VectorGetVal(heap->heap_vector, parent_ind);
		left_child = VectorGetVal(heap->heap_vector, (parent_ind * 2) + 1);
		right_child = VectorGetVal(heap->heap_vector, (parent_ind * 2) + 2);
		
		/* If right_child > left_child and right_child > parent */
		if((heap->cmp_func(left_child, right_child) <= 0) && 
		                              (heap->cmp_func(parent, right_child) < 0))
		{
			/* Swap between parent and right_child, and update the parent to be 
			   right_child */
			SwapVectorVals(heap->heap_vector, parent, parent_ind, right_child, 
			                                              (parent_ind * 2) + 2);
			parent_ind = (parent_ind * 2) + 2;
		}
		
		/* If left_child > right_child and left_child > parent */
		if((heap->cmp_func(left_child, right_child) > 0) && 
		                               (heap->cmp_func(parent, left_child) < 0))
		{
			/* Swap between parent and left_child, and update the parent to be 
			   left_child */
			SwapVectorVals(heap->heap_vector, parent, parent_ind, left_child, 
			                                              (parent_ind * 2) + 1);
			parent_ind = (parent_ind * 2) + 1;
		}
		
		else
		{
			/* Update the parent to be left_child */
			parent_ind = (parent_ind * 2) + 1;
		}
	}
	
	/* Edge case: we've reached the max_possible_ind */
	if(parent_ind == max_possible_ind)
	{
		/* If the parent has 2 children */
		if(((parent_ind * 2) + 2) == (heap_size - 1))
		{
			parent = VectorGetVal(heap->heap_vector, parent_ind);
			left_child = VectorGetVal(heap->heap_vector, (parent_ind * 2) + 1);
			right_child = VectorGetVal(heap->heap_vector, (parent_ind * 2) + 2);
			
			if((heap->cmp_func(left_child, right_child) <= 0) && 
			                          (heap->cmp_func(parent, right_child) < 0))
			{
				SwapVectorVals(heap->heap_vector, parent, parent_ind, right_child, 
				                                          (parent_ind * 2) + 2);
				parent_ind = (parent_ind * 2) + 2;
			}
		
			if((heap->cmp_func(left_child, right_child) > 0) && 
			                           (heap->cmp_func(parent, left_child) < 0))
			{
				SwapVectorVals(heap->heap_vector, parent, parent_ind, left_child, 
				                                          (parent_ind * 2) + 1);
				parent_ind = (parent_ind * 2) + 1;
			}
		}
		
		/* If the parent has only left_child */
		else if(((parent_ind * 2) + 1) == (heap_size - 1))
		{
			parent = VectorGetVal(heap->heap_vector, parent_ind);
			left_child = VectorGetVal(heap->heap_vector, (parent_ind * 2) + 1);
			
			if(heap->cmp_func(parent, left_child) < 0)
			{
				SwapVectorVals(heap->heap_vector, parent, parent_ind, left_child, 
				                                          (parent_ind * 2) + 1);
			}
		}
	}
}

static void HeapifyUp(heap_ty *heap, size_t limit_ind)
{
	size_t val_ind = 0;
	void *val = NULL;
	void *parent = NULL;
	
	assert(heap);
	
	val_ind = HeapSize(heap) - 1;
	
	while(limit_ind < val_ind)
	{
		val = VectorGetVal(heap->heap_vector, val_ind);
		parent = VectorGetVal(heap->heap_vector, (val_ind - 1) / 2);
	
		if(heap->cmp_func(parent, val) < 0)
		{
			SwapVectorVals(heap->heap_vector, val, val_ind, parent, (val_ind - 1) / 2);
		}
	
		val_ind = (val_ind - 1) / 2;
	}
}

static void SwapVectorVals(vector_ty *vector, void *elem1, size_t ind1, 
                                                       void *elem2, size_t ind2)
{
	assert(vector);
	assert(elem1);
	assert(elem2);
	
	VectorSetVal(vector, ind1, elem2);
	VectorSetVal(vector, ind2, elem1);
}

/************* HeapSort - Pseudo Code *****************************************/

static void HeapSort(heap_ty *heap)
{
	void *last_element = NULL;
	void *curr_first_element = NULL;
	size_t i = 0;
	size_t heap_size = 0;
	
	assert(heap);
	
	heap_size = HeapSize(heap);
	
	HeapifyDown(heap, 0);
	
	for(i = 0; i < heap_size - 1; ++i)
	{
		last_element = VectorGetVal(heap->heap_vector, heap_size - 1);
		curr_first_element = VectorGetVal(heap->heap_vector, i);
		
		SwapVectorVals(heap->heap_vector, curr_first_element, i, last_element, 
		                                                         heap_size - 1);
		
		HeapifyUp(heap, i);
	}
}




