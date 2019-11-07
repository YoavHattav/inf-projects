#include <stdio.h>

void LowerIt(char **myenv)
{
	char **run=myenvp;
	while('\0' != *run)
	{
		while('\0' != **run)
		{
			tolower(**run);
			++*run;
		}
	++*run;	
	}
}



void PrintIt(char **myenp)
{
	char **run=myenvp;
	while('\0' != *run)
	{
		printf("%s", *run);
		++*run;	
	}
}


size_t Sizeofenv(const char **envp)
{
	assert(NULL != **envp);
	const char **runner= envp;
	while('\0' != *runner)
	{
		++runner;
	}
	return runner-str;
}

size_t MyEnvpLen(const char **envp)
{
	assert(NULL != envp);
	const char **runner= envp;
	while('\0' != *runner)
	{
		++runner;
	}
	return runner-envp;
}




void CleanEnvCopy(char **myenvp)
{
	char **runner=myenvp;

	while('\0' != *runner)
	{
		free(*runner);
	}

	free(myenvp);
}




char **CpyEnv(const char **envp)
{

	assert(NULL != envp);

	char **runner= envp;
	char **myenvp=NULL;
	counter=MyEnvpLen(envp);
	char **runmy=myenvp;

	myenvp = (char**)calloc(counter+1, sizeof(char*));

	while ('\0' != *runner)
	{	
		*myenvp=strdup(*runner);
		++runner;
		++myenvp;
	}

}



void MyMalloc(char **myevp)
{

}