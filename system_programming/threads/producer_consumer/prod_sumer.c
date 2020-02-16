#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <stdlib.h>

#define NUM_OF_ELEMENTS 100
#define NUM_OF_PRODUCED 10

#define GREEN "\033[;032m"
#define RED   "\033[;031m"
#define RESET "\033[0m"
#define UNUSED(x) (void)(x)
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

int lock_flag = 0;
int arr[NUM_OF_ELEMENTS] = {0};

void *ProducerFunction(void *data)
{
	size_t i = 0;

	for (i = 0; i < NUM_OF_PRODUCED; ++i)
	{
		size_t j = 0;

		while (!__sync_lock_test_and_set(&lock_flag, 1));

		for (j = 0; j < NUM_OF_ELEMENTS; ++j)
		{
			arr[j] = i;
		}

		__sync_lock_release(&lock_flag);
	}

	return data;
}

void *ConsumerFunction(void *data)
{
	size_t i = 0;

	for (i = 0; i < NUM_OF_PRODUCED; ++i)
	{
		size_t j = 0;

		while (__sync_lock_test_and_set(&lock_flag, 0));

		for (j = 0; j < NUM_OF_ELEMENTS; ++j)
		{
			printf("%d\n", arr[j]);
			RUN_TEST(arr[j] == arr[NUM_OF_ELEMENTS - 1]);
		}

		__sync_lock_release(&lock_flag);
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
