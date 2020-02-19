#include <stdio.h>
#include <unistd.h>
#include <semaphore.h>
#include <fcntl.h>

#define NUM_OF_ITERATION 10

sem_t *pong, *ping;

int main (int argc, char *argv[])
{
	int i = 0;

	ping = sem_open("/ping", 0);
	if (SEM_FAILED == ping)
	{
		printf("fail\n");

		return 1;
	}


	pong = sem_open("/pong", 0);
	if (SEM_FAILED == pong)
	{
		printf("fail\n");

		sem_close(ping);
		return 1;
	}


	for (i = 0; i < NUM_OF_ITERATION; ++i)
	{
		sem_wait(pong);
		write(1, "ping\n", 5);
		sem_post(ping);
	}

	sem_close(pong);
	sem_close(ping);
	
	return 0;
}
