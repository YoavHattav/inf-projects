#include <stdio.h>
#include <unistd.h>
#include <semaphore.h>
#include <fcntl.h>

#define NUM_OF_ITERATION 10

sem_t *pong, *ping;

int main (int argc, char *argv[])
{
	int i = 0;

	ping = sem_open("/ping", O_CREAT, 0644, 0);
	if (SEM_FAILED == ping)
	{
		printf("fail\n");
		sem_unlink("/ping");
		return 1;
	}
	
	pong = sem_open("/pong", O_CREAT, 0644, 0);
	if (SEM_FAILED == pong)
	{
		printf("fail\n");
		sem_close(ping);
		sem_unlink("/pong");
		return 1;
	}

	for (i = 0; i < NUM_OF_ITERATION; ++i)
	{
		write(1, "pong\n", 5);
		sem_post(pong);
		sem_wait(ping);
	}

	sem_close(pong);
	sem_close(ping);

	sem_unlink("/ping");
	sem_unlink("/pong");
	
	return 0;
}
