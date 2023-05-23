/******************************************************************************
* Description: API for Sorting Algorithms
* Name: HRD20
* Date: 29/11/21
* Version: 1.0 ready for review   
*******************************************************************************/
#ifndef  __MT_SORTING_H__
#define  __MT_SORTING_H__  

#include <stddef.h> /* size_t */

/*******************************************************************************
* Function Description: sorting an array of integers, in ascending order. 
			       
* Arguments: unsorted_arr: array of ints to sort. 
             arr_size: size of array 
             thread_num - amount of thread for the function to use. 

* Return value: None 
   
* Notes: In case of failure of memory allocation - the function won't sort the 
         array 

* Stablity: Stable

* Space complexity:  O(n + k) additional space n = num of elements, k = range of 
                     distinct elements
                     
* Time Complexity:	O(n)  n = number of elements
*******************************************************************************/
int MTCountingSort(char *unsorted_arr, size_t arr_size, size_t thread_num); 

#endif /* __MT_SORTING_H__ */