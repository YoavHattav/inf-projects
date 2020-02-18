/*********************************/
/*	  PRO_CONS_circular 2        */
/*    Author :Yoav Hattav        */
/*                               */
/*    Date:     17/02/2020       */
/*********************************/

#include <stdio.h>     /* printf */
#include <pthread.h>   /* threads */
#include <semaphore.h> /* semaphores */

#define NUM_OF_PROD_THREADS 1
#define NUM_OF_CONS_THREADS 5

#define ZERO 0

/**************** GLOBALS ****************/

pthread_mutex_t mutex_lock = PTHREAD_MUTEX_INITIALIZER;

sem_t produced_counter_sem = {0};

pthread_cond_t producer_blocker_cv = {0};

size_t counter = 0;

int product = 0;

/**************** GLOBALS ****************/

void *ProducerFunction(void *circ_buff)
{
	while (1)
	{
		pthread_mutex_lock(&mutex_lock);
		printf("work\n");
		++product;

		for (int i = 0; i < NUM_OF_CONS_THREADS; ++i)
		{
			sem_post(&produced_counter_sem);
		}

		pthread_cond_wait(&producer_blocker_cv, &mutex_lock);
		pthread_mutex_unlock(&mutex_lock);
	}

	return NULL;
}

void *ConsumerFunction(void *circ_buff)
{
	while (1)
	{
		sem_wait(&produced_counter_sem);
		pthread_mutex_lock(&mutex_lock);
		
		printf("%d\n", product);
		++counter;

		if (NUM_OF_CONS_THREADS == counter)
		{
			counter = 0;
			pthread_cond_signal(&producer_blocker_cv);
		}

		pthread_mutex_unlock(&mutex_lock);
	}

	return NULL;
}

int main(int argc, char const *argv[])
{
	size_t i = 0;

	pthread_t producer[NUM_OF_PROD_THREADS] = {0};
	pthread_t consumer[NUM_OF_CONS_THREADS] = {0};

	sem_init(&produced_counter_sem, ZERO, ZERO);

	pthread_cond_init(&producer_blocker_cv, NULL);

	for (i = ZERO; i < NUM_OF_PROD_THREADS; ++i)
	{
		while (ZERO != pthread_create(&(producer[i]), NULL, &ProducerFunction, NULL));
	}	

	for (i = ZERO; i < NUM_OF_CONS_THREADS; ++i)
	{
		while (ZERO != pthread_create(&(consumer[i]), NULL, &ConsumerFunction, NULL));
	}	

	for (i = ZERO; i < NUM_OF_PROD_THREADS; ++i)
	{
		pthread_join(producer[i], NULL);
	}

	for (i = ZERO; i < NUM_OF_CONS_THREADS; ++i)
	{
		pthread_join(consumer[i], NULL);
	}

	sem_destroy(&produced_counter_sem);
	pthread_cond_destroy(&producer_blocker_cv);

	return 0;
}
