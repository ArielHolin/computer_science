/*******************************************************************************
 * ipc_pipe.c                                                                  *
 * Author: Ariel                                                               *
 * Reviewer:                                                                   *
 * ****************************************************************************/
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

#define ARR_SIZE 5

int main(void)
{
    // creating pipe with 2 file descriptors
    int fd[2];

    if(-1 == pipe(fd))
    {
        perror("pipe");
        return 1;
    }

    // creating child process
    int pid = fork();

    if(-1 == pid)
    {
        perror("fork");
        return 1;
    }

    if(0 == pid)
    {
        int pong = 0;
        while(1)
        {
            if(-1 == read(fd[0], &pong, sizeof(pong)))
            {
                perror("read");
                return 1;
            }
            
            if(1 == pong)
            {
                printf("ping...\n");
                sleep(1);
            }
            pong = 0;
            
            if(-1 == write(fd[1], &pong, sizeof(pong)))
            {
                perror("write");
                return 1;
            }
            sleep(1);
        }
    }
    else
    {
        int ping = 1;
        while(1)
        {
            if(-1 == write(fd[1], &ping, sizeof(ping)))
            {
                perror("write");
                return 1;
            }
            sleep(1);

            if(-1 == read(fd[0], &ping, sizeof(ping)))
            {
                perror("read");
                return 1;
            }
            
            if(0 == ping)
            {
                printf("pong...\n");
                sleep(1);
            }
            ping = 1;
        }
    }
    return 0;
}