#include <stdio.h> /*printf*/
#include <time.h> /*time(), time_t*/

#include "../include/task.h" /*task API- CHANGE THE PATH BEFORE RELEASE!*/
#include "../include/scheduler.h" /*sched API- CHANGE THE PATH BEFORE RELEASE!*/
#include "../include/uid.h" /*uid API- CHANGE THE PATH BEFORE RELEASE!*/
#include "../include/sortedlist.h" /*sll API- CHANGE THE PATH BEFORE RELEASE!*/

#define NRM "\x1B[0m"
#define RED "\x1B[31m"
#define GREEN "\x1B[32m"

#define RUN_TEST(test,err_msg) {\
							if (test)\
							{\
								printf(GREEN"SUCCESS\n"NRM);\
							} \
							else\
							{\
								printf(RED"FAIL: %s\n",err_msg);\
							}\
						}	

int task1(void *param)
{
	printf("task1 succ\n");

	return 0;
}

void CreateTaskTests()
{
	ilrd_uid_t id_holder;
	task_t *new_task1 = TaskCreate(task1, time(NULL) ,NULL);
	task_t *new_task2 = TaskCreate(task1, time(NULL) ,NULL);
	task_t *new_task3 = TaskCreate(task1, time(NULL) ,NULL);

	RUN_TEST((new_task1 != NULL) , "fails to create task1");
	RUN_TEST((new_task2 != NULL) , "fails to create task2");
	RUN_TEST((new_task3 != NULL) , "fails to create task3");
	
	RUN_TEST(TaskIsMatch(new_task2, new_task1) == 0, "unexpected match");
	RUN_TEST(TaskIsMatch(new_task3, new_task3) == 1, "false unmatch");


	id_holder = TaskGetUid(new_task1);

	TaskDestroy(new_task1);
	TaskDestroy(new_task2);
	TaskDestroy(new_task3);
}

void schedTests()
{
	
}

int main()
{
	/*
	printf("%d\n", (int)id_holder.timestamp);
	printf("%lu\n", (int)id_holder.counter);
	printf("%lu\n", (int)id_holder.pid);
	*/

	CreateTaskTests();

	return 0;
}