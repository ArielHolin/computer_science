#include <stdlib.h> /* atoi */
#include <signal.h> /* SIGUSR1 */
#include <pthread.h> /* pid */
#include <sys/types.h>
#include <unistd.h>

#include <stdio.h> /* TODO: Remove after testing */

/***********************/
int InitGuard(pid_t other_guard_pid, const char *other_name, 
                                        const char *my_name);
void RunGuard(void);
extern char *wd_fname_g;
/**********************/

int main(int argc, char const *argv[])
{
    (void)argc;

    InitGuard(getppid(), (char *)argv[1], wd_fname_g);

    /* Signal guard that Im ready */
    printf("I, WD, am sending rdy signal to: %d\n", getppid());
    kill(getppid(), SIGUSR1);

    RunGuard();

    return 0;
}
