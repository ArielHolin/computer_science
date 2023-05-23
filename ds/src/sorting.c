/*******************************************************************************
*  sorting.c                                                                   *
*  Author: Ariel                                                               *
*  Reviewer: Eva                                                               *
*******************************************************************************/
#include <stddef.h> /* size_t         */
#include <assert.h> /* assert         */
#include <stdlib.h> /* malloc, free   */
#include <stdio.h>  /* printf         */
#include <string.h> /* memcpy, memset */
#include <limits.h> /* CHAR_BIT       */

#include "sorting.h"

enum status
{
	ILRD_FAILURE = -1,
	ILRD_SUCCESS = 0
};

static void Swap(int *num1, int *num2);
/* Helper functions - SelectionSort */
static int *FindMinVal(int *arr, size_t array_len);
/* Helper functions - CountingSort */
static int FindMaxVal(int *arr, size_t array_len);
static void ArraySort(int *unsorted_array, int *array_to_sort, size_t *hist, 
                      size_t array_len);
/* Helper functions - RadixSort */
static void HelperCountingSort(unsigned int *unsorted_arr, 
                               unsigned int *buffer_output, size_t arr_size, 
                               unsigned int *hist_arr, size_t hist_arr_size, 
                               unsigned int round, unsigned int num_of_bits, 
                               unsigned int min_hist_val);
static unsigned int RadInitMask(unsigned int num_of_bits, unsigned int round);
static void RadArraySort(unsigned int *unsorted_arr, unsigned int *array_to_sort, 
                         unsigned int *hist, size_t array_len, unsigned int mask, 
                         unsigned int num_of_bits);
static unsigned int ReverseBits(unsigned int num);
/* Helper functions - MergeSort */
static int MergeLeftAndRight(int *left_array, int *right_array, 
                                 int left_num_elements, int right_num_elements);

/* Helper functions - QuickSort */
static void VoidPSwap(void *elem1, void *elem2, size_t elem_size);
static int Partioning(void *base, int high_ind, size_t elem_size, cmp_func_ty cmp_func);

#define INT_EXP 5

/* Creating LUT for reversing bits */
#define R2(n)     n,     n + 2*64,     n + 1*64,     n + 3*64
#define R4(n) R2(n), R2(n + 2*16), R2(n + 1*16), R2(n + 3*16)
#define R6(n) R4(n), R4(n + 2*4 ), R4(n + 1*4 ), R4(n + 3*4 )

unsigned int lookuptable[256] = { R6(0), R6(2), R6(1), R6(3) };

/* Creating static variable for use inside RadixSort */
static unsigned int num_of_push_right = 0;

/***** BubbleSort *************************************************************/

void BubbleSort(int *unsorted_arr, size_t arr_size)
{
	size_t swap_counter = 1;
	int *start_unsorted_arr = NULL;
	int *end_unsorted_arr = NULL;
	int *last_swapped_ind = NULL;
	
	assert(unsorted_arr);
	
	if(arr_size > 1)
	{
		end_unsorted_arr = unsorted_arr + (arr_size - 1);
	
		while(0 != swap_counter)
		{
			swap_counter = 0;	
			start_unsorted_arr = unsorted_arr;
		
			while(start_unsorted_arr != end_unsorted_arr)
			{	
				if(*start_unsorted_arr > *(start_unsorted_arr + 1))
				{
					Swap(start_unsorted_arr, start_unsorted_arr + 1);
					++swap_counter;
					last_swapped_ind = start_unsorted_arr;
				}
			
				++start_unsorted_arr;
			}
		
			end_unsorted_arr = last_swapped_ind;
		}
	}
}

/***** InsertionSort **********************************************************/

