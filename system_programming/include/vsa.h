/******************************************************************************
* Description: API for variable_size_allocator
* Name: HRD20
* Date: 09/09/21
* Version: 1.0 ready for review           
* Version: 1.1 after    review           
* Version: 1.2 after changes:
             to Function Descriptions (VSAAlloc and VSALargestFreeBlock)
             to Function arguments (VSAInit)
*
*******************************************************************************/
#ifndef __VARIABLE_SIZE_ALLOCATOR_H__
#define __VARIABLE_SIZE_ALLOCATOR_H__

#include <stddef.h> /* size_t */

typedef struct variable_size_allocator vsa_ty;

/******************************************************************************
* Function Description: Initialize the memory provided by the user
			       
* Arguments: memory_vsa - the memory vsa to be allocated
                        (address is assumed to be alligned)
		   	 vsa_size   - total number of bytes to be allocated			 

* Return value: pointer to the initialized memory vsa
   
* Notes: undefined behavior if memory_vsa is NULL

* Time Complexity: O(1)
*******************************************************************************/
vsa_ty *VSAInit(void *memory_vsa, size_t vsa_size);

/*******************************************************************************
* Function Description: 
    - allocate block of memory
    - defragmentation up to block of memory to be allocated: 
      (unite adjoining free blocks into a single free block)
			       
* Arguments: vsa        - pointer to the memory vsa
             block_size - the size of the requested block in bytes

* Return value: the allocated memory block.
                returns NULL if memory is exhausted.
   
* Notes: - undefined behavior if requested block_size is 0

* Time Complexity: O(n) - n represents number of memory blocks
*******************************************************************************/
void *VSAAlloc(vsa_ty *vsa, size_t block_size); 

/*******************************************************************************
* Function Description: free allocated block
			       
* Arguments: address_to_free: pointer to the block to free           

* Return value: no return value
   
* Notes: undefined behavior:    -  If address_to_free is NULL
                                -  If address_to_free is not valid
(not valid refers to address other than of an allocated memory block)

* Time Complexity: O(1)
*******************************************************************************/
void VSAFree(void *address_to_free);

/*******************************************************************************
* Function Description: 
    - indicates the largest available free contigious chunck of memory
    - defragmentation up to end block: 
      (unite adjoining free blocks into a single free block)
			       
* Arguments: vsa: pointer to the memory vsa

* Return value: size of largest available free block,  in bytes
   
* Notes: undefined behavior if NULL is recieved.

* Time Complexity: O(n) - n represents number of memory blocks
*******************************************************************************/
size_t VSALargestFreeBlock(vsa_ty *vsa);

#endif /* __VARIABLE_SIZE_ALLOCATOR_H__ */
