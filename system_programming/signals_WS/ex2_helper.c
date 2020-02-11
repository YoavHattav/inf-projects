#include <signal.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>

void sigusr2_handler (int signal_number)
{
	write(1, "pong\n", 5);
	kill(getppid() ,SIGUSR1);
}

int main (int argc, char *argv[])
{
	struct sigaction sa2;

	memset (&sa2, 0, sizeof  (sa2));
	sa2.sa_handler = &sigusr2_handler;
	sigaction (SIGUSR2, &sa2, NULL);

	kill(getppid() ,SIGUSR1);

	while (1){};

	return 0;
}
