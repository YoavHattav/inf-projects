/*********************************/
/*   System Programming          */
/*   WD- wd api funcs            */
/*   Author: Yoav Hattav         */
/*   Last Updated 24/02/20       */
/*   Reviewed by:                */
/*********************************/
#include <stdio.h> /* printf */
#include <pthread.h> /* threads */
#include <time.h>   /* time_t */
#include <unistd.h> /* sleep  */
#include <assert.h>	/* assert */
#include <signal.h> /* signals */
#include <pthread.h> /* threads */
#include <semaphore.h> /* sems */
#include <fcntl.h> /* named sems */

#include "../include/scheduler.h"
#include "wd.h"
#include "wd_util_funcs.h"

sem_t *sem_wd_is_up_flag;

wd_t *WDStart(const char *filename, enum status *status_holder)
{
	pid_t fork_return_value = 0;
	int wd_sem_up_value = 0;

	wd_t *pack = NULL;

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

	/*printf("%s\n", pack->my_exec);
	printf("%s\n", pack->partner_exec);*/

	sem_wd_is_up_flag = sem_open("/sem_wd_is_up_flag", O_CREAT, 0644, 0);
	sem_getvalue(sem_wd_is_up_flag, &wd_sem_up_value);

	if (0 == wd_sem_up_value)
	{
		printf("exec wd\n");
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

	pack->p1 = sem_open("/sem_app_is_ready", O_CREAT, 0644, 0);
	if (SEM_FAILED == pack->p1)
	{
		printf("failed to open /sem_app_is_ready\n");
		sem_unlink("/sem_app_is_ready");

		*status_holder = OS_FAIL;

		return NULL;
	}
	pack->p2 = sem_open("/sem_wd_is_ready", O_CREAT, 0644, 0);
	if (SEM_FAILED == pack->p2)
	{
		printf("failed to open /sem_wd_is_ready\n");
		sem_unlink("/sem_wd_is_ready");

		*status_holder = OS_FAIL;

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
	time_t sleep_timer = 100;
	while(sleep_timer)
	{
		sleep_timer = sleep(sleep_timer);
	}

	printf("WDStop Func.\n");

	printf("app-%d\n", getpid());
	printf("wd-%d\n", partner_id);

	kill(partner_id, SIGUSR2);
	kill(getpid(), SIGUSR2);
	sem_close(sem_wd_is_up_flag);

	pthread_join((pack->thread), NULL);

	sem_unlink("/sem_wd_is_ready");
	sem_unlink("/sem_app_is_ready");
	sem_unlink("/sem_wd_is_up_flag");
}

