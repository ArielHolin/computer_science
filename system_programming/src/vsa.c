/*******************************************************************************
*  vsa.c                                                                       *
*  Author: Ariel                                                               *
*  Reviewer: Doron                                                             *
*******************************************************************************/
#include <assert.h> /* assert */
#include <stddef.h> /* size_t */

#include "vsa.h"

#ifndef NDEBUG
#define DEBUG_ONLY(exp) exp
#else
#define DEBUG_ONLY(exp) 
#endif

#define ALLOC_ID 0xDEADBEEF

struct variable_size_allocator
{
    long block_size;
    DEBUG_ONLY(long alloc_id;)
};

#define VSA_TY_SIZE sizeof(vsa_ty)
#define WORD_SIZE sizeof(long)

static long AlignBlockSize(size_t block_size);
static void VSADefregment(vsa_ty *vsa);

/***** VSAInit ****************************************************************/

vsa_ty *VSAInit(void *memory_vsa, size_t vsa_size)
{
	long base = 0;
	long head = 0;
	long end = 0;
	
	assert(memory_vsa);
	
	/* Recomputing vsa_size for block alignment according to WORD_SIZE */
	vsa_size = (vsa_size / WORD_SIZE) * WORD_SIZE;
	
	base = (long)memory_vsa;
	head = base;
	end = base + vsa_size - VSA_TY_SIZE;
	
	*(long *)head = vsa_size - (2 * VSA_TY_SIZE);
	DEBUG_ONLY(head += WORD_SIZE;)
	DEBUG_ONLY(*(long *)head = ALLOC_ID;)
	
	*(long *)end = 0;
	DEBUG_ONLY(end += WORD_SIZE;)
	DEBUG_ONLY(*(long *)end = ALLOC_ID;)
	
	return (vsa_ty *)base;	
}

/***** VSAAlloc ***************************************************************/

void *VSAAlloc(vsa_ty *vsa, size_t block_size)
{
	long curr_block_size = 0;
	long occupied_block_size = 0;
	long curr_vsa = 0;
	long runner = 0;
	long aligned_block_size = 0;
	void *ret_block = NULL;
	
	assert(vsa);
	
	aligned_block_size = AlignBlockSize(block_size);
	
	curr_vsa = (long)vsa;
	curr_block_size = *(long *)curr_vsa;
	
	while( 0 != curr_block_size )
	{
		if( aligned_block_size + (long)VSA_TY_SIZE < curr_block_size )
		{
			occupied_block_size = -aligned_block_size;
			
			*(long *)curr_vsa = occupied_block_size;
			curr_vsa += VSA_TY_SIZE;
			DEBUG_ONLY(curr_vsa -= WORD_SIZE;)
			DEBUG_ONLY(*(long *)curr_vsa = ALLOC_ID;)
			DEBUG_ONLY(curr_vsa += WORD_SIZE;)
			
			ret_block = (void *)curr_vsa;
			
			curr_vsa += aligned_block_size;
			*(long *)curr_vsa = curr_block_size + occupied_block_size - VSA_TY_SIZE;
			
			return ret_block;
		}
		
		if( (aligned_block_size <= curr_block_size) && 
		    (aligned_block_size + (long)VSA_TY_SIZE >= curr_block_size) )
		{
			*(long *)curr_vsa = -curr_block_size;
			curr_vsa += VSA_TY_SIZE;
			DEBUG_ONLY(curr_vsa -= WORD_SIZE;)
			DEBUG_ONLY(*(long *)curr_vsa = ALLOC_ID;)
			DEBUG_ONLY(curr_vsa += WORD_SIZE;)
			
			return (void *)curr_vsa;
		}
		
		if( (aligned_block_size > curr_block_size) && (curr_block_size > 0) )
		{
			runner = curr_vsa;
			
			/* Defregmentation */
			while(*(long *)runner != 0)
			{
				while((*(long *)runner > 0) && (aligned_block_size > curr_block_size))
				{
					if( runner != curr_vsa )
					{
						curr_block_size += *(long *)runner + VSA_TY_SIZE;
					}
				
					runner = runner + VSA_TY_SIZE + *(long *)runner;
				}
			
				if( aligned_block_size + (long)VSA_TY_SIZE < curr_block_size )
				{
					*(long *)curr_vsa = -aligned_block_size;
					curr_vsa += VSA_TY_SIZE;
					DEBUG_ONLY(curr_vsa -= WORD_SIZE;)
					DEBUG_ONLY(*(long *)curr_vsa = ALLOC_ID;)
					DEBUG_ONLY(curr_vsa += WORD_SIZE;)
			
					ret_block = (void *)curr_vsa;
			
					curr_vsa += aligned_block_size;
					*(long *)curr_vsa = curr_block_size - aligned_block_size - VSA_TY_SIZE;
			
					return ret_block;
				}
			
				if( (aligned_block_size <= curr_block_size) && 
		    		(aligned_block_size + (long)VSA_TY_SIZE >= curr_block_size) )
				{
					*(long *)curr_vsa = -curr_block_size;
					curr_vsa += VSA_TY_SIZE;
					DEBUG_ONLY(curr_vsa -= WORD_SIZE;)
					DEBUG_ONLY(*(long *)curr_vsa = ALLOC_ID;)
					DEBUG_ONLY(curr_vsa += WORD_SIZE;)
			
					return (void *)curr_vsa;
				}
				
				/* If the block is occupied, then *(long *)runner < 0 */
				if( 0 != *(long *)runner )
				{
					runner = runner + VSA_TY_SIZE - *(long *)runner;
					curr_vsa = runner;
				}
			}
		}
		
		if(curr_block_size < 0)
		{
			curr_block_size = -curr_block_size;
		}
		
		curr_vsa = curr_vsa + VSA_TY_SIZE + curr_block_size;
		curr_block_size = *(long *)curr_vsa;
	}
	
	return ret_block;
}

