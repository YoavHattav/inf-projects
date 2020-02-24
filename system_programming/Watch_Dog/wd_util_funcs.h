#ifndef _WD_UTIL_FUNCS_H_
#define _WD_UTIL_FUNCS_H_

#include <pthread.h>
#include <semaphore.h>
#include "wd.h"
#include "../include/scheduler.h"

pid_t partner_id;

struct pack
{
	scheduler_t *scheduler;
	sem_t *p1;
	sem_t *p2;
	const char *filename;
	pthread_t thread;
};

wd_t *WDInit(enum status *status_holder);

void *WDSchedulerRun(void *pack);

#endif