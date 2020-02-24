/*********************************/
/*   System Programming          */
/*   WD- wd api                  */
/*   Author: Yoav Hattav         */
/*   Last Updated 20/02/20       */
/*   Reviewed by:   Daniel       */
/*********************************/
#include <stdio.h> /* printf */
#include <time.h>   /* time_t */
#include <unistd.h> /* sleep  */
#include <assert.h>	/* assert */
#include <semaphore.h> /* sems */
#include <fcntl.h> /* named sems */

#include "../include/scheduler.h"
#include "wd_util_funcs.h"

#define UNUSED(x) (void)(x)

int main(int argc, char const *argv[])
{
	enum status *status_holder;

	struct pack *pack = NULL;
	
	partner_id = getppid();

	printf("wd: %d\n", getpid());

	pack = WDInit(status_holder);

	pack->p1 = sem_open("/sem_wd_is_ready", O_CREAT, 0644, 0);
	if (SEM_FAILED == pack->p1)
	{
		printf("failed to open /sem_wd_is_ready in wd\n");
		sem_close(pack->p1);
		sem_unlink("/sem_wd_is_ready");
		return 1;
	}
	pack->p2 = sem_open("/sem_app_is_ready", O_CREAT, 0644, 0);
	if (SEM_FAILED == pack->p2)
	{
		printf("failed to open /sem_app_is_ready in wd\n");
		sem_close(pack->p2);
		sem_unlink("/sem_app_is_ready");
		return 1;
	}

	pack->filename = argv[0];

	WDSchedulerRun(pack);

	sem_unlink("/sem_wd_is_ready");
	sem_unlink("/sem_app_is_ready");
	
	return 0;
}