void InsertionSort(int *unsorted_arr, size_t arr_size)
{
	int *element_to_insert = NULL;
	int *end_unsorted_arr = NULL;
	int *runner = NULL;
	
	assert(unsorted_arr);
	
	if(arr_size > 1)
	{
		element_to_insert = unsorted_arr + 1;
		end_unsorted_arr = unsorted_arr + arr_size;
	
		while(element_to_insert != end_unsorted_arr)
		{
			runner = element_to_insert;
		
			while(runner != unsorted_arr)
			{
				if(*runner >= *(runner - 1))
				{
					break;
				}
			
				Swap(runner, runner - 1);
				--runner;
			}
		
			++element_to_insert;
		}
	}
}

/***** SelectionSort **********************************************************/

void SelectionSort(int *unsorted_arr, size_t arr_size)
{
	int *curr_min_val = NULL;
	int *sub_unsorted_arr = NULL;
	int *end_unsorted_arr = NULL;
	size_t i = 0;
	
	assert(unsorted_arr);
	
	if(arr_size > 1)
	{
		sub_unsorted_arr = unsorted_arr;
		end_unsorted_arr = unsorted_arr + (arr_size - 1);
		
		while(sub_unsorted_arr != end_unsorted_arr)
		{
			curr_min_val = FindMinVal(sub_unsorted_arr, arr_size - i);
			
			if(curr_min_val != sub_unsorted_arr)
			{
				Swap(curr_min_val, sub_unsorted_arr);
			}
			
			++sub_unsorted_arr;
			++i;
		}
	}	
}

/***** CountingSort ***********************************************************/

void CountingSort(int *unsorted_arr, size_t arr_size)
{
	size_t *hist = NULL;
	int *sorted_arr = NULL;
	size_t i = 0;
	int max_val = 0;
	int j = 1;
	
	assert(unsorted_arr);
	
	/* Finding max val of unsorted_arr */
	max_val = FindMaxVal(unsorted_arr, arr_size);
	
	/* Creating array for counting valus of unsorted_arr */
	hist = (size_t *)malloc((max_val + 1) * sizeof(size_t));
	
	if(!hist)
	{
		printf("System Error\n");
		return;
	}
	
	/* Initializing counts array with 0's */
	hist = (size_t *)memset(hist, 0, ((size_t)(max_val + 1)) * sizeof(size_t));
	
	/* Counting values appearnces of unsorted array, where each index of counts 
	   represents value of unsorted array */
	for(i = 0; i < arr_size; ++i)
	{
		++hist[unsorted_arr[i]];
	}
	
	/* Performing cummulative sum at each index */
	for(j = 1; j <= max_val; ++j)
	{
		hist[j] += hist[j - 1];
	}
	
	/* Creating new array to store the sorted values */
	sorted_arr = (int *)malloc(arr_size * sizeof(int));
	
	if(!sorted_arr)
	{
		free(hist);
		hist = NULL;
		
		printf("System Error\n");
		return;
	}
	
	/* Sorting unsorted_arr and storing the result in sorted_arr */
	ArraySort(unsorted_arr, sorted_arr, hist, arr_size);
	
	/* Copying sorted_arr into unsorted_arr */
	memcpy(unsorted_arr, sorted_arr, arr_size * sizeof(int));
	
	/* Deallocating memory */
	free(hist);
	hist = NULL;
	
	free(sorted_arr);
	sorted_arr = NULL;
}

/***** Helper Function - Swap *************************************************/

static void Swap(int *num1, int *num2)
{
	int tmp = *num1;
	*num1 = *num2;
	*num2 = tmp;
}

/***** Helper Function - FindMinVal *******************************************/

/* Find min val in array, and return the location of the min val.
   Array length should be > 1 */
static int *FindMinVal(int *arr, size_t array_len)
{
	int *min_val_loc = NULL;
	int *end_array = NULL;
	
	assert(arr);
	assert(arr + 1);
	
	min_val_loc = arr;
	end_array = arr + array_len;
	++arr;
	
	while(arr != end_array)
	{
		if(*arr < *min_val_loc)
		{
			min_val_loc = arr;
		}
		
		++arr;
	}
	
	return min_val_loc;
}

