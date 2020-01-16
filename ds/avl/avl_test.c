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

static int Compare(const void *user_data, const void *data)
{
    
    return ((*(int *)(user_data)) - (*(int *)(data)));
}

static int AddNum(void *node_data, void *num)
{
    *(int *)node_data += *(int *)num;
    
    return 0;
}

void TestCreate()
{
	avl_t *tree = AVLCreate(&Compare);
    
    printf("Create:\n");
    RUN_TEST(0 == AVLSize(tree));
    RUN_TEST(1 == AVLIsEmpty(tree));
    
    AVLDestroy(tree); tree = NULL;
}

static void TestInsert()
{
    avl_t *tree = AVLCreate(&Compare);
    int x1 = 1, x2 = 2, x3 = 3, x4 = 4, x5 = 5, x6 = 6, x7 = 7; 
    
    printf("\nInsert:\n");
    RUN_TEST(0 == AVLSize(tree));
    RUN_TEST(1 == AVLIsEmpty(tree));
    
    RUN_TEST(0 == AVLInsert(tree, &x4));
    RUN_TEST(0 == AVLInsert(tree, &x5));
    RUN_TEST(0 == AVLInsert(tree, &x3));
    RUN_TEST(0 == AVLInsert(tree, &x1));
    RUN_TEST(0 == AVLInsert(tree, &x2));
    RUN_TEST(0 == AVLInsert(tree, &x6));
    RUN_TEST(0 == AVLInsert(tree, &x7));
    
    RUN_TEST(7 == AVLSize(tree));
    
    AVLDestroy(tree); tree = NULL; 
}

int main()
{
	TestCreate();
	return 0;
}
