/*********************************/
/*	  SUM OF DIVIDERS            */
/*    Author :Yoav Hattav        */
/*                               */
/*    Date:     17/02/2020       */
/*********************************/
#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <stdlib.h>

#define THE_NUM 1000000000
#define HUN_K 100
#define ONE 1
#define NUM_OF_THREADS 10

size_t section_sum_arr[NUM_OF_THREADS] = {0};

typedef struct range  
{
	size_t index;
	size_t start;
	size_t end;

}range_t;

void *ThreadFunction(void *data)
{
	size_t i = 0;
	range_t *range = (range_t *)data;

	for (i = range->start; i <= range->end; ++i)
	{
		if (0 == (THE_NUM % i))
		{
			section_sum_arr[range->index] += i;
		}
	}

	return NULL;
}

size_t ArraySum()
{
	size_t i = 0, sum = 0;

	for (i = 0; i < NUM_OF_THREADS; ++i)
	{
		sum += section_sum_arr[i];

	}

	return sum;
}

int main(int argc, char const *argv[])
{
	pthread_t thread[NUM_OF_THREADS];
	range_t range[NUM_OF_THREADS] = {0};

	size_t i = 0, sum = 0;

	for (i = 0; i < NUM_OF_THREADS; ++i)
	{
		range[i].start = i * (THE_NUM / NUM_OF_THREADS) + 1;
		range[i].end = (i + 1) * (THE_NUM / NUM_OF_THREADS);
		range[i].index = i;

		if (0 != pthread_create(&(thread[i]), NULL, &ThreadFunction, &(range[i]) ))
		{
			return 1;
		}
	}

	for (i = 0; i < NUM_OF_THREADS; ++i)
	{
		pthread_join(thread[i], NULL);
	}

	sum  = ArraySum(); 
	printf("%lu\n", sum);

	return 0;
}
