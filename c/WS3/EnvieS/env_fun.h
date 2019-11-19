#ifndef _ENVFUNC_H
#define _ENVFUNC_H
#include <stddef.h>

/*void LowerIt(char *myenvp);*/
char *Mymalloc(int flag, int size);
void PrintIt(const char **myenvp);
void CleanEnvCopy(char **myenvp);
size_t MyEnvpLen(const char **envp);
char *MyenvDup(const char *copyofstr);
char **CpyEnv(const char **envp);

#endif
