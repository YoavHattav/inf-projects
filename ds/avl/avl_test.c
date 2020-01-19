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
    	return -1;
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

    printf("\nBefore Add Number:\n");

    RUN_TEST(0 == AVLForeach(tree, &PrintTree, NULL));
    
    RUN_TEST(0 == AVLForeach(tree, &AddNum, &x3));

    printf("\nAfter Add Number:\n");
    
    RUN_TEST(0 == AVLForeach(tree, &PrintTree, NULL));

    RUN_TEST(10 == *(int *)AVLFind(tree, &x10));

    AVLDestroy(tree); tree = NULL;	
}

static void TestRemove()
{
	avl_t *tree = AVLCreate(&Compare);
    int x1 = 1, x2 = 2, x3 = 3, x4 = 4, x5 = 5, x6 = 6, x7 = 7; 
    
    printf("\nRemove:\n");
    RUN_TEST(0 == AVLSize(tree));
    RUN_TEST(1 == AVLIsEmpty(tree));
    
    AVLInsert(tree, &x4);
    AVLInsert(tree, &x5);
    AVLInsert(tree, &x3);

    AVLRemove(tree, &x5);

	RUN_TEST(2 == AVLSize(tree));
    RUN_TEST(0 == AVLIsEmpty(tree));

    AVLRemove(tree, &x3);
	
	RUN_TEST(1 == AVLSize(tree));
    RUN_TEST(0 == AVLIsEmpty(tree));
    
    AVLDestroy(tree); tree = NULL; 
}

static void TestRemoveRoot()
{
	avl_t *tree = AVLCreate(&Compare);
    int x1 = 1, x2 = 2, x3 = 3, x4 = 4, x5 = 5, x6 = 6, x7 = 7; 
    
    printf("\nRemove-Root:\n");
    
    AVLInsert(tree, &x4);

    AVLRemove(tree, &x4);

	RUN_TEST(0 == AVLSize(tree));
    RUN_TEST(1 == AVLIsEmpty(tree));

    AVLDestroy(tree); tree = NULL; 
}

static void TestSpecialPlace()
{
	avl_t *tree = AVLCreate(&Compare);
    int x8 = 8, x9 = 9, x13 = 13, x20 = 20;
    int x1 = 1, x2 = 2, x5 = 5, x7 = 7; 
 
    
    printf("\nTestSpecialPlace:\n");
    
    AVLInsert(tree, &x7);
    AVLInsert(tree, &x2);
    AVLInsert(tree, &x13);
    AVLInsert(tree, &x1);
    AVLInsert(tree, &x5);
    AVLInsert(tree, &x9);
    AVLInsert(tree, &x8);
    AVLInsert(tree, &x20);
    
    RUN_TEST(8 == AVLSize(tree));
    RUN_TEST(0 == AVLIsEmpty(tree));

    AVLRemove(tree, &x7);

	RUN_TEST(7 == AVLSize(tree));
	printf("%lu\n", AVLSize(tree));
    RUN_TEST(0 == AVLIsEmpty(tree));

    AVLDestroy(tree); tree = NULL; 
}

static void TestDanielStupidTest()
{
	avl_t *tree = AVLCreate(&Compare);
    int x5 = 150, x6 = 25, x7 = 80, x8 = 70, x9 = 60, x10 = 65, x11 = 140, x12 = 135 , x13= 138;
    int x1 = 100, x2 = 50, x3 = 200, x4 = 300; 
 
    
    printf("\nyyiuyy:\n");
    
    AVLInsert(tree, &x1);
    AVLInsert(tree, &x2);
    AVLInsert(tree, &x3);
    AVLInsert(tree, &x4);
    AVLInsert(tree, &x5);
    AVLInsert(tree, &x6);
    AVLInsert(tree, &x7);
    AVLInsert(tree, &x8);
    AVLInsert(tree, &x9);
    AVLInsert(tree, &x10);
    AVLInsert(tree, &x11);
    AVLInsert(tree, &x12);
    AVLInsert(tree, &x13);
        
    RUN_TEST(13 == AVLSize(tree));
    RUN_TEST(0 == AVLIsEmpty(tree));

    AVLRemove(tree, &x13);

	RUN_TEST(12 == AVLSize(tree));
    RUN_TEST(0 == AVLIsEmpty(tree));

    AVLDestroy(tree); tree = NULL; 
}

static void TestHeight()
{
	avl_t *tree = AVLCreate(&Compare);
    int x5 = 150, x6 = 25, x7 = 80, x8 = 70, x9 = 60, x10 = 65, x11 = 140, x12 = 135 , x13= 138;
    int x1 = 100, x2 = 50, x3 = 200, x4 = 300; 
 
    
    printf("\nheight:\n");
    
    AVLInsert(tree, &x1);
    AVLInsert(tree, &x2);
    AVLInsert(tree, &x3);
    AVLInsert(tree, &x4);
    AVLInsert(tree, &x5);
    AVLInsert(tree, &x6);
    AVLInsert(tree, &x7);
    AVLInsert(tree, &x8);
    AVLInsert(tree, &x9);
    AVLInsert(tree, &x10);
    AVLInsert(tree, &x11);
    AVLInsert(tree, &x12);
    AVLInsert(tree, &x13);
        
    RUN_TEST(13 == AVLSize(tree));
    RUN_TEST(0 == AVLIsEmpty(tree));

    AVLRemove(tree, &x13);

	RUN_TEST(12 == AVLSize(tree));
    RUN_TEST(0 == AVLIsEmpty(tree));

    printf("%lu\n", AVLGetHeight(tree));


    AVLDestroy(tree); tree = NULL; 
}

int main()
{
	TestCreate();
	TestInsert();
	TestFind();
	TestRemove();
	TestRemoveRoot();
	TestSpecialPlace();
	TestDanielStupidTest();
	TestHeight();


	return 0;
}
