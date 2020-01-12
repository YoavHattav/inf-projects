/************************************************
*
* File: bst_test.c
* Ex: Binary Search Tree
* writer: Israel Drayfus
* Description: run and test functions of Binary Search Tree.
*
*************************************************/

#include <stdio.h> /*printf()*/

#include "../include/bst.h"

#define RED "\033[31m"
#define GREEN "\033[32m"
#define WHITE "\033[0m"

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


int Compare(const void *data1, const void *data2, void *param)
{
	UNUSED(param);
	
	return *(int *)data1 > *(int *)data2;
}

int Compare2(void *data1, void *data2, void *param)
{
	return *(int *)data1 * *(int *)param - *(int *)data2 * *(int *)param;
}

int AddOne(void *d1, void *param)
{
	UNUSED(param);
	
	++*(int *)d1;
	
	return 0;
}

void InsertAll(bst_t *bst, int *a, size_t size)
{
	size_t i = 0;
	
	for (; i < size; ++i)
	{
		BSTInsert(bst, (void *)&a[i]);
	}
}

void FindAll(bst_t *bst, int *a, size_t size)
{
	size_t i = 0;
	bst_itr_t itr = BSTBegin(bst);
	
	printf("\n");
	for (; i < size; ++i)
	{
		itr = BSTFind(bst, (void *)&a[i]);
		TEST(&a[i] == BSTGetData(itr), "Find failed");
	}
	printf("\n");
}

void TestBSTNext(bst_t *bst)
{
	bst_itr_t itr = BSTBegin(bst);
	bst_itr_t end = BSTEnd(bst);
	
	while (itr != end)
	{
		printf("%d ", *(int *)BSTGetData(itr));
		itr = BSTNext(itr);
	}
	printf("\n");
}

void TestBSTPrev(bst_t *bst)
{
	bst_itr_t itr = BSTEnd(bst);
	bst_itr_t begin = BSTBegin(bst);
	
	itr = BSTPrev(itr);
	while (itr != begin)
	{
		printf("%d ", *(int *)BSTGetData(itr));
		itr = BSTPrev(itr);
	}
	printf("%d\n", *(int *)BSTGetData(itr));
}

void TestForEach(bst_t *bst)
{
	printf("Before ForEach: ");
	TestBSTNext(bst);
	BSTForeach(BSTBegin(bst), BSTEnd(bst), AddOne, NULL);
	printf("After ForEach: ");
	TestBSTNext(bst);
}

void Test1(bst_t *bst)
{
	int x = 0;
	
	TEST(BSTSize(bst) == 0, "Size, empty tree");
	TEST(BSTIsEmpty(bst) == 1, "IsEmpty, empty tree");
	TEST(BSTIsSameItr(BSTEnd(bst), BSTBegin(bst)), " IsSame & End & Begin,\
 empty tree");
	TEST(BSTFind(bst, &x) == NULL, "Find, empty tree");
	printf("\n");
}

void Test2(bst_t *bst)
{
	bst_itr_t itr = NULL;
	int x = 0;
	
	BSTInsert(bst, &x);
	TEST(BSTSize(bst) == 1, "Size, one item");
	TEST(BSTIsEmpty(bst) == 0, "IsEmpty, one item");
	TEST(&x == BSTGetData(BSTBegin(bst)), "GetData & Begin, one item");
	itr = BSTFind(bst, &x);
	TEST(BSTIsSameItr(itr, BSTBegin(bst)), "Find, one item");
	BSTForeach(itr, BSTEnd(bst), AddOne, NULL);
	TEST((x == 1), "ForEach, one item");
	TEST(BSTNext(itr) == BSTEnd(bst), "Next, one item");
	TEST(BSTPrev(itr) == BSTEnd(bst), "Prev, one item");
	BSTRemove(itr);
	TEST(BSTIsEmpty(bst) == 1, "Remove, one item");
	
	printf("\n");
}

