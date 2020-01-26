#include <stdio.h>

#include "../include/avl.h"

#define GREEN "\033[;032m"
#define RED   "\033[;031m"
#define RESET "\033[0m"
#define UNUSED(x) (void)(x)
#define RUN_TEST(test)\
{\
  if(test)\
  {\
    printf(GREEN);\
    printf("SUCCESS\n");\
    printf(RESET);\
  }\
  else\
  {\
    printf(RED);\
    printf("FAIL \n");\
    printf(RESET);\
  }\
}

int UserCmp(const void *data1, const void *data2, void *param)
{
	UNUSED(param);

	return ((void *)data1 - (void *)data2);
}

static void TestPQCreate()
{
	PQCreate(&UserCmp, NULL);
}

int main()
{
	TestPQCreate();
	return 0;
}
