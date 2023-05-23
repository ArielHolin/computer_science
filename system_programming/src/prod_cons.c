/*******************************************************************************
 *   producer_consumer.c                                                       *
 *   Author: Ariel                                                             *
 *   Reviewer:                                                                 *
 * ****************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <signal.h>
#include <stddef.h>

#define ARR_SIZE 10000
#define SUCCESS  0

int array[ARR_SIZE];
int produce = 0;
int rounds = 5;

void *ArrIncrement(void *arg);
void *ArrSum(void *arg);

int main(void)
{
    pthread_t id1 = 1;
    pthread_t id2 = 2;

    while(SUCCESS != pthread_create(&id1, NULL, ArrIncrement, NULL));
    while(SUCCESS != pthread_create(&id2, NULL, ArrSum, NULL));

    while(SUCCESS != pthread_join(id1, NULL));
    while(SUCCESS != pthread_join(id2, NULL));

    return 0;
}

void *ArrIncrement(void *arg)
{
    size_t i = 0;

    while(rounds > 0)
    {
        while(produce == 0)
        {
            for(i = 0; i < ARR_SIZE; ++i)
            {
                ++array[i];
            }

            produce = 1;
        }
    }

    return arg;
}

void *ArrSum(void *arg)
{
    while(rounds > 0)
    {
        while(produce == 1)
        {
            size_t i = 0;
            int sum = 0;

            for(i = 0; i < ARR_SIZE; ++i)
            {
                sum += array[i];
            }

            printf("Sum: %d\n", sum);
            produce = 0;
            --rounds;
        }
    }

    return arg;
}

