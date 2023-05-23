/*******************************************************************************
 *   mt_sorting.c                                                              *
 *   Author: Ariel                                                             *
 *   Reviewer:                                                                 *
 * ****************************************************************************/
#include <stddef.h>  /* size_t       */
#include <stdlib.h>  /* malloc, free */
#include <assert.h>  /* assert       */
#include <string.h>  /* memset       */
#include <stdio.h>   /* printf       */
#include <pthread.h> /* pthread_t, pthread_mutex_t */

#include "mt_sorting.h" 

#define ASCII     256
#define SUCCESS   0
#define SYS_FAIL -1

typedef struct inds_range
{
    size_t start_ind;
    size_t end_ind;
    char *array_to_sort;
}inds_range_ty;

size_t hist_global[ASCII];
pthread_mutex_t lock;

void *BuildHist(void *arg);
static void ArraySort(char *unsorted_arr, char *array_to_sort, size_t *hist, 
                      size_t arr_size);

int MTCountingSort(char *unsorted_arr, size_t arr_size, size_t thread_num)
{
    char *sorted_arr = NULL;
    size_t i = 0;
    size_t j = 0;
    size_t remainder = arr_size % thread_num;
    pthread_t ids[thread_num];
    inds_range_ty sub_arrs[thread_num];

    assert(unsorted_arr);

    for(i = 0; i < thread_num - 1; ++i)
    {
        sub_arrs[i].start_ind = i * (arr_size / thread_num);
        sub_arrs[i].end_ind = (i + 1) * (arr_size / thread_num) - 1;
        sub_arrs[i].array_to_sort = unsorted_arr;
    }

    sub_arrs[i].start_ind = i * (arr_size / thread_num);
    sub_arrs[i].end_ind = (i + 1) * (arr_size / thread_num) - 1 + remainder;
    sub_arrs[i].array_to_sort = unsorted_arr;

    if(SUCCESS != pthread_mutex_init(&lock, NULL))
    {
        perror("pthread_mutex_init");
        return SYS_FAIL;
    }

    for(i = 0; i < thread_num; ++i)
    {
        if(SUCCESS != pthread_create(&ids[i], NULL, BuildHist, &sub_arrs[i]))
        {
            perror("pthread_create");
            return SYS_FAIL;
        }
    }

    for(i = 0; i < thread_num; ++i)
    {
        if(SUCCESS != pthread_join(ids[i], NULL))
        {
            perror("pthread_join");
            return SYS_FAIL;
        }
    }

    /* Performing cummulative sum at each index */
	for(j = 1; j < ASCII; ++j)
	{
		hist_global[j] += hist_global[j - 1];
	}

    /* Creating new array to store the sorted values */
	sorted_arr = (char *)malloc((arr_size + 1) * sizeof(char));

    if(!sorted_arr) {return -1;}

    memset(sorted_arr, 0, arr_size + 1);

    /* Sorting unsorted_arr and storing the result in sorted_arr */
	ArraySort(unsorted_arr, sorted_arr, hist_global, arr_size);

    /* Copying sorted_arr into unsorted_arr */
	memcpy(unsorted_arr, sorted_arr, arr_size * sizeof(char));

    free(sorted_arr);
	sorted_arr = NULL;

    if(SUCCESS != pthread_mutex_destroy(&lock))
    {
        perror("pthread_mutex_destroy");
        return SYS_FAIL;
    }
    
    return 0;
}

void *BuildHist(void *sub_array)
{
    size_t i = 0;
    size_t hist[ASCII];
    inds_range_ty *sub_arr = (inds_range_ty *)sub_array;

    memset(hist, 0, ASCII * sizeof(size_t));

    for(i = sub_arr->start_ind; i <= sub_arr->end_ind; ++i)
    {
        ++hist[(int)(sub_arr->array_to_sort[i])];
    }

    pthread_mutex_lock(&lock);

    for(i = 0; i < ASCII; ++i)
    {
        hist_global[i] += hist[i];
    }

    pthread_mutex_unlock(&lock);

    return NULL;
}

static void ArraySort(char *unsorted_arr, char *array_to_sort, size_t *hist, 
                      size_t arr_size)
{
	char *end_unsorted_arr = NULL;
	
	assert(unsorted_arr);
	assert(array_to_sort);
	assert(hist);
    
    end_unsorted_arr = unsorted_arr + (arr_size - 1);
	
	while(end_unsorted_arr != (unsorted_arr - 1))
	{
		--hist[(int)*end_unsorted_arr];
		array_to_sort[hist[(int)*end_unsorted_arr]] = *end_unsorted_arr;
		--end_unsorted_arr;
	}
}
