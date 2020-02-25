/*********************************/
/*   System Programming          */
/*   WD- wd api funcs            */
/*   Author: Yoav Hattav         */
/*   Last Updated 24/02/20       */
/*   Reviewed by:                */
/*********************************/
#include <stdio.h>     /* printf */
#include <pthread.h>   /* threads */
#include <time.h>      /* time_t */
#include <unistd.h>    /* getpid */
#include <assert.h>	   /* assert */
#include <signal.h>    /* signals */
#include <pthread.h>   /* threads */
#include <semaphore.h> /* sems */
#include <fcntl.h>     /* named sems */
#include <stdlib.h>    /* free */

#include "scheduler.h"
#include "wd.h"
#include "wd_util_funcs.h"

sem_t *sem_wd_is_up_flag = NULL; /**/

static void ExecWDIfNotUP(wd_t *pack)
{
	pid_t fork_return_value = 0;
	int wd_sem_up_value = 0;

	sem_wd_is_up_flag = sem_open("/sem_wd_is_up_flag", O_CREAT, 0644, 0);
	sem_getvalue(sem_wd_is_up_flag, &wd_sem_up_value);

	if (0 == wd_sem_up_value)
	{
		printf("exec wd for the first time\n");
		if ((fork_return_value = fork()) == 0)
		{
			sem_post(sem_wd_is_up_flag);
			execl(pack->partner_exec, pack->partner_exec, pack->my_exec, NULL);
		}

		partner_id = fork_return_value;
	}
	else
	{
		partner_id = getppid();
	}
}

wd_t *WDStart(const char *filename, enum status *status_holder)
{
	wd_t *pack = NULL;

	assert(NULL != filename);

	printf("start func\n");

	printf("app id :%d\n", getpid());
	pack = WDInit(status_holder);
	if (NULL == pack)
	{
		printf("failed to init pack in start func\n");

		return NULL;
	}
	pack->my_exec = filename;
	pack->partner_exec = "./wd_out";

	ExecWDIfNotUP(pack);

	pack->p1 = sem_open("/sem_app_is_ready", O_CREAT, 0644, 0);
	if (SEM_FAILED == pack->p1)
	{
		*status_holder = OS_FAIL;

		return NULL;
	}
	pack->p2 = sem_open("/sem_wd_is_ready", O_CREAT, 0644, 0);
	if (SEM_FAILED == pack->p2)
	{
		*status_holder = OS_FAIL;
		sem_close(pack->p1);
		sem_unlink("/sem_app_is_ready");

		return NULL;
	}

	if (0 != pthread_create(&pack->thread, NULL, &WDSchedulerRun, pack))
	{
		printf("thread didnt work\n");

		return NULL;
	}

	return pack;
}

void WDStop(wd_t *pack)
{
	time_t start = time(NULL);
	time_t end = 4 + start;

	int stop_flag_value = 0;

	assert(NULL != pack); /**/

	while ((0 == stop_flag_value) && (end > start))
	{
		sem_getvalue(sem_stop_flag, &stop_flag_value);
		kill(partner_id, SIGUSR2);
		kill(getpid(), SIGUSR2); 
		start = time(NULL);
	}
	if (0 == stop_flag_value)
	{
		kill(partner_id, SIGUSR2);
		kill(getpid(), SIGUSR2); 
	}

	sem_close(sem_wd_is_up_flag);

	pthread_join((pack->thread), NULL);

	sem_unlink("/sem_wd_is_ready");
	sem_unlink("/sem_app_is_ready");
	sem_unlink("/sem_wd_is_up_flag");

	free(pack);pack = NULL;
}

