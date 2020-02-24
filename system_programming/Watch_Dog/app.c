/*********************************/
/*   System Programming          */
/*   WD- wd user app             */
/*   Author: Yoav Hattav         */
/*   Last Updated 24/02/20       */
/*   Reviewed by:                */
/*********************************/
#include <stdio.h>

#include "wd.h"

int main(int argc, char const *argv[])
{
	wd_t *pack= NULL;
	enum status status_holder;

	pack = WDStart("./app_out", &status_holder);

	printf("after start\n");

	WDStop(pack);

	return 0;
}