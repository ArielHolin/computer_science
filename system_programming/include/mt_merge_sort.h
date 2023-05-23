/******************************************************************************
* Description: API for Multi Threaded Sorting Algorithms
* Name: HRD20
* Date: 30/11/21
* Version: 1.0 ready for review   
*******************************************************************************/
#ifndef  __MT_MERGE_SORT_H__
#define  __MT_MERGE_SORT_H__  

#include <stddef.h> /* size_t */
/*******************************************************************************
* Function Description: Sorting a an array of words. 
			       
* Arguments: arr_to_sort: array of strings to word. 
             arr_size: size of array 

* Return value: status - 0 for success 1 for failure
   
* Notes: In case of failure of memory allocation - the function won't sort the 
         array 

* Stablity: Stable

* Space complexity:  O(n) n = number of elements

* Time Complexity:	O(n * log(n))  n = number of elements
*******************************************************************************/
int MTMergeSort(char **arr_to_sort, size_t arr_size);

#endif /* __MT_MERGE_SORT_H__ */