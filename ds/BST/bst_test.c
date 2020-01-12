#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <time.h>

#include "../include/bst.h"

#define END_DATA 0xDEADBEEF

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

enum Bool {FALSE, TRUE};
enum Side {LEFT, RIGHT};
enum State {SUCC, FAIL};

typedef struct BSTNode bst_node_t;

struct BSTNode
{
	void *data;
	struct BSTNode *child[2];
	struct BSTNode *parent;
};

struct BSTree
{
	bst_node_t dummy;
	compare_func_t cmp;
	void *param;
};

int CompareFunc(const void *data1, const void *data2, void *param)
{
	UNUSED(param);

	return (data1 > data2);
}

int ActionFunc(void *data1, void *data2)
{
	assert(NULL != data1);
	assert(NULL != data2);

	*(int *)data1 += *(int *)data2;

	return 0;  
}

int RandomNumGenerator()
{
	srand(time(0));
	
	return (rand()%32);
}

static void TESTBSTCreate()
{
	bst_t *tree = NULL;

	printf("create\n");
	RUN_TEST(NULL != (tree= BSTCreate(&CompareFunc, NULL)));

	free(tree); tree = NULL;
}

static void TESTBSTDestroy()
{
	bst_t *tree = NULL;

	printf("destroy\n");
	RUN_TEST(NULL != (tree= BSTCreate(&CompareFunc, NULL)));
	BSTDestroy(tree);
	
}
static void TESTBSTInsert()
{
	bst_t *tree = NULL;
	int x1 = 1, x2 = 2, x3 = 3; 
	printf("insert\n");
	RUN_TEST(NULL != (tree= BSTCreate(&CompareFunc, NULL)));
	RUN_TEST(1 != BSTInsert(tree, &x1));
	RUN_TEST(1 != BSTInsert(tree, &x2));
	RUN_TEST(1 != BSTInsert(tree, &x3));

	RUN_TEST(3 == BSTSize(tree));

	BSTDestroy(tree);
}

static void TESTBSTRemove()
{
	bst_t *tree = NULL;
	bst_itr_t itr1 = NULL;
	bst_itr_t itr2 = NULL;


	int x1 = 1, x2 = 2, x3 = 3, x4 = 4, x5 = 5; 
	printf("insert, remove, next, begin, isempty, size\n");
	RUN_TEST(NULL != (tree= BSTCreate(&CompareFunc, NULL)));
	RUN_TEST(1 != BSTInsert(tree, &x1));
	RUN_TEST(1 != BSTInsert(tree, &x5));
	RUN_TEST(1 != BSTInsert(tree, &x3));
	RUN_TEST(1 != BSTInsert(tree, &x4));

	itr1 = BSTBegin(tree);
	itr2 = BSTNext(itr1);

	BSTRemove(itr1);

	RUN_TEST(3 == BSTSize(tree));

	BSTDestroy(tree);	
}

static void TESTBSTFind()
{
	bst_t *tree = NULL;
	bst_itr_t itr1 = NULL;
	bst_itr_t itr2 = NULL;


	int x1 = 1, x2 = 2, x3 = 3, x4 = 4, x5 = 5; 
	printf("find, getdata, prev, is_same_itr\n");
	RUN_TEST(NULL != (tree= BSTCreate(&CompareFunc, NULL)));
	RUN_TEST(1 != BSTInsert(tree, &x1));
	RUN_TEST(1 != BSTInsert(tree, &x5));
	RUN_TEST(1 != BSTInsert(tree, &x3));

	itr1 = BSTFind(tree, &x5);
	RUN_TEST(5 == *(int *)BSTGetData(itr1));
	itr2 = BSTBegin(tree);
	RUN_TEST(BSTNext(itr2) == BSTPrev(itr1));
	RUN_TEST(0 == BSTIsSameItr(itr1, itr2));
	
	printf("itr 1 data : %d\n", *(int *)itr1->data);
	printf("itr 2 data : %d\n", *(int *)itr2->data);

	BSTDestroy(tree);	
}

static void TESTBSTForeach()
{

}

static void TESTBSTEnd()
{

}

static void TESTBSTPrev()
{

}

static void TESTBSTIsSameItr()
{

}

int main()
{
	
	TESTBSTCreate();
	TESTBSTDestroy();
	TESTBSTInsert();
	TESTBSTRemove();
	TESTBSTFind();
	TESTBSTForeach();
	TESTBSTEnd();
	TESTBSTPrev();
	TESTBSTIsSameItr();
	
	return 0;
}