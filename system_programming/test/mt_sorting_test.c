/*******************************************************************************
 *   mt_sorting_test.c                                                         *
 *   Author: Ariel                                                             *
 *   Reviewer:                                                                 *
 * ****************************************************************************/
#include <stdio.h>  /* printf                         */
#include <stddef.h> /* size_t                         */
#include <time.h>   /* clock_t, clock, CLOCKS_PER_SEC */
#include <unistd.h>

#include "mt_sorting.h"
#include "dict_arr.h"

void TestMTCountingSortBasic(void);
void CmpMTCountingSort(int num_of_threads);

int main(void)
{
    size_t i = 0;
    int num_of_threads[4] = {1, 2, 4, 8};
    
    TestMTCountingSortBasic();
    
    for(i = 0; i < 4; ++i)
    {
        CmpMTCountingSort(num_of_threads[i]);
        sleep(2);
    }
}

void TestMTCountingSortBasic(void)
{
    size_t i = 0;
    char unsorted_arr[11] = {'t', 'q', 'b', 'a', '1', 'b', 'z', 'b', 'j', 'A', 
                                                                           'a'};
    char sorted_arr[11] = {'1', 'A', 'a', 'a', 'b', 'b', 'b', 'j', 'q', 't', 
                                                                           'z'};

    MTCountingSort(unsorted_arr, 11, 5);

    for(i = 0; i < 11; ++i)
    {
        if(unsorted_arr[i] != sorted_arr[i])
        {
            printf("MTCountingSort fails at index: %ld\n", i);
            printf("----------\n");
        }
    }

    printf("MTCountingSort Success!\n----------\n");
}

void CmpMTCountingSort(int num_of_threads)
{
    clock_t start_t;
    clock_t end_t;
    double total_t;
    size_t i = 0;

    start_t = clock();
    MTCountingSort(dict_arr, 840301, num_of_threads);
    end_t = clock();

    total_t = (double)(end_t - start_t) / CLOCKS_PER_SEC;

    printf("MTCountingSort() with %d threads time: %f\n", num_of_threads, 
                                                                       total_t);
    printf("MTCountingSort Success\n----------\n");
}