/******************************************************************************
* Description: API for fixed_size_allocator
* Name: HRD20
* Date: 01/09/21
* Versions: 1.0 ready for review
*           1.1 ready for review
*
*******************************************************************************/
#ifndef __FIXED_SIZE_ALLOCATOR_H__
#define __FIXED_SIZE_ALLOCATOR_H__

#include <stddef.h> /* size_t */

typedef struct fixed_size_allocator fsa_ty;

/******************************************************************************
* Function Description: Initialize the memory provided by the user
			       
* Arguments: memory_fsa - the memory fsa to be allocated
		   	 fsa_size - total number of bytes to be allocated
			 block_size - number of bytes in a single block

* Return value: pointer to the initialized memory fsa
   
* Notes: before initializing the fsa, user must check suggested fsa size.
		 undefined behaviour if fsa_size does not accommodate memory 
		 requirements. FSAInit assumes recieving aligned address.

* Time Complexity: O(n) - n is number of blocks
*******************************************************************************/
fsa_ty *FSAInit(void *memory_fsa, size_t fsa_size, size_t block_size);

/*******************************************************************************
* Function Description: allocate block of memory
			       
* Arguments: fsa - pointer to the memory fsa

* Return value: the desired allocated memory block
   
* Notes: undefined behavior if NULL is recieved
		 if memory exhausted, return NULL.

* Time Complexity: O(1) 
*******************************************************************************/
void *FSAAlloc(fsa_ty *fsa);

/*******************************************************************************
* Function Description: free allocated block
			       
* Arguments: fsa:  pointer to the memory fsa
             address_to_free: pointer to the block to free

* Return value: no return value
   
* Notes: undefined behavior if NULL is recieved in either argument

* Time Complexity: O(1)
*******************************************************************************/
void FSAFree(fsa_ty *fsa, void *address_to_free);

/*******************************************************************************
* Function Description: counts the number of free blocks
			       
* Arguments: fsa: pointer to  the memory fsa

* Return value: number of free blocks
   
* Notes: undefined behavior if NULL is recieved. legal for allocated memonly.

* Time Complexity: O(n) - n is number of blocks
*******************************************************************************/
size_t FSAFreeBlocks(const fsa_ty *fsa);

/*******************************************************************************
* Function Description: calculates suggested size for initialization of memory 
						fsa
			       
* Arguments: block_size: size of block in bytes
             num_of_blocks: number of required blocks in the fsa

* Return value: total number of bytes to be allocated
   
* Notes:
         
* Time Complexity: O(1)
*******************************************************************************/
size_t FSASuggestedSize(size_t block_size, size_t num_of_blocks);

#endif /* __FIXED_SIZE_ALLOCATOR_H__ */