/***** Helper Function - FindMaxVal *******************************************/

/* Find max val of array, and return that value. */
static int FindMaxVal(int *arr, size_t array_len)
{
	int *end_array = NULL;
	int max_val = 0;
	
	assert(arr);
	
	end_array = arr + array_len;
	max_val = *arr;
	
	while(arr != end_array)
	{
		if(*arr > max_val)
		{
			max_val = *arr;
		}
		
		++arr;
	}
	
	return max_val;
}

/***** Helper Function - ArraySort ********************************************/

/*
	ArraySort sorting unsorted_array based on counts array, and stores the sorted
	array in array_to_sort.
*/
static void ArraySort(int *unsorted_arr, int *array_to_sort, size_t *hist, 
                      size_t array_len)
{
	int *end_unsorted_arr = NULL;
	
	assert(unsorted_arr);
	assert(array_to_sort);
	assert(hist);
	
	end_unsorted_arr = unsorted_arr + (array_len - 1);
	
	while(end_unsorted_arr != (unsorted_arr - 1))
	{
		--hist[*end_unsorted_arr];
		array_to_sort[hist[*end_unsorted_arr]] = *end_unsorted_arr;
		--end_unsorted_arr;
	}
}

/***** RadixSort **************************************************************/

void RadixSort(unsigned int *unsorted_arr, size_t arr_size, 
                                                   unsigned int exponent_of_two)
{
	unsigned int bits_in_int = 0;
	unsigned int num_of_bits = 0;
	unsigned int round = 0;
	unsigned int hist_arr_size = 0;
	unsigned int *buffer_output = NULL;
	unsigned int *hist_arr = NULL;
	
	assert(unsorted_arr);
	assert(exponent_of_two <= INT_EXP);
	
	bits_in_int = CHAR_BIT * sizeof(unsigned int);
	num_of_bits = 1UL << exponent_of_two;
	round = bits_in_int / num_of_bits;
	hist_arr_size = 1UL << num_of_bits;
	
	buffer_output = (unsigned int *)malloc((arr_size + 1)*sizeof(unsigned int));
	
	if(!buffer_output)
	{
		printf("System error\n");
		return;
	}
	
	hist_arr = (unsigned int *)malloc((hist_arr_size + 1)*sizeof(unsigned int));
	
	if(!hist_arr)
	{
		free(buffer_output);
		buffer_output = NULL;
		
		printf("System error\n");
		return;
	}
	
	if(1 == round)
	{
		CountingSort((int *)unsorted_arr, arr_size);
		return;
	}
	
	HelperCountingSort(unsorted_arr, buffer_output, arr_size, hist_arr, 
		               hist_arr_size, round, num_of_bits, 0);
	
	free(buffer_output);
	buffer_output = NULL;
	
	free(hist_arr);
	hist_arr = NULL;
}

/* Helper function CountingSort to be used by RadixSort */
static void HelperCountingSort(unsigned int *unsorted_arr, 
                               unsigned int *buffer_output, size_t arr_size, 
                               unsigned int *hist_arr, size_t hist_arr_size, 
                               unsigned int round, unsigned int num_of_bits, 
                               unsigned int min_hist_val)
{
	size_t i = 0;
	size_t j = 1;
	unsigned int mask = 0;
	
	assert(unsorted_arr);
	assert(buffer_output);
	assert(hist_arr);
	
	/* Start condition for the recursion */
	if(0 == round)
	{
		return;
	}
	
	/* Create mask appropriate to the current round */
	mask = RadInitMask(num_of_bits, round);
	mask = ReverseBits(mask);
	
	/* Initializing hist_arr with 0's */
	hist_arr = (unsigned int *)memset(hist_arr, 0, hist_arr_size * 
	                                                      sizeof(unsigned int));
	
	/* Creating histogram, making sure we're not exceeding hist range */
	for(i = 0; i < arr_size; ++i)
	{
		++hist_arr[(unsorted_arr[i] & mask)>>(num_of_push_right*num_of_bits)];
	}
	
	/* Performing cummulative sum at each index */
	for(j = 1; j < hist_arr_size; ++j)
	{
		hist_arr[j] += hist_arr[j - 1];
	}
	
	/* Sorting unsorted_arr */
	RadArraySort(unsorted_arr, buffer_output, hist_arr, arr_size, mask, num_of_bits);
	
	/* Updating round */
	--round;
	/* Updating num_of_push_right to be used next round */
	++num_of_push_right;
	
	/* Call HelperCountingSort recursively, substituting roles of buffer_output
	   and unsorted_array */
	HelperCountingSort(buffer_output, unsorted_arr, arr_size, hist_arr, 
	                   hist_arr_size, round, num_of_bits, min_hist_val);
}

