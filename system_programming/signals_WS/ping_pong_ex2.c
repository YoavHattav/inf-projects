#include <signal.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>

volatile sig_atomic_t state =  0;

void sigusr1_handler (int signal_number)
{
	write(1, "ping\n", 5);
	state = 1;
}

int main (int argc, char *argv[])
{
	struct sigaction sa1;
	pid_t child_id = 0;

	memset (&sa1, 0, sizeof  (sa1));
	sa1.sa_handler = &sigusr1_handler;
	sigaction (SIGUSR1, &sa1, NULL);

	child_id = fork();

	if (0 != child_id)
	{		
		while(1)
		{
			while(0 == state){};

			state = 0;
			kill(child_id, SIGUSR2);
		}
	}

	if (0 == child_id)
	{
		execvp(argv[1], &argv[2]);
	}

	return 0;
}
