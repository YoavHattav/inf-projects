/*********************************/
/*   System Programming          */
/*   WD- wd util funcs           */
/*   Author: Yoav Hattav         */
/*   Last Updated 24/02/20       */
/*   Reviewed by:                */
/*********************************/
#include <stdio.h>     /* printf */
#include <time.h>      /* time_t */
#include <unistd.h>    /* sleep  */
#include <assert.h>	   /* assert */
#include <signal.h>    /* signals */
#include <stdlib.h>    /* malloc */
#include <semaphore.h> /* sems */
#include <fcntl.h>     /* named sems */

#include "../include/scheduler.h"
#include "wd.h"
#include "wd_util_funcs.h"

int im_alive = 0;

/*********** signal handlers **********/
static void SigUsr1Handler(int sig)
{
	UNUSED(sig);
	++im_alive;
}

static void SigUsr2Handler(int sig)
{
	UNUSED(sig);
	printf("handler2\n");
	sem_post(sem_stop_flag);
}		
/*********** signal handlers **********/

/************* Tasks ******************/
static int TaskImAlive(void *param)
{
	int sem_stop_flag_value = 0;

	assert(NULL != param);

	sem_getvalue(sem_stop_flag, &sem_stop_flag_value);

	if (0 != sem_stop_flag_value)
	{
		printf("should stop here\n");
		SchedulerStop(((wd_t *)param)->scheduler);
	}
	else
	{
		printf("Woof %d\n", im_alive);
		kill(partner_id, SIGUSR1);
	}

	return 0;
}

static int TaskIsAlive(void *param)
{
	printf("Task2\n");

	assert(NULL != param);
	
	if (0 == im_alive)
	{
		int fork_return_value = 0;

		kill(partner_id, SIGKILL);

		printf("Task 2 revive\n");
		printf("executing %s\n", ((wd_t *)param)->partner_exec);
		if (0 == (fork_return_value = fork()))
		{
			execl(((wd_t *)param)->partner_exec, ((wd_t *)param)->partner_exec, ((wd_t *)param)->my_exec, NULL);

		}
		partner_id = fork_return_value;
		SchedulerStop(((wd_t *)param)->scheduler);
	}

	im_alive = 0;

	return 0;
}
/************* Tasks ******************/


wd_t *WDInit(enum status *status_holder)
{
	time_t interval = 2;
	int stop_flag_value = 0;

	struct sigaction sigact1 = {0};
	struct sigaction sigact2 = {0};

	wd_t *pack = malloc(sizeof(*pack));
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
		sem_close(sem_stop_flag);

		sem_unlink("/sem_stop_flag");

		return NULL;
	}
	
	if (UIDIsBad(SchedulerAddTask(pack->scheduler, &TaskImAlive, interval, pack)))
	{
		printf("bad uid\n");
		SchedulerDestroy(pack->scheduler);
		*status_holder = MEMORY_FAIL;

		sem_close(sem_stop_flag);

		sem_unlink("/sem_stop_flag");

		return NULL;
	}
	if (UIDIsBad(SchedulerAddTask(pack->scheduler, &TaskIsAlive, (3 * interval), pack)))
	{	
		printf("bad uid\n");

		SchedulerDestroy(pack->scheduler);
		*status_holder = MEMORY_FAIL;

		sem_close(sem_stop_flag);

		sem_unlink("/sem_stop_flag");

		return NULL;
	}
	
	sigact1.sa_handler = SigUsr1Handler;
    sigact1.sa_flags = 0;

    sigact2.sa_handler = SigUsr2Handler;
    sigact2.sa_flags = 0;

	sigaction(SIGUSR1, &sigact1, NULL); /*check fail */
	sigaction(SIGUSR2, &sigact2, NULL); /*check fail */

	*status_holder = SUCCESS;

	return pack;
}

static void CleanUp(wd_t *pack)
{
	assert(NULL != pack);

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

	assert(NULL != pack);

	sem_getvalue(sem_stop_flag, &sem_stop_flag_value);

	while (0 == sem_stop_flag_value)
	{
		sem_post(((wd_t *)pack)->p1);
		sem_wait(((wd_t *)pack)->p2);
		SchedulerRun(((wd_t *)pack)->scheduler);
		sem_getvalue(sem_stop_flag, &sem_stop_flag_value);
	}

	CleanUp(pack);
	pack = NULL;

	return NULL;
}