#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include <assert.h>
#include "env_fun.h"




int main(int argc, char const *argv[],  const char **envp)
{
	char **myenvcpy;
	/* char arr[]="BASAD";
	char *p_arr=arr;
	LowerIt(p_arr);
	printf("%s\n", arr); */

	myenvcpy=CpyEnv(envp);
	
	PrintIt((const char **)myenvcpy);
	CleanEnvCopy(myenvcpy);
	

	return 0;
}

