#include <stdio.h>    /* printf */
#include <unistd.h>   /* pid_t  */
#include <sys/wait.h> /* wait   */

#define ERR       2
#define ILRD_TRUE 1

int main(void)
{
    char *args[] = {"./dummy", NULL}; 
    
    while(ILRD_TRUE)
    {
        pid_t pid = fork();

        if(-1 == pid)
        {
            printf("Error while creating child process\n");
            return ERR;
        }

        else if(0 == pid)
        {
            execv(args[0], args);

            /* If we have reached here, than an error occured */
            return ERR;
        }

        if(wait(NULL) != -1)
        {
            printf("Child process finished execution\n");
        }
        else
        {
            return ERR;
        }
    }

    return 0;
}