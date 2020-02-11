#define _POSIX_C_SOURCE 199309L

#include <signal.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>

void sigusr2_handler (int signal_number, siginfo_t *siginfo, void *data)
{
	write(1, "ping\n", 5);
	kill(siginfo->si_pid, SIGUSR1);
}

int main (int argc, char *argv[])
{
	struct sigaction sa2;

	sa2.sa_flags = SA_SIGINFO;
	sa2.sa_sigaction = &sigusr2_handler;
	sigaction (SIGUSR2, &sa2, NULL);
	
	while(1)
	{
		pause();
	}

	return 0;
}
