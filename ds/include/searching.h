/*********************************************************************
* Description: API for Searching Algorithm
* Name: HRD20
* Date: 19/10/2021
* Versions: 1.0 - 
*********************************************************************/
#ifndef __SEARCHING_H_
#define __SEARCHING_H_

#include <stddef.h> /* size_t  */

/*******************************************************************************
* Function Description: Find int in array of ints
			       
* Arguments: sorted_arr: array of ints sorted.
             array size: the size of the sorted array 
             num_to_find: the number that searched in the array. 
             

* Return value: In case the number was found the function return its index, 
                if didn't found - return -1. 
   
* Notes: if array is not sorted or unvalid, Undefined behavior.  
        
* Time Complexity: O(log(n))
*******************************************************************************/
int IterativeBinarySearch(int *sorted_arr, size_t arr_size, int num_to_find);

/*******************************************************************************
* Function Description: Find int in array of ints
			       
* Arguments: sorted_arr: array of ints sorted.
             array size: the size of the sorted array 
             num_to_find: the number that searched in the array. 
             

* Return value: In case the number was found the function return its index, 
                if didn't found - return -1. 
   
* Notes: if array is not sorted or unvalid, Undefined behavior.  
        
* Time Complexity: O(log(n))
*******************************************************************************/
int RecursiveBinarySearch(int *sorted_arr, size_t arr_size, int num_to_find);

#endif /* __SEARCHING_H__ */
