/*********************************/
/*	  PRO_CONS_MUTEX             */
/*    Author :Yoav Hattav        */
/*                               */
/*    Date:     17/02/2020       */
/*********************************/

#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <stdlib.h>

#include "dll.h"

#define NUM_OF_THREADS 10
#define NUM_OF_ELEMENTS 30000

#define GREEN "\033[;032m"
#define RED   "\033[;031m"
#define RESET "\033[0m"

#define RUN_TEST(test)\
{\
  if(test)\
  {\
    printf(GREEN);\
    printf("SUCCESS\n");\
    printf(RESET);\
  }\
  else\
  {\
    printf(RED);\
    printf("FAIL \n");\
    printf(RESET);\
  }\
}

enum state{
	UNLOCK,
	LOCK
};

pthread_mutex_t mutex_lock = PTHREAD_MUTEX_INITIALIZER;

size_t arr[NUM_OF_ELEMENTS] = {0};

int data_index = 0;

void *ProducerFunction(void *list)
{
	pthread_mutex_lock(&mutex_lock);

	if (!DLLPushFront((dll_t *)list, &arr[data_index]))
	{
		printf("insert failed\n");

		return NULL;
	}
	++data_index;

	pthread_mutex_unlock(&mutex_lock);
		
	return NULL;
}

void *ConsumerFunction(void *list)
{
	void *removed_value = NULL;

	pthread_mutex_lock(&mutex_lock);

	while (DLLIsEmpty((dll_t *)list))
	{
		pthread_mutex_unlock(&mutex_lock);
		pthread_mutex_lock(&mutex_lock);
	}

	removed_value = DLLPopBack((dll_t *)list);
	printf("%d\n", *(int *)removed_value);

	pthread_mutex_unlock(&mutex_lock);
	
	return NULL;	
}

int main(int argc, char const *argv[])
{
	int i = 0;
	pthread_t producer[NUM_OF_THREADS] = {0};
	pthread_t consumer[NUM_OF_THREADS] = {0};
	

	dll_t *list = DLLCreate();
	if (NULL == list)
	{
		return 1;
	}

	for (i = 0; i < NUM_OF_ELEMENTS; ++i)
	{
		arr[i] = i;
	}

	for (i = 0; i < NUM_OF_THREADS; ++i)
	{
		while (0 != pthread_create(&(producer[i]), NULL, &ProducerFunction, (void *)list));
		while (0 != pthread_create(&(consumer[i]), NULL, &ConsumerFunction, (void *)list));
	}	

	for (i = 0; i < NUM_OF_THREADS; ++i)
	{
		pthread_join(producer[i], NULL);
	}

	for (i = 0; i < NUM_OF_THREADS; ++i)
	{
		pthread_join(consumer[i], NULL);
	}

	printf("size is:%lu\n" ,DLLSize(list));

	DLLDestroy(list);

	return 0;
}
