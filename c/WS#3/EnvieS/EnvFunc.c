#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include <assert.h>
#include "env_fun.h"

void LowerIt(char *myenvp)
{
	char *run=myenvp;
	while('\0' != *run)
	{
		*run=tolower(*run);
		++run;
	}
}

void PrintIt(const char **myenvp)
{
	const char **run=myenvp;
	while(NULL != *run)
	{
		printf("%s\n", *run);
		++run;	
	}
}


void CleanEnvCopy(char **myenvp)
{
	char **runner=myenvp;

	while(NULL != *runner)
	{
		free(*runner);
		++runner;
	}

	free(myenvp);
}

size_t MyEnvpLen(const char **envp)
{
	const char **runner= envp;
	assert(NULL != envp);
	

	while(NULL != *runner)
	{
		++runner;
	}
	return runner-envp;
}


char *MyenvDup(const char *copyofstr)
{
	const char *sour_str=copyofstr;
    char *alocated_str = malloc((strlen(sour_str)) * sizeof(char));
    char *duploc = alocated_str;

	assert(NULL != copyofstr);

	
    while( '\0' != *sour_str)
    {
        *alocated_str = *sour_str;
        ++alocated_str;
        ++sour_str;
    }
    return duploc;
}

char **CpyEnv(const char **envp)
{

	const char **runner_envp= envp;
	char **myenvp, **runner_myenvp;
	int counter=MyEnvpLen(envp);

	assert(NULL != envp);

	
	myenvp = (char**)calloc(counter+1, sizeof(char *));

	runner_myenvp = myenvp;

	while (NULL != *runner_envp)
	{	
		*runner_myenvp=MyenvDup(*runner_envp);
		LowerIt(*runner_myenvp);				/****can be sent to lower here..****/
		++runner_envp;
		++runner_myenvp;
	}
	return myenvp;
}

