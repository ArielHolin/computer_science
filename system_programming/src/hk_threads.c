/*******************************************************************************
 *   threads_ex1.c                                                             *
 *   Author: Ariel                                                             *
 *   Reviewer: Bnaya                                                           *
 * ****************************************************************************/
#include <pthread.h>
#include <time.h>
#include <stdio.h>
#include <unistd.h>
#include <stddef.h>

#define HK 100000
#define SUCCESS 0

void *SetGlobalArrInd(void *ind);

size_t global_arr[HK];

int main(void)
{
    size_t i = 0;
    pthread_t ids[HK];
    time_t start;
    time_t end;

    /* Initializing ids */
    for(i = 0; i < HK; ++i)
    {
        ids[i] = i;
    }

    start = time(NULL);
    for(i = 0; i < HK; ++i)
    {
        while (SUCCESS != pthread_create(&ids[i], NULL, SetGlobalArrInd, (void *)i));
    }
    end = time(NULL);

    printf("Time taken to execute 100k threads: %ld\n", end - start);

    printf("Sleeping for 10 seconds....\n");
    sleep(10);

    for(i = 0; i < HK; ++i)
    {
        if(i != global_arr[i])
        {
            printf("Error occured in thread %ld\n", i);
            return 1;
        }
    }

    printf("Threads executed successfuly\n");

    return 0;
}

void *SetGlobalArrInd(void *ind)
{
    global_arr[(size_t)ind] = (size_t)ind;
    pthread_detach(pthread_self());
    return ind;
}