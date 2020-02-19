/*********************************/
/*	  PRO_CONS_circular 1        */
/*    Author :Yoav Hattav        */
/*                               */
/*    Date:     17/02/2020       */
/*********************************/

#include <stdio.h>     /* printf */
#include <pthread.h>   /* threads */
#include <semaphore.h> /* semaphores */

#include "circular_overflow.h"

#define NUM_OF_PROD_THREADS 300
#define NUM_OF_CONS_THREADS 300

#define ZERO 0
#define CAPACITY 30
#define DATA_ARRAY_SIZE 3000

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

/**************** GLOBALS ****************/

pthread_mutex_t mutex_lock = PTHREAD_MUTEX_INITIALIZER;

size_t arr[DATA_ARRAY_SIZE] = {0};

int data_index = 0;

sem_t write_counter;
sem_t read_counter;

/**************** GLOBALS ****************/

void *ProducerFunction(void *circ_buff)
{
	sem_wait(&write_counter);

	pthread_mutex_lock(&mutex_lock);
	CBufferWrite((cbuffer_t *)circ_buff, &arr[data_index]);
	++data_index;
	pthread_mutex_unlock(&mutex_lock);

	sem_post(&read_counter);

	return NULL;
}

void *ConsumerFunction(void *circ_buff)
{
	int removed_value = 0;

	sem_wait(&read_counter);

	pthread_mutex_lock(&mutex_lock);
	printf("%d\n", *(int *)CBufferRead((cbuffer_t *)circ_buff, &removed_value));
	pthread_mutex_unlock(&mutex_lock);

	sem_post(&write_counter);
	
	return NULL;	
}

int main(int argc, char const *argv[])
{
	int i = 0;
	size_t capacity = CAPACITY;

	pthread_t producer[NUM_OF_PROD_THREADS] = {0};
	pthread_t consumer[NUM_OF_CONS_THREADS] = {0};
	
	cbuffer_t *circ_buff = CBufferCreate(capacity);

	printf("capacity : %lu\n", CBufferCapacity(circ_buff));

	sem_init(&read_counter, ZERO, ZERO);
	sem_init(&write_counter, ZERO, CAPACITY);

	if (NULL == circ_buff)
	{
		return 1;
	}

	for (i = ZERO; i < DATA_ARRAY_SIZE; ++i)
	{
		arr[i] = i;
	}

	for (i = ZERO; i < NUM_OF_PROD_THREADS; ++i)
	{
		while (ZERO != pthread_create(&(producer[i]), NULL, &ProducerFunction, (void *)circ_buff));
	}	

	for (i = ZERO; i < NUM_OF_CONS_THREADS; ++i)
	{
		while (ZERO != pthread_create(&(consumer[i]), NULL, &ConsumerFunction, (void *)circ_buff));
	}	

	for (i = ZERO; i < NUM_OF_PROD_THREADS; ++i)
	{
		pthread_join(producer[i], NULL);
	}

	for (i = ZERO; i < NUM_OF_CONS_THREADS; ++i)
	{
		pthread_join(consumer[i], NULL);
	}

	printf("free space is:%lu\n" , CBufferFreeSpace(circ_buff));

	CBufferDestroy(circ_buff);

	return 0;
}
