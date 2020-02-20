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

static scheduler_t *WDInit()
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

int main()
{
	wd_t *pack = malloc(sizeof(*pack));

	pack->scheduler = WDInit();

	WDSchedulerRun(pack);

	return 0;
}