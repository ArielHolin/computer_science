/*******************************************************************************
 * ipc_npipew.c                                                                *
 * Author: Ariel                                                               *
 * Reviewer:                                                                   *
 * ****************************************************************************/

// C program to implement one side of FIFO
// This side writes first, then reads
#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

#define ARR_SIZE 5

int main(void)
{
    int fd;

    // FIFO file path
    char* my_npipe = "/home/ariel/infinitylabs/git/system_programming/ipc/mynpipe";

    // Creating the named file(FIFO)
    // mkfifo(<pathname>, <permission>)
    mkfifo(my_npipe, 0666);

    char* ping = "ping";
    char arr[ARR_SIZE] = {0};
    while (1)
    {
        // Open FIFO for write only
        fd = open(my_npipe, O_WRONLY);

        // Write the input arr2ing on FIFO
        // and close it
        write(fd, ping, strlen(ping)+1);
        close(fd);

        sleep(1);

        // Open FIFO for Read only
        fd = open(my_npipe, O_RDONLY);

        // Read from FIFO
        read(fd, arr, ARR_SIZE);

        // Print the read message
        printf("%s...\n", arr);
        close(fd);
    }
    return 0;
}