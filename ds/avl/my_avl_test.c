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

/*static int Compare(const void *user_data, const void *data)
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
	TestFind();
	TestRemove();
	TestRemoveRoot();
	TestSpecialPlace();
	TestDanielStupidTest();
	TestHeight();

	return 0;
}
*/


struct Person
{
    char name[20];
    unsigned int age;
    char city[20];    
};

static int Compare(const void *user_data, const void *tree_data)
{
    return (*(int *)user_data - *(int *)tree_data);
}

static int CompareAge(const void *user_data, const void *tree_data)
{
    return (((struct Person *)user_data)->age - ((struct Person *)tree_data)->age);
}

static int PrintNode(void *tree_data, void *param)
{
    printf("%d\n", *(int *)tree_data);
    
    UNUSED(param);
    
    return 0;
}

static int PrintName(void *tree_data, void *param)
{
    printf("%s\n", ((struct Person *)tree_data)->name);
    
    UNUSED(param);
    
    return 0;
}

static void TestAVLCreate()
{
    avl_t *tree = AVLCreate(&Compare);
    
    printf("Create:\n");
    
    RUN_TEST(0 == AVLSize(tree));
    RUN_TEST(1 == AVLIsEmpty(tree));
    RUN_TEST(0 == AVLGetHeight(tree));
    
    AVLDestroy(tree);
}

static void TestAVLInsert()
{
    avl_t *tree = AVLCreate(&Compare);
    int x1 = 18, x2 = 34, x3 = 2, x4 = 11, x5 = 4;
    
    printf("\nInsert:\n");
    
    RUN_TEST(0 == AVLSize(tree));
    RUN_TEST(1 == AVLIsEmpty(tree));
    RUN_TEST(0 == AVLGetHeight(tree));
    
    RUN_TEST(0 == AVLInsert(tree, &x1));
    RUN_TEST(0 == AVLInsert(tree, &x2));
    RUN_TEST(0 == AVLInsert(tree, &x3));
    RUN_TEST(0 == AVLInsert(tree, &x4));
    
    RUN_TEST(4 == AVLSize(tree));
    RUN_TEST(2 == AVLGetHeight(tree));
    
    RUN_TEST(0 == AVLForeach(tree, &PrintNode, NULL));
    RUN_TEST(x2 == *(int *)AVLFind(tree, &x2));
    RUN_TEST(NULL == AVLFind(tree, &x5));
    
    AVLDestroy(tree);
}

static void TestAVLFind()
{
    avl_t *tree = AVLCreate(&CompareAge);
    struct Person p1 = {"Yonatan", 28, "Jerusalem"},
                  p2 = {"Guy", 10, "Tel-Aviv"},
                  p3 = {"Raz", 16, "Netanya"},
                  p4 = {"Shye", 26, "Jerusalem"},
                  p5 = {"Israel", 14, "Jerusalem"},
                  p6 = {"Yoav", 32, "Tel-Aviv"},
                  p7 = {"Eliya", 19, "Petah-Tikva"},
                  p8 = {"Daniel", 45, "Petah-Tikva"},
                  p9 = {"Ben", 40, "Rehovot"},
                  p10 = {"Itay", 22, "Tel-Aviv"};
    
    printf("\nFind:\n");
    
    RUN_TEST(0 == AVLSize(tree));
    RUN_TEST(1 == AVLIsEmpty(tree));
    RUN_TEST(0 == AVLGetHeight(tree));
    
    RUN_TEST(0 == AVLInsert(tree, &p1));
    RUN_TEST(0 == AVLInsert(tree, &p2));
    RUN_TEST(0 == AVLInsert(tree, &p3));
    RUN_TEST(0 == AVLInsert(tree, &p4));
    RUN_TEST(0 == AVLInsert(tree, &p5));
    RUN_TEST(0 == AVLInsert(tree, &p6));
    RUN_TEST(0 == AVLInsert(tree, &p7));
    RUN_TEST(0 == AVLInsert(tree, &p8));
    RUN_TEST(0 == AVLInsert(tree, &p9));
    RUN_TEST(0 == AVLInsert(tree, &p10));
    RUN_TEST(3 == AVLGetHeight(tree));
    RUN_TEST(10 == AVLSize(tree));
    
    RUN_TEST(0 == AVLForeach(tree, &PrintName, NULL));
    
    PrintName(AVLFind(tree, &p6), NULL);
    
    AVLDestroy(tree);
}

