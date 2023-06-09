/*******************************************************************************
 * C Program for Shared Memory (Writer Process)                                *
 * ipc_smw.c                                                                   *
 * Author: Ariel                                                               *
 * Reviewer:                                                                   *
 * ****************************************************************************/
#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdio.h>

#define MAX 10
  
int main(void)
{
    // ftok to generate unique key
    key_t key = ftok("shmfile", 65);
  
    // shmget returns an identifier in shmid
    int shmid = shmget(key, 1024, 0666|IPC_CREAT);
  
    // shmat to attach to shared memory
    char *str = (char*)shmat(shmid,(void*)0,0);
  
    printf("Write Data : ");
    fgets(str, MAX, stdin);
  
    printf("Data written in memory: %s\n",str);
      
    //detach from shared memory 
    shmdt(str);

    printf("Writer process terminated...\n");
  
    return 0;
}