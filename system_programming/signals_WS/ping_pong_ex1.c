#include <signal.h>  
#include <stdio.h>  
#include <string.h>  
#include <sys/types.h>  
#include <unistd.h>
#include <sys/wait.h>

volatile sig_atomic_t state =  0;

void SigHandler(int sig)
{
    if (sig == SIGUSR1)
    {
        write(1, "PING\n", 5);
        state = 1;
    }

    if (sig == SIGUSR2)
    {
        write(1, "PONG\n", 5);
        state = 0;
    }
}

void PingPongEX1()
{	
    pid_t fork_return_status = 0;
    struct sigaction sigact;

    sigact.sa_handler = SigHandler;
    sigact.sa_flags = 0;

	sigaction(SIGUSR1, &sigact, NULL);
	sigaction(SIGUSR2, &sigact, NULL);

	fork_return_status = fork();

	if(0 < fork_return_status)
	{
		while(1)
		{
			while(1 == state)
			{
			}

			state = 1;
			kill(fork_return_status, SIGUSR1);
		}
	}

	if(0 == fork_return_status)
	{
		while(1)
		{
			while(0 == state)
			{
			}

			state = 0;
			kill(getppid(), SIGUSR2);
		}
	}	
}

int main(int argc, char *argv[])
{

 	PingPongEX1();

  	return 0;  
}