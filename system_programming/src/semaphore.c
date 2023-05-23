/*******************************************************************************
 *   semaphore.c                                                               *
 *   Author: Ariel                                                             *
 *   Reviewer: Nasrat                                                          *
 * ****************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>

#define ERROR -2

typedef unsigned short ushort;

union semun 
{
    int val;
    struct semid_ds *buf;
    ushort *array;
};

int main(int argc, char **argv)
{
    char buffer[4];
    key_t key;
    int semid;
    struct sembuf sb;
    union semun arg;

    if(3 != argc)
    {
        printf("Usage: ./semaphore [num_of_semphores] [name]\n");
    }
    
    sb.sem_num = 0;
    sb.sem_op = -1;  /* set to allocate resource */
    sb.sem_flg = SEM_UNDO;

    if ((key = ftok(argv[2], 'J')) == -1) 
    {
        perror("ftok");
        return ERROR;
    }

    /* create a semaphore set with 1 semaphore: */
    if ((semid = semget(key,1, IPC_CREAT | 0666) == -1)) 
    {
        perror("semget");
        return ERROR; 
    }

    /* initialize semaphore 0 to argv[1]: */ 
    arg.val = atoi(argv[1]);
    if (semctl(semid, 0, SETVAL, arg) == -1) 
    {
        perror("semctl");
        return ERROR; 
    }

    printf("Press D [number] / I [number] / V / X: ");
    while(fgets(buffer, 4, stdin))
    {
        if('D' == buffer[0])
        {   
            sb.sem_op = atoi(&buffer[2]);

            if(sb.sem_op > semctl(semid, sb.sem_num, GETVAL))
            {
                printf("The value you asked is too large.\nYou must enter a "
                       "number at most %d\n", semctl(semid, sb.sem_num, GETVAL));
                continue;
            }

            sb.sem_op = -sb.sem_op;
            if (semop(semid, &sb, 1) == -1) 
            {
                perror("semop");
                return ERROR;
            }
            
            printf("Semaphore value decreased by %d\n", -sb.sem_op);

            if(0 == semctl(semid, sb.sem_num, GETVAL))
            {
                printf("Locked.\n");
            }
        }

        if('I' == buffer[0])
        {
            sb.sem_op = atoi(&buffer[2]);
            if (semop(semid, &sb, 1) == -1) 
            {
                perror("semop");
                return ERROR;
            }
            
            printf("Semaphore value increased by %d\n", sb.sem_op);
            printf("Unlocked\n");
        }

        if('V' == buffer[0])
        {
            printf("Semaphore value: %d\n", semctl(semid, sb.sem_num, GETVAL));
        }

        if('X' == buffer[0])
        {
            if(semctl(semid, 1, IPC_RMID) == -1)
            {
                perror("semctl");
                return ERROR;
            }
            
            return 0;
        }
    }

    return 0;
}