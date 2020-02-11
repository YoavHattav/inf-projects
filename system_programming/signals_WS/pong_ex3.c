#include <signal.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>

void sigusr1_handler (int signal_number)
{
	write(1, "pong\n", 5);
}

int main (int argc, char *argv[])
{
	struct sigaction sa1;

	memset (&sa1, 0, sizeof  (sa1));
	sa1.sa_handler = &sigusr1_handler;
	sigaction (SIGUSR1, &sa1, NULL);
		
	while(1)
	{
		kill(atoi(argv[1]), SIGUSR2);
		pause();
	}

	return 0;
}
