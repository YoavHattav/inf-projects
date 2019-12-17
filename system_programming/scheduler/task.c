/*********************************/
/*   System Programming          */
/*   Task                        */
/*   Author: Yoav Hattav         */
/*   Last Updated 15/12/19       */
/*   Reviewed by: Daniel         */   
/*********************************/
#include <time.h>   /* time_t */
#include <stdlib.h> /* malloc */
#include <assert.h> /* assert */

#include "task.h" /* Task Functions */
#include "uid.h" /*UID Functions*/

#define FREE(ptr) free(ptr); ptr = NULL;

task_t *TaskCreate(task_func to_do, time_t interval, void *param)
{
	task_t *new_task = (task_t *)malloc(sizeof(task_t));
	if (NULL != new_task)
	{
		new_task->uid = UIDCreate();
		new_task->taskfunc = to_do;
		new_task->param = param;
		new_task->run_time = new_task->uid.time_stamp;
		new_task->interval = interval;
		
		return new_task;
	}
	FREE(new_task);

	return NULL;
}

void TaskDestroy(task_t *t)
{
	assert(NULL != t);

	FREE(t);
}

ilrd_uid_t TaskGetUid(task_t *t)
{
	assert(NULL != t);

	return t->uid;
}

int TaskIsMatch(const task_t *t1, const task_t *t2)
{
	assert(NULL != t1);
	assert(NULL != t2);

	return (t1 == t2);
}

time_t TaskGetTimeToRun(const task_t *t)
{
	assert(NULL != t);

	return (t->run_time);
}

int TaskRun(const task_t *t)
{
	assert(NULL != t);

	return (t->taskfunc(t->param));
}

void TaskUpdateTimeToRun(task_t *t)
{
	assert(NULL != t);

	t->run_time = time(NULL) + t->interval;
}
