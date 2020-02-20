#include <stdio.h>  
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>

void WatchDogExe(char *argv[])
{
	int zero_val = 0;
	while (1)
	{
		pid_t pid = fork();
		if (pid == 0)
		{
			execvp(argv[2], &argv[3]);
		}
		else
		{
			wait(&zero_val);
		}
	}
}

void WatchDogSys(char *argv[])
{
	while (1)
	{
		system(argv[2]);
	}
}

int main(int argc, char *argv[])
{
	if (0 == strcmp("system", argv[1]))
	{
		WatchDogSys(argv);
	}
	else if (0 == strcmp("fork", argv[1]))
	{
		WatchDogExe(argv);
	}

	return 0;
}