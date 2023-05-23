/*******************************************************************************
 * ipc_npiper.c                                                                *
 * Author: Ariel                                                               *
 * Reviewer:                                                                   *
 * ****************************************************************************/

// C program to implement one side of FIFO
// This side reads first, then reads
#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

#define ARR_SIZE 5

int main(int argc, char *argv[])
{   
    int fd1;

    // FIFO file path
    char* my_npipe = "/home/ariel/infinitylabs/git/system_programming/ipc/mynpipe";

    // Creating the named file(FIFO)
    // mkfifo(<pathname>,<permission>)
    mkfifo(my_npipe, 0666);

    char arr1[ARR_SIZE] = {0};
    char* pong = "pong";
    while (1)
    {
        // First open in read only and read
        fd1 = open(my_npipe, O_RDONLY);
        read(fd1, arr1, ARR_SIZE);

        // Print the read string and close
        printf("%s...\n", arr1);
        close(fd1);

        // Now open in write mode and write
        // string taken from user.
        fd1 = open(my_npipe, O_WRONLY);
        write(fd1, pong, strlen(pong)+1);
        close(fd1);

        sleep(1);
    }
    return 0;
}