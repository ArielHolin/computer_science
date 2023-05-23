/*******************************************************************************
* Description: API for Sorting Algorithms
* Name: HRD20
* Date: 26/09/21
* Version: 1.0 ready for review   
* Version: 1.1 Approved         
*******************************************************************************/
#ifndef  __SORTING_H__
#define  __SORTING_H__

#include <stddef.h> /* size_t */

typedef int (*cmp_func_ty)(const void *element1, const void *element2);

/*******************************************************************************
* Function Description: sorting an array of integers, in ascending order. 
			       
* Arguments: unsorted_arr: array of ints to sort. 
             arr_size: size of array 

* Return value: None 
   
* Notes: None

* Stablity: Stable

* Space complexity: works in-place O(1). O(n^2) swaps 
        
* Time Complexity:	O(n^2) worst case, O(n) best case n = number of elements
*******************************************************************************/
void BubbleSort(int *unsorted_arr, size_t arr_size);
/*******************************************************************************
* Function Description: sorting an array of integers, in ascending order. 
			       
* Arguments: unsorted_arr: array of ints to sort. 
             arr_size: size of array 

* Return value: None 
   
* Notes: None

* Stablity: Stable

* Space complexity: works in-place O(1). O(n^2) swaps 
        
* Time Complexity:	O(n^2) worst case, O(n) best case n = number of elements
*******************************************************************************/
void InsertionSort(int *unsorted_arr, size_t arr_size);
/*******************************************************************************
* Function Description: sorting an array of integers, in ascending order. 
			       
* Arguments: unsorted_arr: array of ints to sort. 
             arr_size: size of array 

* Return value: None 
   
* Notes: None

* Stablity: Stable

* Space complexity: works in-place O(1). O(n) swaps
       
* Time Complexity:	O(n^2)  n = number of elements
*******************************************************************************/
void SelectionSort(int *unsorted_arr, size_t arr_size);

/*******************************************************************************
* Function Description: sorting an array of integers, in ascending order. 
			       
* Arguments: unsorted_arr: array of ints to sort. 
             arr_size: size of array 

* Return value: None 
   
* Notes: None

* Stablity: Stable

* Space complexity:  O(n + k) additional space n = num of elements, 
                                               k = range of distinct elements
 
* Time Complexity:	O(n)  n = number of elements
*******************************************************************************/
void CountingSort(int *unsorted_arr, size_t arr_size);
/*******************************************************************************
* Function Description: sorting an array of integers, in ascending order. 
			       
* Arguments: unsorted_arr: array of ints to sort. 
             arr_size: size of array 
             exponent_of_two: The index of base two, that will determine number 
                              of bits to compare in each stage. (limited [0, 5])

* Return value: None 
   
* Notes: In case of failure of memory allocation - the function won't sort the array 

* Stablity: Stable

* Space complexity:  O(d*(n+b)) additional space n = num of elements, 
                     d = exponent_of_two, b = 2^exponent_of_two

* Time Complexity:	O(n)  n = number of elements
*******************************************************************************/
void RadixSort(unsigned int *unsorted_arr, size_t arr_size, unsigned int exponent_of_two);

/*******************************************************************************
* Function Description: sorting an array of integers, in ascending order. 
			       
* Arguments: arr_to_sort: array of ints to sort. 
             arr_size: size of array 

* Return value: status - 0 for success 1 for failure
   
* Notes: In case of failure of memory allocation - the function won't sort the array 

* Stablity: Stable

* Space complexity:  O(n) n = number of elements

* Time Complexity:	O(n * log(n))  n = number of elements
*******************************************************************************/
int MergeSort(int *arr_to_sort, size_t num_elements);

/*******************************************************************************
* Function Description: sorting any type of array according to cmp_func given. 
			       
* Arguments: base: pointer to the begining of the unsorted array.  
             arr_size: size of array to sort. 
             elem_size: size of each element in the array. 
             cmp_func: function pointer that responsible for the sorting policy.  

* Return value: 
   
* Notes: if any unvalid parameter is given - undefined behavior.  

* Stablity: UnStable

* Space complexity:  O(1) (in place)

* Time Complexity:	O(n * log(n)) avrage case, O(n) worst case,  n = number of elements
*******************************************************************************/
void QuickSort(void *base, size_t num_of_elem, size_t elem_size, cmp_func_ty cmp_func);

#endif /* __SORTING_H__ */
