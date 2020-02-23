/*********************************/
/*   System Programming          */
/*   WD- wd api                  */
/*   Author: Yoav Hattav         */
/*   Last Updated 20/02/20       */
/*   Reviewed by:   Daniel       */   
/*********************************/
#include <stdio.h>
#include <time.h>   /* time_t */
#include <unistd.h> /* sleep  */
#include <assert.h>	/* assert */
#include <signal.h>
#include <stdlib.h>

#include "../include/scheduler.h"
#include "wd_util_funcs.h"

#define UNUSED(x) (void)(x)

int main()
{
	enum status *status_holder;

	struct pack *pack = NULL;
	
	partner_id = getppid();

	printf("wd: %d\n", getpid());

	pack = WDInit(status_holder);

	WDSchedulerRun(pack);

	return 0;
}