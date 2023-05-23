/*******************************************************************************
 *   multi_producer_consumer.c - exercise 4                                    *
 *   Author: Ariel                                                             *
 *   Reviewer: Eli                                                             *
 * ****************************************************************************/
#include <stddef.h>    /* size_t                                            */
#include <sys/types.h> /* ssize_t                                           */
#include <assert.h>    /* assert                                            */
#include <stdlib.h>    /* malloc, free                                      */
#include <stdio.h>     /* printf                                            */
#include <pthread.h>   /* pthread_create, pthread_join, pthread_mutex_init,
                          pthread_mutex_lock, pthread_mutex_destroy,        */
#include <semaphore.h> /* sem_init, sem_destroy, sem_wait, sem_post         */
#include <signal.h>    /* sig_atomic_t                                      */

/************** Declarations relevant for FSQ implementation ******************/

#define FSQ_SIZE 10
#define OFFSETOF(TYPE, ELEMENT) ((size_t)&(((TYPE *)0)->ELEMENT))

typedef struct fsq
{
    size_t write_ind;
    size_t read_ind;
    int array[1];
}fsq_ty;

fsq_ty *FSQCreate(void);
void FSQDestroy(fsq_ty *fsq);
void FSQRead(fsq_ty *fsq);
void FSQWrite(fsq_ty *fsq, int val);

/******************************************************************************/

#define ARR_SIZE 10000
#define THREADS  10
#define SUCCESS  0
#define SHARED   0
#define SYS_FAIL -1

pthread_mutex_t lock;
sem_t empty;
sem_t full;
int array[ARR_SIZE];
volatile sig_atomic_t write_ind = 0;

void *Producer(void *arg);
void *Consumer(void *arg);
static void InitArray(int array[ARR_SIZE]);

int main(void)
{
    size_t i = 0;
    pthread_t consumers[THREADS];
    pthread_t producers[THREADS];
    
    fsq_ty *fsq = FSQCreate();

    if(!fsq)
    {
        printf("System error\n");
        return 1;
    }
    
    /* Initializing array of random ints */
    InitArray(array);
 
    if(SUCCESS != sem_init(&empty, SHARED, FSQ_SIZE))
    {
        perror("sem_init");
        FSQDestroy(fsq);
        return SYS_FAIL;
    }

    if(SUCCESS != sem_init(&full, SHARED, 0))
    {
        perror("sem_init");
        FSQDestroy(fsq);
        return SYS_FAIL;
    }

    
    /* Initializing mutex */
    if(SUCCESS != pthread_mutex_init(&lock, NULL))
    {
        perror("pthread_mutex_init");
        FSQDestroy(fsq);
        return SYS_FAIL;
    }

    for(i = 0; i < THREADS; ++i)
    {
        if(SUCCESS != pthread_create(&producers[i], NULL, Producer, 
                                                                 (void *)fsq))
        {
            perror("pthread_create");
            FSQDestroy(fsq);
            return SYS_FAIL;
        }

        if(SUCCESS != pthread_create(&consumers[i], NULL, Consumer, 
                                                                 (void *)fsq))
        {
            perror("pthread_create");
            FSQDestroy(fsq);
            return SYS_FAIL;
        }
    }

    for(i = 0; i < THREADS; ++i)
    {
        if(SUCCESS != pthread_join(producers[i], NULL))
        {
            perror("pthread_join");
            FSQDestroy(fsq);
            return SYS_FAIL;
        }
        
        if(SUCCESS != pthread_join(consumers[i], NULL))
        {
            perror("pthread_join");
            FSQDestroy(fsq);
            return SYS_FAIL;
        }
    }

    if(SUCCESS != pthread_mutex_destroy(&lock))
    {
        perror("pthread_mutex_destroy");
        FSQDestroy(fsq);
        return SYS_FAIL;
    }

    if(SUCCESS != sem_destroy(&empty))
    {
        perror("sem_destroy");
        FSQDestroy(fsq);
        return SYS_FAIL;
    }

    if(SUCCESS != sem_destroy(&full))
    {
        perror("sem_destroy");
        FSQDestroy(fsq);
        return SYS_FAIL;
    }
    FSQDestroy(fsq);

    return 0;
}

void *Consumer(void *arg)
{    
    int rounds = ARR_SIZE / THREADS;

    while(rounds)
    {
        sem_wait(&full);
        
        if(SUCCESS != pthread_mutex_lock(&lock))
        {
            perror("pthread_mutex_lock");
            return NULL;
        }

        FSQRead((fsq_ty *)arg);
        --rounds;

        if(SUCCESS != pthread_mutex_unlock(&lock))
        {
            perror("pthread_mutex_unlock");
            return NULL;
        }

        sem_post(&empty);
    }

    return NULL;
}

void *Producer(void *arg)
{    
    while(write_ind < ARR_SIZE)
    {
        sem_wait(&empty);
        
        if(SUCCESS != pthread_mutex_lock(&lock))
        {
            perror("pthread_mutex_lock");
            return NULL;
        }

        if(write_ind < ARR_SIZE)
        {
            FSQWrite((fsq_ty *)arg, array[write_ind]);
            ++write_ind;
        }

        if(SUCCESS != pthread_mutex_unlock(&lock))
        {
            perror("pthread_mutex_unlock");
            return NULL;
        }

        sem_post(&full);
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

/*******************************************************************************
 **************************** FSQ *********************************************/

/******* FSQCreate ************************************************************/

fsq_ty *FSQCreate(void)
{
	fsq_ty *new_fsq = (fsq_ty *)malloc(OFFSETOF(fsq_ty, array) + 
	                                     (FSQ_SIZE * sizeof(int)));
	
	if( !new_fsq )
	{
		return NULL;
	}
	
	new_fsq->write_ind = 0;
    new_fsq->read_ind = 0;
	
	return new_fsq;
}

/******* FSQDestroy ***********************************************************/

void FSQDestroy(fsq_ty *fsq)
{
    free(fsq);
}

/******* FSQRead **************************************************************/

void FSQRead(fsq_ty *fsq)
{
    assert(fsq);

    printf("Read value: %d\n", fsq->array[fsq->read_ind]);
    fsq->read_ind = (fsq->read_ind + 1) % FSQ_SIZE;
}

/******* FSQWrite *************************************************************/

void FSQWrite(fsq_ty *fsq, int val)
{
    assert(fsq);

    fsq->array[fsq->write_ind] = val;
    fsq->write_ind = (fsq->write_ind + 1) % FSQ_SIZE;
}