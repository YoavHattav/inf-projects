#ifndef _WD_H_
#define _WD_H_

#include <pthread.h>

typedef struct pack wd_t;

enum status{
	SUCCESS,
	MEMORY_FAIL,
	OS_FAIL
};

/* the function recives a pointer to a thread created by the user */
/* which will hold the tread to be joined in WDStop(). the first argument is the excute filename by path */
/* this function guards the process from failing postcall. if the process fails, it will be revived. */
/* Return value: 0 for success, 1 for fail. */
wd_t *WDStart(const char *filename, enum status *status_holder);

/* the function ends the reviving effect. */
/* it recievs the pointer to the tread created in WDStart() */
void WDStop(wd_t *pack);

#endif