/* Helper function for initializing mask.
   mask is a 32-bit bitmap that holds 1's for every bit at the appropriate round, 
   and 0's elsewhere.
   example: num_of_bits = 16, round 1:
            0000000000000000 1111111111111111  
            
            num_of_bits = 16, round 2:
            1111111111111111 0000000000000000*/
static unsigned int RadInitMask(unsigned int num_of_bits, unsigned int round)
{
	unsigned int mask = (1UL << num_of_bits) - 1;
	
	return (mask << ((round - 1)*num_of_bits));
}

/* Helper function to sort unsorted_arr and store the sorted array in 
   array_to_sort.
   The function also receives the histogram, num_of_bits used in the algorithm,
   and mask of the appropriate round */
static void RadArraySort(unsigned int *unsorted_arr, unsigned int *array_to_sort, 
                         unsigned int *hist, size_t array_len, unsigned int mask, 
                         unsigned int num_of_bits)
{
	unsigned int *end_unsorted_arr = NULL;
	
	assert(unsorted_arr);
	assert(array_to_sort);
	assert(hist);
	
	end_unsorted_arr = unsorted_arr + (array_len - 1);
	
	while(end_unsorted_arr != (unsorted_arr - 1))
	{
		--hist[((*end_unsorted_arr) & mask)>>(num_of_push_right * num_of_bits)];
		array_to_sort[hist[((*end_unsorted_arr) & mask)>>
		                (num_of_push_right * num_of_bits)]] = *end_unsorted_arr;
		--end_unsorted_arr;
	}
}

/* Helper function to reverse the order of bits in a 32-bit bitmap */
static unsigned int ReverseBits(unsigned int num)
{
	unsigned int reverse_num = 0;
  
     /* Reverse and then rearrange */ 
  
                   /* first chunk of 8 bits from right */
     reverse_num = lookuptable[ num & 0xff ]<<24 | 
  
                   /* second chunk of 8 bits from  right */
                   lookuptable[ (num >> 8) & 0xff ]<<16 | 
  
                   lookuptable[ (num >> 16 )& 0xff ]<< 8 |
                   lookuptable[ (num >>24 ) & 0xff ] ;
    
    return reverse_num;
}

/***** MergeSort **************************************************************/

int MergeSort(int *arr_to_sort, size_t num_elements)
{
	int *left_array = NULL;
	int *right_array = NULL;
	int left_num_elements = (int)(num_elements / 2) + (int)(num_elements % 2);
	int right_num_elements = (int)(num_elements / 2);
	
	assert(arr_to_sort);

	left_array = arr_to_sort;
	right_array = arr_to_sort + left_num_elements;
	
	if(1 == num_elements)
	{
		return ILRD_SUCCESS;
	}
	
	if(ILRD_SUCCESS != MergeSort(left_array, left_num_elements))
	{
		return ILRD_FAILURE;
	}
	
	if(ILRD_SUCCESS != MergeSort(right_array, right_num_elements))
	{
		return ILRD_FAILURE;
	}
	
	return MergeLeftAndRight(left_array, right_array, left_num_elements, 
	                                                        right_num_elements);
}

