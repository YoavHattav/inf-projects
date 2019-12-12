#include <stdio.h> /* printf */

#include "dllist.h"

#define UNUSED(x) (void)(x)
#define GREEN "\033[;032m"
#define RED   "\033[;031m"
#define RESET "\033[0m"
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

int PrintNode(void *data, void *additional) 
{    
    UNUSED(additional);
    
    printf("data: %d\n", *(int *)data);
    
    return 0;
}

int AddToNode(void *data, void *additional) 
{    
    *(int *)data += *(int *)additional;

    return 0;
}

int IsMatch(void *data, void *additional)
{    
    return (*(int*)data == *(int*)additional);
}

static void TestDLinkedList()
{
    int x1 = 1, x2 = 2, x3 = 3, x4 = 4, x5 = 5;
    int *data1 = NULL;
    dll_t  *dll1 = NULL, *dll2 = NULL, *dll3 = NULL, *dll4 =NULL;
    iterator_t T1, T2, T3;
    
    printf("Linked List 1:\n");
    dll1 = DLLCreate();
    T1 = DLLEnd(dll1);
    T1 = DLLInsert(dll1, T1, &x1);
    RUN_TEST(1 == DLLSize(dll1));
    T1 = DLLInsert(dll1, T1, &x2);
    RUN_TEST(2 == DLLSize(dll1));
    DLLRemove(T1);
    RUN_TEST(1 == DLLSize(dll1));
    RUN_TEST(0 == DLLIsEmpty(dll1));

    DLLDestroy(dll1);

    printf("Linked List 2:\n");
    dll1 = DLLCreate();
    dll2 = DLLCreate();
    T1 = DLLEnd(dll1);
    T2 = DLLEnd(dll2);
    T1 = DLLInsert(dll1, T1, &x1);
    T2 = DLLInsert(dll2, T2, &x2);
    RUN_TEST(1 == DLLSize(dll1));
    RUN_TEST(1 == DLLSize(dll2));
    T1 = DLLRemove(T1);
    RUN_TEST(0 == DLLSize(dll1));
    T1 = DLLInsert(dll1, T1, &x2);
    T1 = DLLInsert(dll1, T1, &x3);
    T1 = DLLInsert(dll1, T1, &x4);
    T1 = DLLInsert(dll1, T1, &x5);
    T3 = DLLEnd(dll1);
    T2 = DLLSplice(T1, T3, T2);
    RUN_TEST(5 == DLLSize(dll2));

    DLLDestroy(dll1);
    DLLDestroy(dll2);
    
    printf("Linked List 3:\n");
    dll1 = DLLCreate();
    dll2 = DLLCreate();
    T1 = DLLEnd(dll1);
    T2 = DLLEnd(dll2);
    T1 = DLLInsert(dll1, T1, &x5);
    T2 = DLLInsert(dll2, T2, &x2);
    RUN_TEST(1 == DLLSize(dll1));
    RUN_TEST(1 == DLLSize(dll2));
    RUN_TEST(5 == *(int *)(DLLGetData(T1)));
    T2 = DLLInsert(dll2, T2, &x2);
    T3 = DLLEnd(dll2);
    T2 = DLLGetNext(T2);
    T3 = DLLGetPrev(T3);
    RUN_TEST(1 == DLLIsSameIter(T2, T3))

    DLLDestroy(dll1);
    DLLDestroy(dll2);

    printf("Linked List 4:\n");
    dll1 = DLLCreate();
    dll2 = DLLCreate();
    T1 = DLLEnd(dll1);
    T2 = DLLEnd(dll2);
    T1 = DLLPushBack(dll1, &x5);
    T1 = DLLPushBack(dll1, &x4);
    RUN_TEST(4 == *(int *)(DLLGetData(T1)));
    RUN_TEST(2 == DLLSize(dll1));
    T1 = DLLRemove(T1);
    T1 = DLLGetPrev(T1);
    RUN_TEST(5 == *(int *)(DLLGetData(T1)));
    T1 = DLLPushFront(dll1, &x1);
    RUN_TEST(1 == *(int *)(DLLGetData(T1)));
    T1 = DLLRemove(T1);
    RUN_TEST(5 == *(int *)(DLLGetData(T1)));
    T1 = DLLPushBack(dll1, &x5);
    T1 = DLLPushBack(dll1, &x4);
    RUN_TEST(4 == *(int *)(DLLGetData(T1)));
    T1 = DLLBegin(dll1);
    T1 = DLLInsert(dll1, T1, &x3);
    printf("%d\n", *(int *)(DLLGetData(T1)));
    RUN_TEST(3 == *(int *)(DLLGetData(T1)));

    DLLDestroy(dll1);
    DLLDestroy(dll2);

    printf("Linked List 5:\n");
    dll1 = DLLCreate();
    T1 = DLLEnd(dll1);
    T1 = DLLPushBack(dll1, &x5);
    RUN_TEST(5 == *(int *)DLLPopBack(dll1));
    T1 = DLLPushFront(dll1, &x1);
    RUN_TEST(1 == *(int *)DLLPopFront(dll1));

    DLLDestroy(dll1);

    printf("Linked List 6:\n");
    dll1 = DLLCreate();
    T1 = DLLEnd(dll1);
    T1 = DLLInsert(dll1, T1, &x1);
    T1 = DLLInsert(dll1, T1, &x2);
    T1 = DLLInsert(dll1, T1, &x3);
    T1 = DLLInsert(dll1, T1, &x4);
    T1 = DLLInsert(dll1, T1, &x5);
    T2 = DLLBegin(dll1);
    T1 = DLLEnd(dll1);
    RUN_TEST(5 == DLLSize(dll1));
    DLLForEach(DLLBegin(dll1), DLLEnd(dll1), &PrintNode, &x2);
    printf("\n");
    RUN_TEST((DLLGetPrev(DLLGetPrev(T1)))== DLLFind(T2, T1, &IsMatch, &x2));

    DLLForEach(DLLBegin(dll1), DLLEnd(dll1), &AddToNode, &x1);
    printf("\n");

    DLLForEach(DLLBegin(dll1), DLLEnd(dll1), &PrintNode, &x2);
    printf("\n");
    
    RUN_TEST(56 == DLLSize(dll1)); /* JUST KIDDING WELL DONE! :)  */
    DLLDestroy(dll1);
}

int main()
{   
    TestDLinkedList();
    return 0;
}