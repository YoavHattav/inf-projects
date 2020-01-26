/*********************************/
/*    Data Structures            */
/*    Binary Search Tree         */       
/*    Author: Guy Cohen Zedek    */
/*    Date:   8/01/2020          */
/*                               */
/*********************************/
#include <stdio.h>

#include "../include/hash.h"

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

size_t Hash(const void *data)
{
	return ((*(int *)data)%10);
}

static int Action(void *table_data, void *param)
{
    *(int *)table_data += *(int *)param;
    
    return 0;
}

static int PrintNodes(void *node_data, void *param)
{
    UNUSED(param);
    
    printf("%d\n", *(int *)node_data);
    
    return 0;
}

int IsMatch(void *user_data, void *table_data)
{
	return (*(int *)user_data == *(int *)table_data);
}


static void Test1()
{
	/*int x1 = 1, x2 = 2, x3 = 3, x4 = 4, x5 = 5, x6 = 6;*/
	size_t size = 10;
	int i = 0;

	hash_t *table = HashCreate(size, &Hash, &IsMatch);

	printf("**insert**\n");

	for (i = 0; i < 15; ++i)
	{
		RUN_TEST(0 == HashInsert(table, &i));
	}

	HashDestroy(table);
}
static void Test2()
{
	int x1 = 1, x2 = 2, x3 = 3, x4 = 4, x5 = 5, x6 = 6;
	int one = 1;
	size_t size = 2;
	int i = 0;
	int remove_data = 4;

	hash_t *table = HashCreate(size, &Hash, &IsMatch);

	printf("**size & remove**\n");

	RUN_TEST(0 == HashInsert(table, &x1));
	RUN_TEST(0 == HashInsert(table, &x2));
	RUN_TEST(0 == HashInsert(table, &x3));
	RUN_TEST(0 == HashInsert(table, &x4));
	RUN_TEST(0 == HashInsert(table, &x5));
	RUN_TEST(0 == HashInsert(table, &x6));

	HashForeach(table, &PrintNodes, NULL);

	RUN_TEST(6 == HashSize(table));
	RUN_TEST( 2 == *(int *)(HashFind(table, &x2)));
	RUN_TEST(0 == HashIsEmpty(table));

	HashRemove(table, &remove_data);

	RUN_TEST( NULL == (HashFind(table, &x4)));
	RUN_TEST( 5 == *(int *)(HashFind(table, &x5)));


	RUN_TEST(5 == HashSize(table));
	RUN_TEST(0 == HashIsEmpty(table));

	HashDestroy(table);

}

int main()
{
	Test1();
	Test2();
	return 0;
}
