/*********************************************************************
* Description: Implementation of Circular Buffer data structure
* Name: HRD20
* Date: 17.8.2021
* Versions:
1.0 - ready for review
1.1 - after Rina's approval
1.2 - updating ssize_t header file
*********************************************************************/
#ifndef __CIRCULAR_BUFFER_H__
#define __CIRCULAR_BUFFER_H__

#include <stddef.h>    /* size_t  */
#include <sys/types.h> /* ssize_t */

typedef struct cbuf cbuf_ty;
 
/*******************************************************************************
* Function Description: Create a new circular buffer with fixed capacity size.
			       
* Arguments: capacity - Max number of bytes that circular buffer can store.

* Return value: Reference to circular buffer.
   
* Notes: After usage of circular buffer, one should always destroy it (using 
         CircBuffDestroy).
        
* Time Complexity: O(1)
*******************************************************************************/
cbuf_ty *CircBuffCreate(size_t capacity);

/*******************************************************************************
* Function Description: Deallocates memory used for the circular buffer
			       
* Arguments: cbuf - reference to the circular buffer that needs to be destroyed.

* Return value:  
   
* Notes: In case cbuf = NULL, behavior is undefined.
        
* Time Complexity: O(1)	
*******************************************************************************/
void CircBuffDestroy(cbuf_ty *cbuf);

/*******************************************************************************
* Function Description: Determines how many free bytes there are in the circular 
                        buffer.
			       
* Arguments: cbuf - reference to the circular buffer.

* Return value: Number of unoccupied bytes in the circular buffer.  
   
* Notes: In case cbuf = NULL, behavior is undefined.
        
* Time Complexity: O(1)	
*******************************************************************************/
size_t CircBuffFreeSpace(const cbuf_ty *cbuf);

/*******************************************************************************
* Function Description: Determines how many occupied bytes there are in circular
                        buffer.
			       
* Arguments: cbuf - reference to the circular buffer.

* Return value: Number of occupied bytes in the circular buffer.
   
* Notes: In case cbuf = NULL, behavior is undefined.
        
* Time Complexity: O(1)
*******************************************************************************/
size_t CircBuffBufsiz(const cbuf_ty *cbuf);

/*******************************************************************************
* Function Description: Deteremines if the circular buffer is empty or not.
			       
* Arguments: cbuf - reference to the circular buffer.

* Return value: If empty return 1, else return 0. 
   
* Notes: In case cbuf = NULL, behavior is undefined.
        
* Time Complexity: O(1)	
*******************************************************************************/
int CircBuffIsEmpty(const cbuf_ty *cbuf);

/*******************************************************************************
* Function Description: Read up to num_bytes from cbuf into dest.
			       
* Arguments: cbuf - reference to the circular buffer to read from.
             dest - reference to the segment to read into.
             num_bytes -Number of bytes to read.

* Return value: On success, the number of bytes successfuly read is returned.
                If circular buffer is empty, return -1. 
   
* Notes: In case cbuf = NULL, behavior is undefined.
         Returned value might be less than num_bytes.
        
* Time Complexity:	O(n). n = count. 
*******************************************************************************/
ssize_t CircBuffRead(cbuf_ty *cbuf, void *dest, size_t num_bytes);

/*******************************************************************************
* Function Description: Writes up to count bytes from src into cbuf.
			       
* Arguments: cbuf - reference to the circular buffer to write to.
             src - reference to the element to write from. 
             num_bytes - Max number of bytes.

* Return value: On success, the number of bytes successfuly written is returned.
                If circular buffer is full, return -1. 
   
* Notes: In case cbuf = NULL, behavior is undefined.
         In case num_bytes > capacity, behavior is undefined.
        
* Time Complexity: O(n). n = count.	
*******************************************************************************/
ssize_t CircBuffWrite(cbuf_ty *cbuf, const void *src, size_t num_bytes);

#endif /* __CIRCULAR_BUFFER_H__ */