static void TestAVLRemove()
{
    avl_t *tree = AVLCreate(&Compare);
    int x1 = 7, x2 = 2, x3 = 13, x4 = 9, x5 = 20, x6 = 5, x7 = 1, x8 = 8;
    
    printf("\nRemove:\n");
    
    RUN_TEST(0 == AVLSize(tree));
    RUN_TEST(1 == AVLIsEmpty(tree));
    RUN_TEST(0 == AVLGetHeight(tree));
    
    RUN_TEST(0 == AVLInsert(tree, &x1));
    RUN_TEST(0 == AVLInsert(tree, &x2));
    RUN_TEST(0 == AVLInsert(tree, &x3));
    RUN_TEST(0 == AVLInsert(tree, &x4));
    RUN_TEST(0 == AVLInsert(tree, &x5));
    RUN_TEST(0 == AVLInsert(tree, &x6));
    RUN_TEST(0 == AVLInsert(tree, &x7));
    RUN_TEST(0 == AVLInsert(tree, &x8));
    
    RUN_TEST(8 == AVLSize(tree));
    RUN_TEST(3 == AVLGetHeight(tree));
    
    RUN_TEST(0 == AVLForeach(tree, &PrintNode, NULL));
    
    printf("After remove 5:\n");
    AVLRemove(tree, &x6);
    RUN_TEST(7 == AVLSize(tree));
    RUN_TEST(0 == AVLForeach(tree, &PrintNode, NULL));
    RUN_TEST(3 == AVLGetHeight(tree));
    
    printf("After remove 7:\n");
    AVLRemove(tree, &x1);
    RUN_TEST(6 == AVLSize(tree));
    RUN_TEST(0 == AVLForeach(tree, &PrintNode, NULL));
    RUN_TEST(2 == AVLGetHeight(tree));
    printf("%ld\n", AVLGetHeight(tree));
    
    printf("After remove 13:\n");
    AVLRemove(tree, &x3);
    RUN_TEST(5 == AVLSize(tree));
    RUN_TEST(0 == AVLForeach(tree, &PrintNode, NULL));
    RUN_TEST(2 == AVLGetHeight(tree));
    
    printf("After remove 20:\n");
    AVLRemove(tree, &x5);
    RUN_TEST(4 == AVLSize(tree));
    RUN_TEST(0 == AVLForeach(tree, &PrintNode, NULL));
    RUN_TEST(2 == AVLGetHeight(tree));
    
    printf("After remove 9:\n");
    AVLRemove(tree, &x4);
    RUN_TEST(3 == AVLSize(tree));
    RUN_TEST(0 == AVLForeach(tree, &PrintNode, NULL));
    RUN_TEST(1 == AVLGetHeight(tree));
    
    AVLDestroy(tree);
}

static void TestAVLBalance()
{
    avl_t *tree = AVLCreate(&Compare);
    int x1 = 7, x2 = 2, x3 = 13, x4 = 1;
    
    printf("\nBalance:\n");
    
    RUN_TEST(0 == AVLSize(tree));
    RUN_TEST(1 == AVLIsEmpty(tree));
    RUN_TEST(0 == AVLGetHeight(tree));
    
    RUN_TEST(0 == AVLInsert(tree, &x2));
    RUN_TEST(0 == AVLInsert(tree, &x1));
    RUN_TEST(0 == AVLInsert(tree, &x3));
    
    RUN_TEST(1 == AVLGetHeight(tree));
    
    RUN_TEST(0 == AVLInsert(tree, &x4));
    
    RUN_TEST(2 == AVLGetHeight(tree));
    
    AVLRemove(tree, &x3);
    
    RUN_TEST(1 == AVLGetHeight(tree));
    
    AVLDestroy(tree);
}

int main()
{
    TestAVLCreate();
    TestAVLInsert();
    TestAVLFind();
    TestAVLRemove();
    TestAVLBalance();
    
    return 0;
}
