/*******************************************************************************
 *   child.c                                                                   *
 *   Author: Ariel                                                             *
 *   Reviewer: Bnaya                                                           *
 * ****************************************************************************/

#include <stdio.h> /* fprintf */
#include <string.h> /* memset, puts */
#include <unistd.h> /* fork, execv, sleep */
#include <signal.h>	/* sigaction, sigemptyset, sigfillset, sigdelset, */

void SigHandler(int signo);

void Child();

volatile sig_atomic_t sig_arrived = 0;

int main()
{
    Child();
    return 0;
}


void Child()
{
	struct sigaction sa;
	sigset_t sigmask;

	/* First set up the signal handler. We only want to handle the USR1
	   signal */
	sa.sa_handler = SigHandler;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = 0;

	sigaction(SIGUSR1, &sa, NULL);
	/* Now wait for the parent to return */
	sigfillset(&sigmask);
	sigdelset(&sigmask,SIGUSR1);
	sigdelset(&sigmask,SIGINT);
	while(1)
	{
        while(!sig_arrived);
        sig_arrived = 0;
		fprintf(stderr, "Pong...\n");
		sleep(1);
		kill(getppid(), SIGUSR2);
	}
}

void SigHandler(int signo)
{
	sig_arrived = 1;
}
