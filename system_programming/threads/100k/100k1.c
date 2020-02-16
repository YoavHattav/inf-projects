#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

#define HUN_K 100000
#define ONE 1

int arr[HUN_K] = {0};

int SumArray()
{
	int sum = 0, i = 0;

	for (i = 0; i< HUN_K; ++i)
	{
		sum += arr[i];
	}

	return sum;
}
void *ThreadFunction(void *index)
{
	arr[(size_t)index] = ONE;

	return NULL;
}

int main()
{
	pthread_t thread[HUN_K];

	size_t i = 0;

	for (i = 0; i < HUN_K; ++i)
	{
		while (0 != pthread_create(&(thread[i]), NULL, &ThreadFunction, (void *)i));
		pthread_detach(thread[i]);
	}

	sleep(1);

	printf("%d\n", SumArray());

	return 0;
}