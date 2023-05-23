#include <stddef.h> /* size_t */
#include <unistd.h>
#include <sys/syscall.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/wait.h> /* wait */
#include <pthread.h> /* pthread_exit */
#include <assert.h> /* assert */
#include <stdio.h> /* TODO: Remove after testing */
#include <string.h> /* strcmp */

#include "scheduler.h"

/* These defines are according to scheduler.h file */
#define CONTINUE 1
#define STOP 0

#define DONT_CHANGE 0 
#define MAX_COUNTER 5

typedef struct other_guard
{
    char *my_name;
    char *other_guard_name;
    pid_t pid;
} other_guard_ty;

static int SendLifeSignal(void *other_guard);
static int UpdateCounter(void *param);
static int IsAllive(void *other_guard);
static int ReviveOther(other_guard_ty *other_guard);
static void SigAlliveHandler(int sig);
static void SigDnrHandler(int sig);
void RunGuard(void);
static void *EliminateZombie(void *arg);


scheduler_ty *scheduler_g = NULL;
volatile size_t counter_g = 0;
volatile int is_continue_g = CONTINUE;
other_guard_ty other_guard_g = {0};
char const *env_wd_g = "WATCHDOG";
char * wd_fname_g = "./main_wdt";

int InitGuard(pid_t other_guard_pid, const char *other_name, 
                                        const char *my_name)
{
	struct sigaction allive_act = {0};
	struct sigaction term_act = {0};
    sigset_t sig_mask_1 = {0};
    sigset_t sig_mask_2 = {0};
    sigset_t sig_mask_12 = {0};

    other_guard_g.my_name = (char *)my_name;
    other_guard_g.other_guard_name = (char *)other_name;
    other_guard_g.pid = other_guard_pid;

    scheduler_g = SchedulerCreate();

    /* unmask SIGUSR1, SIGUSR2 */
    sigemptyset(&sig_mask_12);
    sigaddset(&sig_mask_12, SIGUSR1);
    sigaddset(&sig_mask_12, SIGUSR2);
    pthread_sigmask(SIG_UNBLOCK, &sig_mask_12, NULL);

    /* assign life signal handler */
    sigemptyset(&sig_mask_1);
    sigaddset(&sig_mask_1, SIGUSR1);
	allive_act.sa_handler = SigAlliveHandler;
	allive_act.sa_flags = 0;
    allive_act.sa_mask = sig_mask_1;

    /* assign DNR signal handler */
    sigemptyset(&sig_mask_2);
    sigaddset(&sig_mask_2, SIGUSR2);
    term_act.sa_handler = SigDnrHandler;
	term_act.sa_flags = 0;
    term_act.sa_mask = sig_mask_2;

    sigaction(SIGUSR1, &allive_act, NULL);
    sigaction(SIGUSR2, &term_act, NULL);

    SchedulerAdd(scheduler_g, 1, SendLifeSignal, &other_guard_g);
    SchedulerAdd(scheduler_g, 1, UpdateCounter, NULL);
    SchedulerAdd(scheduler_g, MAX_COUNTER, IsAllive, &other_guard_g);

    return SUCCESS;
}

static int SendLifeSignal(void *unused)
{
    pid_t pid = other_guard_g.pid;

    (void)unused;

    printf("My pid is: %d. other guard is: %d\n", getpid(), pid);
    printf("%s Sending signal\n", other_guard_g.my_name);
    kill(pid, SIGUSR1);

    return is_continue_g;
}

static int UpdateCounter(void *unused)
{
    (void)unused;

    ++counter_g;

    printf("%s counter is: %lu\n", other_guard_g.my_name, counter_g);

    return is_continue_g;
}

static int IsAllive(void *unused)
{
    (void)unused;

    if (counter_g > MAX_COUNTER)
    {
        printf("Reviving %s\n", other_guard_g.other_guard_name);
        ReviveOther(&other_guard_g);
    }

    return is_continue_g;
}

static int ReviveOther(other_guard_ty *other_guard)
{
    pid_t revived_pid = {0};
    char const *argv[3];

    argv[0] = other_guard_g.other_guard_name;
    argv[1] = other_guard_g.my_name;
    argv[2] = NULL;

    revived_pid = fork();
    if (revived_pid == 0)
    {
        execv(other_guard_g.other_guard_name, (char *const *)argv);
    }
    else 
    {
        pthread_t zombie_killer = {0};

        other_guard_g.pid = revived_pid; 
        pthread_create(&zombie_killer, NULL, EliminateZombie, NULL);
        pthread_detach(zombie_killer);
    }
    
    return SUCCESS;
}

static void SigAlliveHandler(int sig)
{
    (void)sig;

    printf("%s got life signal\n", other_guard_g.my_name);
    counter_g = 0;
}

static void SigDnrHandler(int sig)
{
    (void)sig;

    SchedulerDestroy(scheduler_g);
    pthread_exit(NULL);
}

void RunGuard(void)
{
    SchedulerRun(scheduler_g);
}

static void *EliminateZombie(void *arg)
{
    (void)arg;

    wait(NULL);

    return NULL;
}