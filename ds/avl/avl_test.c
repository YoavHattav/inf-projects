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
    
    if (*(int *)user_data > *(int *)data)
    {
    	return 1;
    }
    if (*(int *)user_data == *(int *)data)
    {
    	return 0;
    }
    else 
    {
    	return 1;
    }
}

static int AddNum(void *node_data, void *num)
{
    *(int *)node_data += *(int *)num;
    
    return 0;
}

static int PrintTree(void *node_data, void *param)
{
    UNUSED(param);
    
    printf("%d\n", *(int *)node_data);
    
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

static void TestFind()
{
	avl_t *tree = AVLCreate(&Compare);
    int x1 = 1, x2 = 2, x3 = 3, x4 = 4, x5 = 5, x6 = 6, x7 = 7, x10 = 10; 
    
    printf("\nFind , ForEach:\n");
    RUN_TEST(0 == AVLSize(tree));
    RUN_TEST(1 == AVLIsEmpty(tree));
    
    RUN_TEST(0 == AVLInsert(tree, &x1));
    RUN_TEST(0 == AVLInsert(tree, &x2));
    RUN_TEST(0 == AVLInsert(tree, &x4));
    RUN_TEST(0 == AVLInsert(tree, &x6));
    RUN_TEST(0 == AVLInsert(tree, &x7));
    
    RUN_TEST(5 == AVLSize(tree));

    printf("Before Add Number:\n");

    RUN_TEST(0 == AVLForeach(tree, &PrintTree, NULL));
    
    RUN_TEST(0 == AVLForeach(tree, &AddNum, &x3));

    printf("After Add Number:\n");
    
    RUN_TEST(0 == AVLForeach(tree, &PrintTree, NULL));

    RUN_TEST(10 == *(int *)AVLFind(tree, &x10));
    printf("%d\n", *(int *)AVLFind(tree, &x7));

    AVLDestroy(tree); tree = NULL;	
}
int main()
{
	TestCreate();
	TestInsert();
	TestFind();

	return 0;
}
