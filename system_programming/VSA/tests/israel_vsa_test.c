/************************************************
*
* File: vsa_test.c
* Ex: varient size allocator
* writer: Israel Drayfus
* Date: 18.12.2019
* Description: run and test functions of varient size allocator.
*
*************************************************/

#include <stdio.h> /*printf()*/
#include <stdlib.h> /*malloc()*/

#include "vsa.h" /*API header*/

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

#define SEGMENT_SIZE 1024
#define WORD 8

void Test1(vsa_t *vsa)
{
	size_t largest_size = 0;
	
	largest_size = VSALargestChunkSize(vsa);
	printf("Largest_size after initialization: %lu\n\n", largest_size);
}

void Test2(vsa_t *vsa)
{
	char *block = NULL;
	
	block = VSAAlloc(vsa, WORD);
	block[0] = 'S';
	block[1] = 'U';
	block[2] = 'C';
	block[3] = 'C';
	block[4] = 'E';
	block[5] = 'S';
	block[6] = 'S';
	block[7] = '\0';
	printf("%s\n", block);
	printf("Largest_size after 8 bytes allocation: %lu\n\n", VSALargestChunkSize(vsa));
	VSAFree(block);
	printf("Largest_size after free: %lu\n\n", VSALargestChunkSize(vsa));
}

void Test3(vsa_t *vsa)
{
	char *block = NULL;
	
	block = VSAAlloc(vsa, WORD);
	VSAAlloc(vsa, WORD);
	block[0] = 'S';
	block[1] = 'U';
	block[2] = 'C';
	block[3] = 'C';
	block[4] = 'E';
	block[5] = 'S';
	block[6] = 'S';
	block[7] = '\0';
	printf("%s\n", block);
	VSAFree(block);
	printf("Largest_size [header,8,header,8,header,944,header]: %lu\n\n",
	       VSALargestChunkSize(vsa)
	      );
}

int main()
{
	void *ptr = malloc(SEGMENT_SIZE);
	vsa_t *vsa = {0};
	
	vsa = VSAInit(ptr, SEGMENT_SIZE);
	
	printf(CYAN);
	Test1(vsa);
	Test2(vsa);
	Test3(vsa);
	
	printf(WHITE);
	
	free(ptr); ptr = NULL;
	return 0;
}




















