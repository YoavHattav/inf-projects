/*********************************/
/*   System Programming          */
/*   WD- wd util funcs           */
/*   Author: Yoav Hattav         */
/*   Last Updated 24/02/20       */
/*   Reviewed by:                */
/*********************************/
#include <stdio.h>  /* printf */
#include <time.h>   /* time_t */
#include <unistd.h> /* sleep  */
#include <assert.h>	/* assert */
#include <signal.h> /* signals */
#include <stdlib.h> /* malloc */
#include <semaphore.h> /* sems */
#include <fcntl.h> /* named sems */

#include "../include/scheduler.h"
#include "wd.h"
#include "wd_util_funcs.h"

#define UNUSED(x) (void)(x)

int im_alive = 0;

sem_t *sem_stop_flag;

static void SigUsr1Handler(int sig)
{
	printf("handler1\n");
	++im_alive;
}

static void SigUsr2Handler(int sig)
{
	printf("handler2\n");
	sem_post(sem_stop_flag);
}		

static int AppTaskImAlive(void *param)
{
	int sem_stop_flag_value = 0;
	
	UNUSED(param);

	sem_getvalue(sem_stop_flag, &sem_stop_flag_value);

	if (0 != sem_stop_flag_value)
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

static int AppTaskIsAlive(void *param)
{
	printf("Task2\n");
	if (0 == im_alive)
	{
		int fork_return_value = 0;
		printf("Task 2 revive\n");
		kill(partner_id, SIGKILL);
		if ((fork_return_value = fork()) == 0)
		{
			execl(((wd_t *)param)->filename, ((wd_t *)param)->filename, NULL);

		}
		partner_id = fork_return_value;
		SchedulerStop(((wd_t *)param)->scheduler);
	}
	im_alive = 0;

	return 0;
}

wd_t *WDInit(enum status *status_holder)
{
	time_t interval = 2;
	int stop_flag_value = 0;
	struct sigaction sigact1 = {0};
	struct sigaction sigact2 = {0};

	struct pack *pack = malloc(sizeof(*pack));
	if (NULL == pack)
	{
		*status_holder = MEMORY_FAIL;

		return NULL;
	}
	sem_stop_flag = sem_open("/sem_stop_flag", O_CREAT, 0644, 0);
	sem_getvalue(sem_stop_flag, &stop_flag_value);

	if (SEM_FAILED == sem_stop_flag)
	{
		printf("fail\n");
		sem_unlink("/sem_stop_flag");

		*status_holder = OS_FAIL;

		return NULL;
	}

	pack->scheduler = SchedulerCreate();
	if (NULL == pack->scheduler)
	{
		printf("failed to create the scheduler\n");

		*status_holder = MEMORY_FAIL;

		return NULL;
	}
	SchedulerAddTask(pack->scheduler, &AppTaskImAlive, interval, pack);
	/*if (UIDIsSame(bad_uid, SchedulerAddTask(pack->scheduler, &AppTaskImAlive, interval, pack)))
	{
		SchedulerDestroy(pack->scheduler);
		
		*status_holder = MEMORY_FAIL;

		return NULL;
	}*/
	SchedulerAddTask(pack->scheduler, &AppTaskIsAlive, (5 * interval), pack);
	/*if (UIDIsSame(bad_uid, SchedulerAddTask(pack->scheduler, &AppTaskIsAlive, (5 * interval), pack)))
	{
		SchedulerDestroy(pack->scheduler);

		*status_holder = MEMORY_FAIL;

		return NULL;
	}*/

    sigact1.sa_handler = SigUsr1Handler;
    sigact1.sa_flags = 0;

    sigact2.sa_handler = SigUsr2Handler;
    sigact2.sa_flags = 0;

	sigaction(SIGUSR1, &sigact1, NULL);
	sigaction(SIGUSR2, &sigact2, NULL);

	return pack;
}

static void CleanUp(wd_t *pack)
{
	printf("Cleanup\n");
	SchedulerDestroy(pack->scheduler);
	sem_close(sem_stop_flag);
	sem_close(((wd_t *)pack)->p1);
	sem_close(((wd_t *)pack)->p2);

	sem_unlink("/sem_stop_flag");
}

void *WDSchedulerRun(void *pack)
{
	int sem_stop_flag_value = 0;
	
	sem_getvalue(sem_stop_flag, &sem_stop_flag_value);

	while (0 == sem_stop_flag_value)
	{
		sem_getvalue(sem_stop_flag, &sem_stop_flag_value);
		/*printf("%d\n", sem_stop_flag_value);*/
		sem_post(((wd_t *)pack)->p1);
		sem_wait(((wd_t *)pack)->p2);
		printf("run %d\n", getpid());
		SchedulerRun(((wd_t *)pack)->scheduler);
	}

	CleanUp(pack);

	return NULL;
}