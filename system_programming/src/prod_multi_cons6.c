/*******************************************************************************
 *   multi_producer_consumer.c - exercise 6                                    *
 *   Author: Ariel                                                             *
 *   Reviewer: Eli                                                             *
 * ****************************************************************************/
#include <stddef.h>    /* size_t                                            */
#include <stdio.h>     /* printf                                            */
#include <pthread.h>   /* pthread_create, pthread_join, pthread_mutex_init,
                          pthread_mutex_lock, pthread_mutex_destroy,        */
#include <semaphore.h> /* sem_init, sem_destroy, sem_wait, sem_post         */

#define SHARED    0
#define SUCCESS   0
#define CONSUMERS 5
#define SYS_FAIL  -1
#define ROUNDS    5

pthread_mutex_t lock;
sem_t smp;
pthread_cond_t cndv;
int message = 0;
int version = 0;

void *Producer(void *arg);
void *Consumer(void *arg);

int main(void)
{
    size_t i = 0;
    pthread_t consumers[CONSUMERS];
    pthread_t producer;

    if(SUCCESS != sem_init(&smp, SHARED, 0))
    {
        perror("sem_init");
        return SYS_FAIL;
    }

    if(SUCCESS != pthread_mutex_init(&lock, NULL))
    {
        perror("pthread_mutex_init");
        return SYS_FAIL;
    }

    if(SUCCESS != pthread_cond_init(&cndv, NULL))
    {
        perror("pthread_cond_init");
        return SYS_FAIL;
    }

    if(SUCCESS != pthread_create(&producer, NULL, Producer, NULL))
    {
        perror("pthread_create");
        return SYS_FAIL;
    }

    for(i = 0; i < CONSUMERS; ++i)
    {
        if(SUCCESS != pthread_create(&consumers[i], NULL, Consumer, NULL))
        {
            perror("pthread_create");
            return SYS_FAIL;
        }
    }

    if(SUCCESS != pthread_join(producer, NULL))
    {
        perror("pthread_join");
        return SYS_FAIL;
    }

    for(i = 0; i < CONSUMERS; ++i)
    {
        if(SUCCESS != pthread_join(consumers[i], NULL))
        {
            perror("pthread_join");
            return SYS_FAIL;
        }
    }

    if(SUCCESS != sem_destroy(&smp))
    {
        perror("sem_destroy");
        return SYS_FAIL;
    }

    if(SUCCESS != pthread_mutex_destroy(&lock))
    {
        perror("pthread_mutex_destroy");
        return SYS_FAIL;
    }

    if(SUCCESS != pthread_cond_destroy(&cndv))
    {
        perror("pthread_cond_destroy");
        return SYS_FAIL;
    }

    return 0;
}

void *Producer(void *arg)
{
    while(message < ROUNDS)
    {
        size_t i = 0;
    
        for(i = 0; i < CONSUMERS; ++i)
        {
            sem_wait(&smp);
        }

        ++message;
        ++version;

        if(SUCCESS != pthread_mutex_lock(&lock))
        {
            perror("pthread_mutex_lock");
            return NULL;
        }

        pthread_cond_broadcast(&cndv);

        if(SUCCESS != pthread_mutex_unlock(&lock))
        {
            perror("pthread_mutex_unlock");
            return NULL;
        }
    }

    return arg;
}

void *Consumer(void *arg)
{
    while(message < ROUNDS)
    {
        int local_version = version;
        
        if(SUCCESS != pthread_mutex_lock(&lock))
        {
            perror("pthread_mutex_lock");
            return NULL;
        }

        sem_post(&smp);

        while(local_version == version)
        {
            pthread_cond_wait(&cndv, &lock);
        }

        printf("Thread Num: %ld, Data: %d\n",pthread_self(), message);

        if(SUCCESS != pthread_mutex_unlock(&lock))
        {
            perror("pthread_mutex_unlock");
            return NULL;
        }
    }
    return arg;
}