/* Helper function - Merging left and right arrays */
static int MergeLeftAndRight(int *left_array, int *right_array, 
                                  int left_num_elements, int right_num_elements)
{
	int *sorted_array = NULL;
	int total_num_elements = 0;
	int left_ind = 0;
	int right_ind = 0;
	int sorted_ind = 0;
	
	assert(left_array);
	assert(right_array);
	
	total_num_elements = left_num_elements + right_num_elements;
	
	sorted_array = (int *)malloc(sizeof(int) * total_num_elements);
	
	if(!sorted_array)
	{
		return ILRD_FAILURE;
	}
	
	while((left_ind < left_num_elements) && (right_ind < right_num_elements))
	{
		if(left_array[left_ind] <= right_array[right_ind])
		{
			sorted_array[sorted_ind] = left_array[left_ind];
			++left_ind;
		}
		
		else
		{
			sorted_array[sorted_ind] = right_array[right_ind];
			++right_ind;
		}
		
		++sorted_ind;
	}
	
	while(right_ind < right_num_elements)
	{
		sorted_array[sorted_ind] = right_array[right_ind];
		++sorted_ind;
		++right_ind;
	}
	
	while(left_ind < left_num_elements)
	{
		sorted_array[sorted_ind] = left_array[left_ind];
		++sorted_ind;
		++left_ind;
	}
	
	memcpy(left_array, sorted_array, sizeof(int) * total_num_elements);
	
	free(sorted_array);
	sorted_array = NULL;
	
	return ILRD_SUCCESS;	
}

/***** QuickSort **************************************************************/

void QuickSort(void *base, size_t num_of_elem, size_t elem_size, 
                                                           cmp_func_ty cmp_func)
{
	int pivot_ind = 0;
	
	assert(base);
	
	if(0 == num_of_elem)
	{
		return;
	}
	
	if(num_of_elem > 1)
	{
		pivot_ind = Partioning(base, num_of_elem - 1, elem_size, cmp_func);
		QuickSort(base, pivot_ind, elem_size, cmp_func);
		QuickSort((unsigned char *)base + (pivot_ind + 1)*elem_size, 
		                    num_of_elem - (pivot_ind + 1), elem_size, cmp_func);
	}
}

static void VoidPSwap(void *elem1, void *elem2, size_t elem_size)
{
	unsigned char *char_p1 = NULL;
	unsigned char *char_p2 = NULL;
	unsigned char tmp = '\0';
	size_t i = 0;
	
	assert(elem1);
	assert(elem2);
	
	char_p1 = (unsigned char *)elem1;
	char_p2 = (unsigned char *)elem2;
	
	for(i = 0; i < elem_size; ++i)
	{
		tmp = char_p1[i];
		char_p1[i] = char_p2[i];
		char_p2[i] = tmp;
	}
}

static int Partioning(void *base, int high_ind, size_t elem_size, 
                                                           cmp_func_ty cmp_func)
{
	void *pivot = NULL;
	void *runner = NULL;
	int i = 0;
	int pivot_ind = - 1;
	
	assert(base);
	
	runner = base;
	pivot = (unsigned char *)base + (elem_size * high_ind);
	
	for(i = 0; i < high_ind; ++i)
	{
		if(cmp_func(runner, pivot) < 0)
		{
			++pivot_ind;
			VoidPSwap((unsigned char *)base + (pivot_ind*elem_size), 
			                  (unsigned char *)base + (i*elem_size), elem_size);
		}
		
		runner = (unsigned char *)base + ((i+1) * elem_size);
	}
	
	++pivot_ind;
	VoidPSwap(pivot, (unsigned char *)base + (pivot_ind * elem_size), elem_size);
	
	return pivot_ind;
}




