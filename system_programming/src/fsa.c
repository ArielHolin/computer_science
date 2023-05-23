/*******************************************************************************
*  fixed_size_allocator.c                                                      *
*  Author: Ariel                                                               *
*  Reviewer: Eli                                                               *
*******************************************************************************/
#include <stddef.h> /* size_t */
#include <assert.h> /* assert */

#include "fsa.h"

struct fixed_size_allocator
{
    size_t head;
};

#define FSA_SIZE sizeof(fsa_ty)

/***** PoolInit ***************************************************************/

fsa_ty *FSAInit(void *memory_fsa, size_t fsa_size, size_t block_size)
{
	size_t base_add = 0;
	size_t end_add = 0;
	size_t curr_add = 0;
	size_t block_size_mod = 0;
	
	assert(memory_fsa);
	
	base_add = (size_t)memory_fsa;
	end_add = base_add + fsa_size;
	
	((fsa_ty *)memory_fsa)->head = base_add + FSA_SIZE;
	curr_add = ((fsa_ty *)memory_fsa)->head;
	
	/* Aligning blocks to FSA_SIZE */
	block_size_mod = block_size % FSA_SIZE;
	
	if( 0 != block_size_mod )
	{
		block_size = block_size + (FSA_SIZE - block_size_mod);
	}
	
	/* Initializing memory_pool */
	while( curr_add < end_add )
	{
		*(size_t *)curr_add = curr_add + block_size;
		curr_add = curr_add + block_size;
	}
	
	curr_add = curr_add - block_size;
	*(size_t *)curr_add = 0;
	
	return (fsa_ty *)base_add ;
} 

/***** FSAAlloc ***************************************************************/

void *FSAAlloc(fsa_ty *fsa)
{
	void *block_to_alloc = NULL;
	
	assert(fsa);
	
	if( 0 == fsa->head )
	{
		return NULL;
	}
	
	block_to_alloc = (void *)(fsa->head);
	fsa->head = *(size_t *)block_to_alloc;
	
	return block_to_alloc;
}

/***** FSAFree ****************************************************************/

void FSAFree(fsa_ty *fsa, void *address_to_free)
{
	size_t curr_head = 0;
	
	assert(fsa);
	assert(address_to_free);
	
	curr_head = fsa->head;
	fsa->head = (size_t)address_to_free;
	
	*(size_t *)fsa->head = curr_head;	
}

/***** FSAFreeBLocks **********************************************************/

size_t FSAFreeBlocks(const fsa_ty *fsa)
{
	size_t current_block = 0;
	size_t counter = 0;
	
	assert(fsa);
	
	current_block = fsa->head;
	
	while( 0 != current_block )
	{
		++counter;
		current_block = *(size_t *)current_block;
	}
	
	return counter;
}

/***** FSASuggestedSize *******************************************************/

size_t FSASuggestedSize(size_t block_size, size_t num_of_blocks)
{
	size_t aligned_block_size = 0;
	size_t blocks_to_align = FSA_SIZE - ( block_size % FSA_SIZE );
	
	if( FSA_SIZE == blocks_to_align )
	{
		aligned_block_size = block_size;
	}
	
	else
	{
		aligned_block_size = block_size + blocks_to_align;
	}
	
	return ((aligned_block_size * num_of_blocks) + FSA_SIZE);	
}



