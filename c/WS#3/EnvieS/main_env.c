#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include <assert.h>
#include "env_fun.h"


/*
Yoav Hattav

07/11/19

reviewer: Israel Drayfus
*/



int main(int argc, char const *argv[],  const char **envp)
{
	char **myenvcpy;

	myenvcpy = CpyEnv(envp);
	
	PrintIt((const char **)myenvcpy);
	CleanEnvCopy(myenvcpy);
	

	return 0;
}