/***** VSAFree ****************************************************************/

void VSAFree(void *address_to_free)
{
	long header_of_address = 0;
	
	assert(address_to_free);
	
	header_of_address = (long)address_to_free - VSA_TY_SIZE;
	
	DEBUG_ONLY(header_of_address += WORD_SIZE;)
	assert(*(long *)header_of_address == ALLOC_ID);
	DEBUG_ONLY(header_of_address -= WORD_SIZE;)
	*(long *)header_of_address = -(*(long *)header_of_address);
}

/***** VSALargestFreeBlock ****************************************************/

size_t VSALargestFreeBlock(vsa_ty *vsa)
{
	long runner = 0;
	long curr_free_block = 0;
	long max_free_block = 0;
	
	assert(vsa);
	
	VSADefregment(vsa);
	
	runner = (long)vsa;
	
	while( 0 != *(long *)runner )
	{
		curr_free_block = *(long *)runner;
		
		if( curr_free_block > max_free_block )
		{
			max_free_block = curr_free_block;
		}
		
		if( curr_free_block > 0 )
		{
			runner = runner + VSA_TY_SIZE + curr_free_block;
		}
		
		else
		{
			runner = runner + VSA_TY_SIZE - curr_free_block;
		}
	}
	
	return max_free_block;
}

/***** Helper Function - VSADefregmentate *************************************/

static void VSADefregment(vsa_ty *vsa)
{
	long curr_free_block = 0;
	long start_header = 0;
	long runner = 0;
	
	assert(vsa);
	
	start_header = (long)vsa;
	runner = (long)vsa;
	
	while( 0 != *(long *)runner )
	{
		while( *(long *)runner > 0 )
		{	
			curr_free_block += *(long *)runner;
			
			if(runner != start_header) 
			{
				curr_free_block += VSA_TY_SIZE;
			}
			
			runner = runner + VSA_TY_SIZE + *(long *)runner;
		}
		
		if( curr_free_block > 0 )
		{
			*(long *)start_header = curr_free_block;
			curr_free_block = 0;
		}
		
		/* If the block is occupied, then *(long *)runner < 0 */
		if( 0 != *(long *)runner )
		{
			runner = runner + VSA_TY_SIZE - *(long *)runner;
			start_header = runner;
		}
	}
}

/***** Helper Function - AlignBlockSize ***************************************/

static long AlignBlockSize(size_t block_size)
{
	long block_mod_size = ((long)block_size) % WORD_SIZE;
	
	return block_mod_size ? block_size + (WORD_SIZE - block_mod_size) 
	                                                               : block_size; 
}
