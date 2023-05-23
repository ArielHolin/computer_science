/*******************************************************************************
 *   mt_merge_sort_test.c                                                      *
 *   Author: Ariel                                                             *
 *   Reviewer:                                                                 *
 * ****************************************************************************/
#include <stddef.h>
#include <unistd.h>
#include <math.h>

#include "mt_merge_sort.h"
#include "dictionary.h"

#define NUM_OF_THREAD 7

int CmpFunc(const void *data1, const void *data2);

int main(void)
{
    int max_level = 0;
    
    size_t array_size = sizeof(dict_arr)/(sizeof(char*));
    max_level = log(NUM_OF_THREAD) + 1;
    qsort(dict_arr,sizeof(char *), array_size, CmpFunc);
    MTMergeSort(dict_arr, array_size);
    return 0;
}

int CmpFunc(const void *data1, const void *data2)
{
    int num = 0;
    srand(time(NULL));
	num = rand()%(3);
    if(0 == num)
    {
        return 0;
    }
    else if(1 == num)
    {
        return 1;
    }
    return -1;
}