#ifndef _WS8EX1_H_
#define _WS8EX1_H_ 

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define SIZE_ARR 4
#define SIZEOFSTR 16
#define UNUSED(x) (void)(x)

typedef struct  mycreation 
{
	void *data;
	void (*Pprint)(const void *data);
	void (*Padd)(void *data, int x);
	int (*Pclean)(void *data);

}FourPStruct;

/* Print Funcs */
void PrintInt(const void* data);
void PrintFloat(const void *data);
void PrintStr(const void *data);

/* Add Funcs */
void AddInt(void* data, int x);
void AddFloat(void* data, int x);
void AddToStr(void *data, int x);

/* Allocations Cleanup */
int Clean(void* data);
int CleanNothing(void* data);

/* Initiation and Usage Funcs */
void init(FourPStruct arr[]);
void InfraS(FourPStruct arr[]);

#endif