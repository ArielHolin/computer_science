#include <stdlib.h> /* system */
#include <stdio.h> /* puts */

#define ERR 2
#define ILRD_TRUE 1

int main(void)
{
    int status = 0;
    const char *cmd = "gcc dummy.c -o dummy && ./dummy";

    status = system(cmd);

    if (status == -1)
    {
        puts("Child could not be created or it's status could not be retrieved");
    }
    
    if (status == 127)
    {
        puts("Shell could not be executed");
    }
    
    puts("System() call was successful!");

    return 0;
}
