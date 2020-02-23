#include <stdio.h>

#include "wd.h"

int main(int argc, char const *argv[])
{
	wd_t *pack;
	enum status *status_holder;

	pack = WDStart("./app.c", status_holder);

	printf("after start\n");

	WDStop(pack);

	return 0;
}