/*********************************/
/*   System Programming          */
/*   WD- wd api                  */
/*   Author: Yoav Hattav         */
/*   Last Updated 20/02/20       */
/*   Reviewed by:   Daniel       */   
/*********************************/
#include <stdio.h>
#include <pthread.h> /* threads */
#include <time.h>   /* time_t */
#include <unistd.h> /* sleep  */
#include <assert.h>	/* assert */
#include <signal.h>
#include <stdlib.h>

#include "../include/scheduler.h"
#include "wd.h"

#define UNUSED(x) (void)(x)

typedef struct pack
{
	scheduler_t *scheduler;
	pthread_t *thread;

}wd_t;

int updated_id = 0;
int im_alive = 0;

static void SigUsr1Handler(int sig)
{
	++im_alive;
}	

static int AppTaskImAlive(void *param)
{
	UNUSED(param);

	printf("Woof\n");
	kill(updated_id, SIGUSR1);

	return 0;
}

static scheduler_t *WDInit(enum status status_holder)
{
	time_t interval = 2;
	struct sigaction sigact;

	scheduler_t *scheduler = SchedulerCreate();

	SchedulerAddTask(scheduler, &AppTaskImAlive, interval, NULL);

    sigact.sa_handler = SigUsr1Handler;
    sigact.sa_flags = 0;

	sigaction(SIGUSR1, &sigact, NULL);

	return scheduler;
}

static void *WDSchedulerRun(void *pack)
{
	SchedulerRun(((wd_t *)pack)->scheduler);

	return NULL;
}

wd_t *WDStart(const char *filename, enum status status_holder)
{
	pthread_t thread;

	wd_t *pack = malloc(sizeof(*pack));

	assert(NULL != filename);

	pack->scheduler = WDInit(status_holder);

	pthread_create(&thread, NULL, &WDSchedulerRun, pack->scheduler);

	updated_id = fork();
	if (updated_id > 0)
	{
		exec(filename);
	}

	return pack;
}

#include <signal.h>  
#include <stdio.h>  
#include <string.h>  
#include <sys/types.h>  
#include <unistd.h>
#include <sys/wait.h>

volatile sig_atomic_t state =  0;

void SigHandler(int sig)
{
    if (sig == SIGUSR1)
    {
        write(1, "PING\n", 5);
        state = 1;
    }

    if (sig == SIGUSR2)
    {
        write(1, "PONG\n", 5);
        state = 0;
    }
}

void PingPongEX1()
{	
    pid_t fork_return_status = 0;
    struct sigaction sigact;

    sigact.sa_handler = SigHandler;
    sigact.sa_flags = 0;

	sigaction(SIGUSR1, &sigact, NULL);
	sigaction(SIGUSR2, &sigact, NULL);

	fork_return_status = fork();

	if(0 < fork_return_status)
	{
		while(1)
		{
			while(1 == state)
			{
			}

			state = 1;
			kill(fork_return_status, SIGUSR1);
		}
	}

	if(0 == fork_return_status)
	{
		while(1)
		{
			while(0 == state)
			{
			}

			state = 0;
			kill(getppid(), SIGUSR2);
		}
	}	
}

int main(int argc, char *argv[])
{

 	PingPongEX1();

  	return 0;  
}