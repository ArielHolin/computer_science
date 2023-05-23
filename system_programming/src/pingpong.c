/*******************************************************************************
 *   pingpong.c                                                                *
 *   Author: Ariel                                                             *
 *   Reviewer: Bnaya                                                           *
 * ****************************************************************************/

#include <stdio.h> /* fprintf */
#include <string.h> /* memset, puts */
#include <unistd.h> /* fork, execv, sleep */
#include <signal.h>	/* sigaction, sigemptyset, sigfillset, sigdelset, */

/* My two signal handlers. p1 for the parent, p2 for the child. */
void SigHandler1(int);
void SigHandler2(int);

/* Main will call the appropriate child or parent function after
   the fork */
void Child();
void Parent(int);

#define ERR 2

volatile sig_atomic_t sig_1_arrived = 0;
volatile sig_atomic_t sig_2_arrived = 0;

int main()
{
	struct sigaction sa_child = {0};
	struct sigaction prev = {0};
	sigset_t sigmask;
	int childpid = 0;

	memset(&sa_child, 0, sizeof(struct sigaction));

	sa_child.sa_handler = SigHandler1;
	sigemptyset(&sa_child.sa_mask);
	sa_child.sa_flags = 0;
	sigfillset(&sigmask);
	sigdelset(&sigmask, SIGUSR1);
	sigdelset(&sigmask, SIGINT);

	sigaction(SIGUSR1, &sa_child, &prev);

	childpid = fork();

    if (childpid == -1)
    {
        puts("Failed to create child");
        return ERR;
    }

	if ( childpid == 0 )
	{
		/* For ex1: */
		/* Child(); */

		/* For ex2: */
		execv("./child", NULL);
	}
	else 
	{
		sigaction(SIGUSR1, &prev, NULL);
		sig_2_arrived = 1;
		Parent(childpid);
	}
	return 0;
}

void Parent(int childpid)
{
	struct sigaction sa;
	sigset_t sigmask;

	/* First set up the signal handler. We only want to handle the USR1
	   signal */
	sa.sa_handler = SigHandler2;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = 0;

	sigaction(SIGUSR2, &sa, NULL);

	/* The parent sends the first signal. */
	sigfillset(&sigmask);
	/* Every signal active in the signal mask will be blocked during
		the suspend. If I want a signal to resume my code, I must
		delete that signal from the signal mask */
	sigdelset(&sigmask,SIGUSR2);
	/* The signal mask will identify all signals to be blocked for
		this wait. If I keep the SIGINT blocked in the sigmask, my
		process will not return if the user presses Ctrl-C at the
		keyboard. In order to let SIGINT be processed, I must remove
		it from this mask, or it will be blocked indefinitely. */
	sigdelset(&sigmask,SIGINT);
	/* Two signals are unmasked for this suspend: SIGUSR2 and SIGINT
		Because SIGUSR2 has a custom signal handler that does not
		call exit(), sigsuspend will exit on SIGUSR2.
		Because SIGINT is not handled, the default handler will call
		the exit() function, and sigsuspend will never return. */
 	while(1)
	{
		while(!sig_2_arrived);
		sig_2_arrived = 0;
		fprintf(stderr, "Ping...\n");
		sleep(1);
		kill(childpid, SIGUSR1);
	}
}

void Child()
{
	sigset_t sigmask;
	/* Now wait for the parent to return */
	sigfillset(&sigmask);
	sigdelset(&sigmask, SIGUSR1);
	sigdelset(&sigmask, SIGINT);
	while(1)
	{
		/* Parent serves first */
		while(!sig_1_arrived);
		sig_1_arrived = 0;
		fprintf(stderr, "Pong...\n");
		sleep(1);
		kill(getppid(), SIGUSR2);
	}
}

void SigHandler1(int signo)
{
	sig_1_arrived = 1;
}

void SigHandler2(int signo)
{
	sig_2_arrived = 1;
}