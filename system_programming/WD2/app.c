/*********************************/
/*   System Programming          */
/*   WD- wd user app             */
/*   Author: Yoav Hattav         */
/*   Last Updated 24/02/20       */
/*   Reviewed by:                */
/*********************************/
#include <unistd.h> /* sleep */

#include "wd.h"

#define UNUSED(x) (void)(x)

int main(int argc, char const *argv[])
{
	wd_t *pack= NULL;
	enum status status_holder = SUCCESS;
	time_t sleep_timer = 30;

	pack = WDStart(argv[0], &status_holder);

	/********* MMI *************/
	while(sleep_timer)
	{
		sleep_timer = sleep(sleep_timer);
	}
	/********* DNR *************/
	
	WDStop(pack);

	UNUSED(argc);

	return 0;
}