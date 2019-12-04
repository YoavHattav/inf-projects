#include <stdio.h>

#include "linkedlist.h"

#define GREEN "\033[0;32m"
#define RED "\033[1;31m"
#define WHITE "\033[0m"

#define TEST(Test, msg) if (Test)\
                        {\
                            printf(GREEN);\
                            printf("SUCCESS\n");\
                        }\
                        else\
                        {\
                            printf(RED);\
                            printf("FAIL-%s\n", msg);\
                        }\
                        printf(WHITE);

static int TestInsertDestroySize()
{
	
	float x1 = 1, x2 = 2;
	float x3 = 3, x4 = 4, x5 = 23;
    

    node_t *mytest1 = NULL;
    node_t *mytest2 = NULL;
    node_t *mytest3 = NULL;
    node_t *mytest4 = NULL;
    node_t *mytest2_3 = NULL;


/*
SLLCreateNode
SLLDestroy
Insert
SLLInsertAfter
SLLRemove

SLLRemoveAfter
SLLGetNode
SLLForEach
SLLSize
SLLFlip
SLLHasLoop
SLLFindIntersection
*/
    mytest1 = SLLCreateNode(NULL, &x1);
    mytest2 = SLLCreateNode(NULL, &x2);
    mytest3 = SLLCreateNode(NULL, &x3);
    mytest4 = SLLCreateNode(NULL, &x4);
    mytest2_3 = SLLCreateNode(NULL, &x5);

    TEST(0 == SLLInsert(mytest3, mytest4),"insert func");

   

    printf("%f\n", *(float *)(mytest1->data));
    printf("%f\n", *(float *)(mytest2->data));
    printf("%f\n", *(float *)(mytest3->data));
    printf("%f\n", *(float *)(mytest4->data));

   /* TEST(0 == SLLInsertAfter(mytest2_3, mytest2),"insert after func");*/

    printf("%lu\n", SLLSize(mytest4));
    printf("%lu\n", SLLSize(mytest3));

    TEST(0 == SLLInsertAfter(mytest2, mytest4),"insert func");

    printf("%lu\n", SLLSize(mytest4));





/*

    TEST((sizeof(*mytest1) == 32 ), "stack size diff then expectation");
    TEST((mytest1->capacity == 5 ), "stack size diff then expectation");

    Insert(mytest1);
    VectorPopBack(mytest1);
    VectorPopBack(mytest1);

    for (; i < 10; ++i)
	{
		
		TEST((VectorSize(mytest1) == i+1), "Wrong # of items");	
	}

	printf("capacity is: %lu\n", VectorCapacity(mytest1));
	printf("size is: %lu\n", VectorSize(mytest1));

	TEST(10 == VectorCapacity(mytest1),"didnt double the capacity");
	TEST(10 == VectorSize(mytest1),"didnt double the size");


	TEST(0 == VectorPushBack(mytest1, &i),"could not push");

	TEST(20 == VectorCapacity(mytest1),"didnt double the capacity");
	TEST(11 == VectorSize(mytest1),"didnt double the size");

	printf("capacity is: %lu\n", VectorCapacity(mytest1));
	printf("size is: %lu\n", VectorSize(mytest1));

	for (i = 0; i < 6; ++i)
	{
		VectorPopBack(mytest1);
	}

	TEST(10 == VectorCapacity(mytest1),"didnt double the capacity");
	TEST(5 == VectorSize(mytest1),"didnt double the size");

	printf("capacity is: %lu\n", VectorCapacity(mytest1));
	printf("size is: %lu\n", VectorSize(mytest1));


	VectorReserve(mytest1, 40);
	TEST(40 == VectorCapacity(mytest1),"didnt Reserve the right capacity");
	VectorPopBack(mytest1);
	TEST(20 == VectorCapacity(mytest1),"didnt cut the capacity in half");


	
	TEST(0 == *(int *)(VectorGetItemAddress(mytest1, 1)), "0?");
	TEST(1 == *(int *)(VectorGetItemAddress(mytest1, 2)), "0?");
	TEST(2 == *(int *)(VectorGetItemAddress(mytest1, 3)), "0?");
	TEST(3 == *(int *)(VectorGetItemAddress(mytest1, 4)), "0?");

*/
    SLLDestroy(mytest1);
    /*SLLDestroy(mytest2);*/
    SLLDestroy(mytest4);
    SLLDestroy(mytest2_3);
    
	return 0;
}

int main()
{
	TestInsertDestroySize();

	return 0;
}