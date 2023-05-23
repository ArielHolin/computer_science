/*******************************************************************************
 *   multi_producer_consumer.c - exercise 2                                    *
 *   Author: Ariel                                                             *
 *   Reviewer: Eli                                                             *
 * ****************************************************************************/
#include <stdio.h>   /* printf                       */  
#include <pthread.h> /* pthread_create, pthread_join, pthread_mutex_init,
                        pthread_mutex_lock, pthread_mutex_destroy,  */
#include <signal.h>  /* sig_atomic_t */
#include <stddef.h>  /* size_t */
#include <stdlib.h>  /* rand */

#include "dlist.h"

#define ARR_SIZE 10000
#define FIVE_K   5000
#define THREADS  10
#define SUCCESS  0
#define TRUE     1
#define SYS_FAIL -1

pthread_mutex_t lock;
int array[ARR_SIZE];
int counter = 0;

void *Consumer(void *arg);
void *Producer(void *arg);
static void InitArray(int array[ARR_SIZE]);

int main(void)
{
    size_t i = 0;
    pthread_t consumers[THREADS];
    pthread_t producers[THREADS];
    
    dlist_ty *dlist = DListCreate();

    if(!dlist)
    {
        printf("System error\n");
        return SYS_FAIL;
    }
    
    /* Initializing array of random ints */
    InitArray(array);
 
    /* Initializing mutex */
    if(SUCCESS != pthread_mutex_init(&lock, NULL))
    {
        perror("pthread_mutex_init");
        DListDestroy(dlist);
        return SYS_FAIL;
    }

    for(i = 0; i < THREADS; ++i)
    {
        if(SUCCESS != pthread_create(&producers[i], NULL, Producer, 
                                                                 (void *)dlist))
        {
            perror("pthread_create");
            DListDestroy(dlist);
            return SYS_FAIL;
        }

        if(SUCCESS != pthread_create(&consumers[i], NULL, Consumer, 
                                                                 (void *)dlist))
        {
            perror("pthread_create");
            DListDestroy(dlist);
            return SYS_FAIL;
        }
    }

    for(i = 0; i < THREADS; ++i)
    {
        if(SUCCESS != pthread_join(producers[i], NULL))
        {
            perror("pthread_join");
            DListDestroy(dlist);
            return SYS_FAIL;
        }
        
        if(SUCCESS != pthread_join(consumers[i], NULL))
        {
            perror("pthread_join");
            DListDestroy(dlist);
            return SYS_FAIL;
        }
    }

    pthread_mutex_destroy(&lock);
    DListDestroy(dlist);

    return 0;
}

void *Consumer(void *arg)
{
    while(!DListIsEmpty((dlist_ty *)arg))
    {
        void *ret = NULL;
        
        if(SUCCESS != pthread_mutex_lock(&lock))
        {
            perror("pthread_mutex_lock");
            return NULL;
        }

        if(!DListIsEmpty((dlist_ty *)arg))
        {
            ret = DListPopBack((dlist_ty *)arg);
            printf("Popped value: %d\n", *(int *)ret);
        }

        if(SUCCESS != pthread_mutex_unlock(&lock))
        {
            perror("pthread_mutex_unlock");
            return NULL;
        }
    }

    return NULL;
}

void *Producer(void *arg)
{
    while(counter < ARR_SIZE)
    {
        dlist_iter_ty end = DListEnd((dlist_ty *)arg);
        dlist_iter_ty ret_iter = NULL;
        
        if(SUCCESS != pthread_mutex_lock(&lock))
        {
            perror("pthread_mutex_lock");
            return NULL;
        }
        
        if(counter < ARR_SIZE)
        {
            ret_iter = DListPushFront((dlist_ty *)arg, &array[counter]);
        
            if(!DListIsEqual(ret_iter, end))
            {
                ++counter;
            }
        }

        if(SUCCESS != pthread_mutex_unlock(&lock))
        {
            perror("pthread_mutex_unlock");
            return NULL;
        }
    }

    return NULL;
}

static void InitArray(int array[ARR_SIZE])
{
	int i = 0;
	
	for(i = 0; i < ARR_SIZE; ++i)
	{
		array[i] = i;
	}
}