void Tests_1(bst_t *bst)
{
	int test_lst[3] = {0,1,2};
	
	InsertAll(bst, test_lst, sizeof(test_lst) / sizeof(int));
	TEST(BSTSize(bst) == 3, "Tests_1: Size, test3");
	TEST(&test_lst[0] == BSTGetData(BSTBegin(bst)), "Tests_1: Begin, test3");
	TestBSTNext(bst);
	TestBSTPrev(bst);
	TestForEach(bst);
	
	printf("\n");
}

void Tests_2(bst_t *bst)
{
	int test_lst[3] = {2,1,0};
	
	InsertAll(bst, test_lst, sizeof(test_lst) / sizeof(int));
	TEST(BSTSize(bst) == 3, "Tests_2: Size, test3");
	TEST(&test_lst[2] == BSTGetData(BSTBegin(bst)), "Tests_2: Begin, test3");
	TestBSTNext(bst);
	TestBSTPrev(bst);
	TestForEach(bst);
	
	printf("\n");
}

void Tests_3(bst_t *bst)
{
	int test_lst[3] = {1,0,2};
	
	InsertAll(bst, test_lst, sizeof(test_lst) / sizeof(int));
	TEST(BSTSize(bst) == 3, "Tests_2: Size, test3");
	TEST(&test_lst[1] == BSTGetData(BSTBegin(bst)), "Tests_2: Begin, test3");
	TestBSTNext(bst);
	TestBSTPrev(bst);
	TestForEach(bst);
	
	printf("\n");
}

void Tests_4(bst_t *bst)
{
	int test_lst[3] = {2,0,1};
	
	InsertAll(bst, test_lst, sizeof(test_lst) / sizeof(int));
	TEST(BSTSize(bst) == 3, "Tests_2: Size, test3");
	TEST(&test_lst[1] == BSTGetData(BSTBegin(bst)), "Tests_2: Begin, test3");
	TestBSTNext(bst);
	TestBSTPrev(bst);
	TestForEach(bst);
	
	printf("\n");
}

void Tests_5(bst_t *bst)
{
	int test_lst[3] = {0,2,1};
	
	InsertAll(bst, test_lst, sizeof(test_lst) / sizeof(int));
	TEST(BSTSize(bst) == 3, "Tests_2: Size, test3");
	TEST(&test_lst[0] == BSTGetData(BSTBegin(bst)), "Tests_2: Begin, test3");
	TestBSTNext(bst);
	TestBSTPrev(bst);
	TestForEach(bst);
	
	printf("\n");
}

void Tests_6(bst_t *bst)
{
	int test_lst[11] = {11,2,1,10,7,4,3,20,15,17,12};
	
	InsertAll(bst, test_lst, sizeof(test_lst) / sizeof(int));
	TEST(BSTSize(bst) == 11, "Tests_2: Size, test3");
	TEST(&test_lst[2] == BSTGetData(BSTBegin(bst)), "Tests_2: Begin, test3");
	TestBSTNext(bst);
	TestBSTPrev(bst);
	TestForEach(bst);
	
	printf("\n");
}

void Tests()
{
	bst_t *bst = BSTCreate(Compare, NULL);
	Tests_1(bst);
	BSTDestroy(bst);
	
	bst = BSTCreate(Compare, NULL);
	Tests_2(bst);
	BSTDestroy(bst);
	
	bst = BSTCreate(Compare, NULL);
	Tests_3(bst);
	BSTDestroy(bst);
	
	bst = BSTCreate(Compare, NULL);
	Tests_4(bst);
	BSTDestroy(bst);
	
	bst = BSTCreate(Compare, NULL);
	Tests_5(bst);
	BSTDestroy(bst);
	
	bst = BSTCreate(Compare, NULL);
	Tests_6(bst);
	BSTDestroy(bst);
}

int main()
{
	bst_t *bst = BSTCreate(Compare, NULL);
	int x = 0;
	
	Test1(bst);
	BSTDestroy(bst);
	
	bst = BSTCreate(Compare, NULL);
	BSTInsert(bst, &x);
	BSTDestroy(bst);
	
	bst = BSTCreate(Compare, NULL);
	Test2(bst);
	BSTDestroy(bst);
	
	Tests();
	
	return 0;
}























