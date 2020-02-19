/*********************************/
/*	  DYNAMIC SUM OF DIVIDERS    */
/*    Author :Yoav Hattav        */
/*                               */
/*    Date:     17/02/2020       */
/*********************************/
#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <stdlib.h>

typedef struct range  
{
	pthread_t thread;
	size_t index;
	size_t start;
	size_t end;
	size_t sum;
	size_t the_num;

}range_t;

void *ThreadFunction(void *data)
{
	size_t i = 0;
	range_t *range = (range_t *)data;

	for (i = range->start; i <= range->end; ++i)
	{
		if (0 == (range->the_num % i))
		{
			range->sum += i;
		}
	}

	return NULL;
}

/*
size_t ArraySum(range_t *thread_struct)
{
	size_t i = 0, sum = 0;

	sum += thread_struct->sum;

	return sum;
}
*/

int main(int argc, char const *argv[])
{
	size_t num_of_threads = atoi(argv[1]);
	size_t the_input_num = atoi(argv[2]);
	size_t i = 0, sum = 0;

	range_t *arr = malloc(sizeof(range_t) * num_of_threads);
	if (NULL == arr)
	{
		return 1;
	}

	for (i = 0; i < num_of_threads; ++i)
	{
		arr[i].start = i * (the_input_num / num_of_threads) + 1;
		arr[i].end = (i + 1) * (the_input_num / num_of_threads);
		arr[i].index = i;
		arr[i].the_num = the_input_num;
		arr[i].sum = 0;

		if (0 != pthread_create(&(arr[i].thread), NULL, &ThreadFunction, &(arr[i]) ))
		{
			return 1;
		}
	}

	for (i = 0; i < num_of_threads; ++i)
	{
		pthread_join(arr[i].thread, NULL);
	}

	for (i = 0; i < num_of_threads; ++i)
	{
		sum  += arr[i].sum;
	}

	/*sum  = ArraySum(); */
	printf("%lu\n", sum);

	return 0;
}
