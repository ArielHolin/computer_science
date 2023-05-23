#include <pthread.h> /* pthread_create */
#include <sys/types.h> 
#include <sys/wait.h> /* wait */
#include <unistd.h>
#include <signal.h> /* sigset_t */
#include <stdlib.h> /* getenv, setenv */
#include <stdio.h> /* sprintf */

#include "wdt.h"

#define SUCCESS 0
#define DONT_CHANGE 0 

static void *ComHandler(void *arg);
int InitGuard(pid_t other_guard_pid, const char *other_name, 
                                        const char *my_name);
void RunGuard(void);
extern char const *env_wd_g;
extern char *wd_fname_g;

volatile pid_t wd_pid_g = 0;
int is_wd_pid_rdy_g = 0;

int KMA(const char *file_name)
{
    pthread_t guard = {0};
    sigset_t sig_mask = {0};
    pid_t wd_pid = {0};
    char const *argv[3];

    /* mask SIGUSR1, SIGUSR2 */    
    sigemptyset(&sig_mask);
    sigaddset(&sig_mask, SIGUSR1);
    sigaddset(&sig_mask, SIGUSR2);
    pthread_sigmask(SIG_BLOCK, &sig_mask, NULL);

    pthread_create(&guard, NULL, ComHandler, (char *)file_name);
    pthread_detach(guard);
    
    argv[0] = file_name;
    argv[1] = file_name;
    argv[2] = NULL;

    if (!getenv(env_wd_g))
    {
        wd_pid = fork();
        if (wd_pid == 0)
        {
            setenv(env_wd_g, env_wd_g, DONT_CHANGE);
            puts("Creating watchdog");
            execv(wd_fname_g, (char *const *)argv);
        } 
        else 
        {
            printf("wd_pid is : %d\n", wd_pid);
            wd_pid_g = wd_pid;
            is_wd_pid_rdy_g = 1;
        }
    }
    else
    {
        wd_pid_g = getppid();
        is_wd_pid_rdy_g = 1;
    }
    
    return SUCCESS;
}

/* terminate watch dog and guard */
int DNR(void)
{
    /* remove watchdog from environment */
    unsetenv(env_wd_g);
    /* first kill watchdog */
    kill(wd_pid_g, SIGUSR2);
    /* now can kill guard */
    kill(getpid(), SIGUSR2);

    return SUCCESS;
}

static void *ComHandler(void *file_name)
{
    sigset_t sig_mask = {0};
    int sig_other_rdy = SIGUSR1;

    while(!is_wd_pid_rdy_g);
    InitGuard(wd_pid_g, wd_fname_g, file_name);

    /* unmask SIGUSR1, SIGUSR2 */
    sigemptyset(&sig_mask);
    sigaddset(&sig_mask, SIGUSR1);
    sigaddset(&sig_mask, SIGUSR2);
    pthread_sigmask(SIG_UNBLOCK, &sig_mask, NULL);

    /* Wait for signal from wdt_main that it is ready */
    sigwait(&sig_mask, &sig_other_rdy);

    RunGuard();

    return NULL;
}
