#include <stdio.h>

#include "vector.h"

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
struct Vector{

	void* start;
	size_t capacity;
	size_t size;
	size_t element_size;
};


static int TestAllFunctions()
{
	
	size_t capacity = 5;
    size_t element_size = 4;
    size_t i = 0;

    vector_t *mytest1 = NULL;
    mytest1 = VectorCreate(element_size, capacity);

    TEST((sizeof(*mytest1) == 32 ), "stack size diff then expectation");
    TEST((mytest1->capacity == 5 ), "stack size diff then expectation");

    VectorPopBack(mytest1);
    VectorPopBack(mytest1);
    VectorPopBack(mytest1);

    for (; i < 10; ++i)
	{
		TEST(0 == VectorPushBack(mytest1, &i),"could not push");
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


    VectorDestroy(mytest1);


    mytest1 = VectorCreate(0, 5);

    mytest1 = VectorCreate(5, 0);
    
    


	return 0;
}

int main()
{
	TestAllFunctions();

	return 0;
}