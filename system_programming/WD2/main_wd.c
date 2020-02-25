/*********************************/
/*   System Programming          */
/*   WD- wd api                  */
/*   Author: Yoav Hattav         */
/*   Last Updated 20/02/20       */
/*   Reviewed by:                */
/*********************************/
#include <stdio.h>     /* printf */
#include <unistd.h>    /* sleep  */
#include <semaphore.h> /* sems */
#include <fcntl.h>     /* named sems */
#include <stdlib.h>    /* free */

#include "../include/scheduler.h"
#include "wd_util_funcs.h"

int main(int argc, char const *argv[])
{
	enum status status_holder = SUCCESS;

	struct pack *pack = NULL;
	
	partner_id = getppid();

	printf("wd: %d\n", getpid());

	pack = WDInit(&status_holder);
	if (NULL == pack)
	{
		return 1;
	}
	pack->p1 = sem_open("/sem_wd_is_ready", O_CREAT, 0644, 0);
	if (SEM_FAILED == pack->p1)
	{
		printf("failed to open /sem_wd_is_ready in wd\n");
		
		return 1;
	}
	pack->p2 = sem_open("/sem_app_is_ready", O_CREAT, 0644, 0);
	if (SEM_FAILED == pack->p2)
	{
		printf("failed to open /sem_app_is_ready in wd\n");

		return 1;
	}

	pack->partner_exec = argv[1];
	pack->my_exec = "./wd_out";

	WDSchedulerRun(pack);
	
	free(pack);pack = NULL;
	
	sem_unlink("/sem_wd_is_ready");
	sem_unlink("/sem_app_is_ready");
	
	UNUSED(argc);

	return 0;
}