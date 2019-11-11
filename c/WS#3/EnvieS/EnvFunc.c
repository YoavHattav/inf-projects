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



/********* lowers the characters (not needed after lowering in Dup. see line 108.) *****/
/*
void LowerIt(char *myenvp)
{
	char *run = myenvp;

	while('\0' != *run)
	{
		*run = tolower(*run);
		++run;
	}
}
*/
/********* Prints the strings one by one */
void PrintIt(const char **myenvp)
{
	const char **run = myenvp;
	
	while(NULL != *run)
	{
		printf("%s\n", *run);
		++run;	
	}
}

/********** wrapper for malloc *****/
char *Mymalloc(int flag, int size)
{
	char *ptr=NULL;
	if (1==flag)
	{
		return ptr;
	}
	else
	{
		ptr=malloc((size+1) * sizeof(char));
		return ptr;
	}

}

/******** frees the space taken from memory */
void CleanEnvCopy(char **myenvp)
{
	char **runner = myenvp;

	while(NULL != *runner)
	{
		free(*runner);
		++runner;
	}

	free(myenvp);
}

/****** returns the size of **envp */
size_t MyEnvpLen(const char **envp)
{
	const char **runner = envp;

	assert(NULL != envp);
	

	while(NULL != *runner)
	{
		++runner;
	}

	return runner-envp;
}

/********** duplicates the strng into another */
char *MyenvDup(const char *copyofstr)
{
	int flag=0;
	const char *sour_str = copyofstr;
	int size=strlen(sour_str);
    char *alocated_str = Mymalloc(flag, size);
    char *duploc = alocated_str;

    if(alocated_str==NULL)
    {
    	return NULL;
    }
    
	assert(NULL != copyofstr);

	
    while( '\0' != *sour_str)
    {
        *alocated_str = tolower(*sour_str);
        ++alocated_str;
        ++sour_str;
    }
    *alocated_str='\0';
    return duploc;
}

/**** makes a copy of **envp *******/
char **CpyEnv(const char **envp)
{

	const char **runner_envp = envp;
	char **myenvp, **runner_myenvp;
	int counter = MyEnvpLen(envp);

	assert(NULL != envp);

	
	myenvp = (char**)calloc(counter+1, sizeof(char *));

	runner_myenvp = myenvp;

	while (NULL != *runner_envp)
	{	
		*runner_myenvp = MyenvDup(*runner_envp);
		/*LowerIt(*runner_myenvp);               *****************dont need it*******/				
		++runner_envp;
		++runner_myenvp;
	}
	return myenvp;
}

