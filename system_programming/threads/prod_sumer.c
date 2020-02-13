#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <stdlib.h>

#define NUM_OF_ELEMENTS 1000
#define NUM_OF_PRODUCED 100

int flag = 0;
int arr[NUM_OF_ELEMENTS] = {0};

void *ProducerFunction(void *data)
{
	size_t i = 0;
	test_and_set();
}

void *ConsumerFunction(void *data)
{
	
}

int main(int argc, char const *argv[])
{
	pthread_t producer;
	pthread_t consumer;
	

	return 0;
}
