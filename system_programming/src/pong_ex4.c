/*******************************************************************************
 *   pong_ex4.c                                                                *
 *   Author: Ariel                                                             *
 *   Reviewer: Bnaya                                                           *
 * ****************************************************************************/

#include <stdio.h> /* fprintf */
#include <string.h> /* memset, puts */
#include <unistd.h> /* fork, execv, sleep */
#include <signal.h>	/* sigaction, sigemptyset, sigfillset, sigdelset, */
#include <stdlib.h> /* atoi */

void SigHandler(int, siginfo_t *, void *);

volatile sig_atomic_t sig_arrived = 0;

int main(int argc, char const *argv[])
{
    struct sigaction sa = {0};
	sigset_t sigmask = {0};
    int other_proc = atoi(argv[1]);

	memset(&sa, 0, sizeof(struct sigaction));

	sa.sa_sigaction = SigHandler;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = SA_SIGINFO;
	sigfillset(&sigmask);
	sigdelset(&sigmask, SIGUSR2);
	sigdelset(&sigmask, SIGINT);

	sigaction(SIGUSR2, &sa, NULL);

    kill(other_proc, SIGUSR1);

    while (1)
    {
        if(sig_arrived)
        {
            sig_arrived = 0;
        }
    }

    return 0;
}

void SigHandler(int signum, siginfo_t *info, void *ucontext)
{
    sig_arrived = 1;
    puts("Ping...");
    sleep(1);
    kill(info->si_pid, SIGUSR1);
}
