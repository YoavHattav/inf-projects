#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <stdlib.h>

#define NUM_OF_ELEMENTS 100
#define NUM_OF_PRODUCED 10

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

int arr[NUM_OF_ELEMENTS] = {0};

int producer_flag = UNLOCK;
int consumer_flag = LOCK;

void *ProducerFunction(void *data)
{
	size_t i = 0;

	for (i = 0; i < NUM_OF_PRODUCED; ++i)
	{
		size_t j = 0;

		while (__sync_lock_test_and_set(&producer_flag, LOCK));

		for (j = 0; j < NUM_OF_ELEMENTS; ++j)
		{
			arr[j] = i;
		}
		__sync_lock_test_and_set(& consumer_flag, UNLOCK);
	}

	return data;
}

void *ConsumerFunction(void *data)
{
	size_t i = 0;

	for (i = 0; i < NUM_OF_PRODUCED; ++i)
	{
		size_t j = 0;

		while (__sync_lock_test_and_set(&consumer_flag, LOCK));

		for (j = 0; j < NUM_OF_ELEMENTS; ++j)
		{
			printf("%d", arr[j]);
		}

		printf("\n");

		__sync_lock_test_and_set(&producer_flag, UNLOCK);
	}

	return data;	
}

int main(int argc, char const *argv[])
{
	pthread_t producer = {0};
	pthread_t consumer = {0};

	if (0 != pthread_create(&producer, NULL, ProducerFunction, NULL))
	{
		printf("failed to create thread\n");
		
		return 1;
	}

	if (0 != pthread_create(&consumer, NULL, ConsumerFunction, NULL))
	{
		printf("failed to create thread\n");

		return 1;
	}

	pthread_join(producer, NULL);
	pthread_join(consumer, NULL);

	return 0;
}
