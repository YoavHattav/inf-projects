/*********************************/
/*   System Programming          */
/*   Scheduler                   */
/*   Author: Yoav Hattav         */
/*   Last Updated 15/12/19       */
/*   Reviewed by:   Daniel       */   
/*********************************/

#include <stddef.h>	/* size_t */
#include <time.h>	/* time_t */
#include <assert.h>	/* assert */
#include <stdlib.h> /* malloc */
#include <unistd.h> /* sleep  */

#include "priorityq.h" /* Priority Queue functions */
#include "task.h"	/*Task Functions*/
#include "scheduler.h"	/*scheduler Functions*/

#define FREE(ptr) free(ptr); ptr = NULL;
#define UNUSED(s) (void)(s)
#define ON 1
#define OFF 0

struct Scheduler
{
    pq_t *q;
    int remove_current_flag;
    int stop_flag;
    task_t *current_task;
};

int MySchedluleIsBefore(const void *data1, const void *data2, void *param)
{
	UNUSED(param);

	return (((task_t *)data2)->run_time - ((task_t *)data1)->run_time);
}

scheduler_t *SchedulerCreate()
{
    scheduler_t *new_sched = (scheduler_t *)malloc(sizeof(scheduler_t));
    if (NULL != new_sched)
    {
    	new_sched->q = PQCreate(&MySchedluleIsBefore, NULL);
    	new_sched->remove_current_flag = OFF;
    	new_sched->stop_flag = OFF;
    	new_sched->current_task = NULL;

    	return new_sched;
    }
    FREE(new_sched);

    return NULL;
}

void SchedulerDestroy(scheduler_t *s)
{
	SchedulerClear(s);
	PQDestroy(s->q);
	FREE(s);
}

ilrd_uid_t SchedulerAddTask(scheduler_t *s, task_func to_do, time_t interval,
                                                                      void *param)
{
	task_t *new_task = NULL;
	ilrd_uid_t bad_uid = {0};

	assert(NULL != s);

	new_task = TaskCreate(to_do, interval, param);
	if (NULL == new_task || PQEnqueue(s->q, new_task))
	{
		FREE(new_task);
		return bad_uid;
	}

	return new_task->uid;
}

int UidCmp(void *data1, void *data2)
{
	return UIDIsSame(TaskGetUid((task_t *)data1), *(ilrd_uid_t *)data2);
}

void SchedulerRemoveTask(scheduler_t *s, ilrd_uid_t uid)
{
	assert(NULL != s);

	if (NULL != s->current_task)
	{
		if (UIDIsSame(TaskGetUid(s->current_task), uid))
		{
			s->remove_current_flag = ON;
			return;
		}	
	}
	
	TaskDestroy(PQErase(s->q, &UidCmp, &uid));
}

void SchedulerRun(scheduler_t *s)
{
	int sleeper = 0; 

	assert(NULL != s);
	
	s->remove_current_flag = OFF;
	s->stop_flag = OFF;

	while (ON != s->stop_flag)
	{
		s->current_task = (task_t *)PQDequeue(s->q);
		
		sleeper = TaskGetTimeToRun(s->current_task) - time(NULL);

		if (0 < sleeper)
		{	
			while (sleeper)
			{
				sleeper = sleep(sleeper);
			}
		}

		if(!TaskRun(s->current_task))
		{
			if (ON == s->remove_current_flag)
			{
				s->remove_current_flag = OFF;
				TaskDestroy(s->current_task);
				s->current_task = NULL;
			}
			else
			{
				TaskUpdateTimeToRun(s->current_task);
				PQEnqueue(s->q, s->current_task);
			}
		}
		else
		{
			TaskDestroy(s->current_task);
			s->current_task = NULL;
		}
	}	
}

void SchedulerStop(scheduler_t *s)
{
	assert(NULL != s);

	s->stop_flag = ON;
}

size_t SchedulerSize(const scheduler_t *s)
{
	assert(NULL != s);

	return (PQSize(s->q));
}

int SchedulerIsEmpty(const scheduler_t *s)
{
	assert(NULL != s);

	return PQIsEmpty(s->q);
}

void SchedulerClear(scheduler_t *s)
{
	size_t size = 0;

	assert(NULL != s);

	size = PQSize(s->q);

	while (0 < size)
	{
		TaskDestroy((task_t *)PQDequeue(s->q));
		--size;
	}
}
