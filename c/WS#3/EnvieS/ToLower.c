#include <stdio.h>

void LowerIt(char **str)
{
	char **run=str;
	while('\0' != run)
	{
		while('\0' != *run)
		{
			tolower(**run);
			++**run;
		}
	++*run;	
	}
}



void PrintIt(char **str)
{
	char **run=str;
	while('\0' != run)
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
void **CopyEnv(const char **envp)
{
char **myenv

