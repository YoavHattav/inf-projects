#include <stdio.h>
#include <time.h>   /* time_t */
#include <unistd.h> /* sleep  */
#include <assert.h>	/* assert */
#include <signal.h>
#include <stdlib.h>
#include <semaphore.h>
#include <fcntl.h>

#include "../include/scheduler.h"
#include "wd.h"
#include "wd_util_funcs.h"

#define UNUSED(x) (void)(x)

int im_alive = 0;

sem_t *sem_stop_flag;

static void SigUsr1Handler(int sig)
{
	++im_alive;
}

static void SigUsr2Handler(int sig)
{
	sem_post(sem_stop_flag);
}		

static int AppTaskImAlive(void *param)
{
	int sem_stop_flag_value = 0;
	
	UNUSED(param);

	sem_getvalue(sem_stop_flag, &sem_stop_flag_value);

	printf("stop_value is : %d\n", sem_stop_flag_value);

	if (1 == sem_stop_flag_value)
	{
		printf("should stop here\n");
		SchedulerStop(((wd_t *)param)->scheduler);
	}
	else
	{
		printf("Woof %d\n", im_alive);
		printf("my id %d, partner id: %d \n", getpid(), partner_id);
		kill(partner_id, SIGUSR1);
	}

	return 0;
}

/*static int AppTaskIsAlive(void *param)
{
	UNUSED(param);

	printf("Woof %d\n", im_alive);
	printf("my id %d, partner id: %d \n", getpid(), partner_id);
	kill(partner_id, SIGUSR1);

	return 0;
}*/

wd_t *WDInit(enum status *status_holder)
{
	time_t interval = 2;
	struct sigaction sigact1 = {0};
	struct sigaction sigact2 = {0};

	struct pack *pack = malloc(sizeof(*pack));
	if (NULL == pack)
	{
		return NULL;
	}

	sem_stop_flag = sem_open("/sem_stop_flag", O_CREAT, 0644, 0);
	if (SEM_FAILED == sem_stop_flag)
	{
		printf("fail\n");
		sem_unlink("/sem_stop_flag");

		return NULL;
	}
	sem_unlink("/sem_stop_flag");

	pack->scheduler = SchedulerCreate();

	SchedulerAddTask(pack->scheduler, &AppTaskImAlive, interval, pack);


    sigact1.sa_handler = SigUsr1Handler;
    sigact1.sa_flags = 0;

    sigact2.sa_handler = SigUsr2Handler;
    sigact2.sa_flags = 0;

	sigaction(SIGUSR1, &sigact1, NULL);
	sigaction(SIGUSR2, &sigact2, NULL);


	return pack;
}

void *WDSchedulerRun(void *pack)
{
	sleep(1);
	SchedulerRun(((wd_t *)pack)->scheduler);
	sleep(2);

	return NULL;
}