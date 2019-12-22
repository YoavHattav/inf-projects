/************************************************
*
* File: fsa_test.c
* Ex: fixed size allocator
* writer: Israel Drayfus
* Date: 18.12.2019
* Description: run and test functions of fixed size allocator.
*
*************************************************/

#include <stdio.h> /*printf()*/
#include <stdlib.h> /*malloc()*/

#include "fsa.h" /*API header*/

#define RED "\033[31m"
#define GREEN "\033[32m"
#define WHITE "\033[0m"
#define CYAN "\033[36m"

#define TEST(test, errMsg) if (test)\
						   {\
						      printf(GREEN);\
						      printf("%s\n", "SUCCESS");\
						   }\
						   else\
						   {\
						      printf(RED);\
						      printf("%s, %s\n", "FAILURE", errMsg);\
						   }\
						   printf(WHITE);

#define WORD 8
#define UNALIGNED 1
#define BLOCKS_COUNT 4

void Test1(fsa_t *fsa)
{
	while (FSACountFree(fsa))
	{
		printf("%lu ", FSACountFree(fsa));
		FSAAlloc(fsa);
	}
	printf("\n");
}

void Test2(fsa_t *fsa)
{
	void *block = NULL;
	
	block = FSAAlloc(fsa);
	printf("%lu ", FSACountFree(fsa));
	FSAFree(block);
	printf("%lu\n", FSACountFree(fsa));
}

void Test3(fsa_t *fsa)
{
	void *block = NULL;
	
	block = FSAAlloc(fsa);
	FSAAlloc(fsa);
	FSAFree(block);
	printf("%lu\n", FSACountFree(fsa));
}

void Test4(fsa_t *fsa)
{
	void *block = NULL;
	
	block = FSAAlloc(fsa);
	FSAAlloc(fsa);
	FSAFree(block);
	printf("%lu ", FSACountFree(fsa));
	block = FSAAlloc(fsa);
	FSAAlloc(fsa);
	FSAFree(block);
	printf("%lu ", FSACountFree(fsa));
	block = FSAAlloc(fsa);
	FSAAlloc(fsa);
	FSAFree(block);
	printf("%lu\n", FSACountFree(fsa));
}

void Test()
{
	void *alloc_ptr = NULL;
	fsa_t *fsa = NULL;
	size_t segment_size = 0;
	
	segment_size = FSASuggestSize(BLOCKS_COUNT, WORD);
	
	alloc_ptr = malloc(segment_size);
	fsa = FSAInit(alloc_ptr, segment_size, WORD);
	TEST(FSACountFree(fsa) == BLOCKS_COUNT, "FSACountFree() after Init");
	
	printf(CYAN);
	Test1(fsa);
	free(alloc_ptr);
	
	alloc_ptr = malloc(segment_size);
	fsa = FSAInit(alloc_ptr, segment_size, WORD);
	Test2(fsa);
	Test3(fsa);
	free(alloc_ptr);
	
	alloc_ptr = malloc(segment_size);
	fsa = FSAInit(alloc_ptr, segment_size, WORD);
	Test4(fsa);
	
	printf(WHITE);
	free(alloc_ptr); alloc_ptr = NULL;
}

void TestUnaligned()
{
	void *alloc_ptr = NULL;
	fsa_t *fsa = NULL;
	size_t segment_size = 0;
	
	segment_size = FSASuggestSize(BLOCKS_COUNT, UNALIGNED);
	
	alloc_ptr = malloc(segment_size);
	fsa = FSAInit(alloc_ptr, segment_size, UNALIGNED);
	TEST(FSACountFree(fsa) == BLOCKS_COUNT, "FSACountFree() after Init");
	
	printf(CYAN);
	Test1(fsa);
	free(alloc_ptr);
	
	alloc_ptr = malloc(segment_size);
	fsa = FSAInit(alloc_ptr, segment_size, UNALIGNED);
	Test2(fsa);
	Test3(fsa);
	free(alloc_ptr);
	
	alloc_ptr = malloc(segment_size);
	fsa = FSAInit(alloc_ptr, segment_size, UNALIGNED);
	Test4(fsa);
	
	printf(WHITE);
	free(alloc_ptr); alloc_ptr = NULL;
}

int main()
{
	Test();
	TestUnaligned();
	
	return 0;
}
