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
#include <pthread.h> /* threads */

#include "../include/scheduler.h"
#include "wd.h"
#include "wd_util_funcs.h"

wd_t *WDStart(const char *filename, enum status *status_holder)
{
	pid_t fork_return_value = 0;

	wd_t *pack = NULL;

	assert(NULL != filename);

	if ((fork_return_value = fork()) == 0)
	{
		execl("./wd_out", "./wd_out", NULL);
	}
	
	partner_id = fork_return_value;
	
	printf("app id :%d\n", getpid());
	pack = WDInit(status_holder);

	pthread_create(&pack->thread, NULL, &WDSchedulerRun, pack);

	return pack;
}

void WDStop(wd_t *pack)
{
	time_t sleep_timer = 20;
	while(sleep_timer)
	{
		sleep_timer = sleep(sleep_timer);
	}

	printf("yoav is the man\n");

	printf("my-%d\n", getpid());
	printf("wd-%d\n", partner_id);

	kill(partner_id, SIGUSR2);
	kill(getpid(), SIGUSR2);

	pthread_join((pack->thread), NULL);
}

