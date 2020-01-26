
/*********************************/
/*    Data Structures            */
/*    priority queue             */
/*    Author :Yoav Hattav        */
/*    Reviewed By:         */
/*    Date:     26/01/2020       */
/*********************************/
#include <stdio.h>

#include "../include/priorityq.h" /* API */

#define GREEN "\033[;032m"
#define RED   "\033[;031m"
#define RESET "\033[0m"
#define UNUSED(x) (void)(x)
#define RUN_TEST(test,mssg)\
            if (test)\
            {\
                printf(GREEN "SUCCESS: %s\n",mssg);\
                printf(RESET);\
            }\
            else\
            {\
                printf(RED "FAIL: %s\n",mssg);\
                printf(RESET);\
            }\

int UserCmp(const void *data1, const void *data2, void *param)
{
	UNUSED(param);

	return ((int *)data1 - (int *)data2);
}

int MatchFunc(void *data, void *additional)
{   
    return (*(int*)data == *(int*)additional);
}

static void Test()
{
    pq_t *pq = NULL;

    int x1 = 1;
    int x2 = 2;
    int x3 = 3;
    int x4 = 4;
    
    printf("PQ Test 1:\n");  
    pq = PQCreate(&UserCmp, NULL);
    RUN_TEST(0 == PQEnqueue(pq, &x1), "enqueue");
    RUN_TEST(0 == PQEnqueue(pq, &x3), "enqueue");
    RUN_TEST(0 == PQEnqueue(pq, &x2), "enqueue");
    RUN_TEST(0 == PQEnqueue(pq, &x2), "enqueue");
    RUN_TEST(3 == *(int *)PQPeek(pq), "peek");
    RUN_TEST(3 == *(int *)PQDequeue(pq), "Dequeue");
    RUN_TEST(2 == *(int *)PQDequeue(pq), "Dequeue");
    RUN_TEST(2 == *(int *)PQDequeue(pq), "Dequeue");
    RUN_TEST(1 == *(int *)PQDequeue(pq), "Dequeue");
    PQDestroy(pq);
    
    printf("PQ Test 2:\n");  
    pq = PQCreate(&UserCmp, NULL);
    RUN_TEST(0 == PQSize(pq), "size");
    RUN_TEST(1 == PQIsEmpty(pq), "size");
    RUN_TEST(0 == PQEnqueue(pq, &x1), "enqueue");
    RUN_TEST(1 == PQSize(pq), "size");
 
    PQDestroy(pq); 
    
    printf("PQ Test 3:\n");  
    pq = PQCreate(&UserCmp, NULL);
    RUN_TEST(0 == PQEnqueue(pq, &x1), "enqueue");
    RUN_TEST(0 == PQEnqueue(pq, &x3), "enqueue");
    RUN_TEST(0 == PQEnqueue(pq, &x2), "enqueue");
    RUN_TEST(0 == PQEnqueue(pq, &x2), "enqueue");
    RUN_TEST(2 == *(int*)PQErase(pq, &MatchFunc, &x2), "erase");
    RUN_TEST(3 == PQSize(pq), "size");
    RUN_TEST(NULL == PQErase(pq, &MatchFunc, &x4), "erase");
 
    PQDestroy(pq); 
    
    printf("PQ Test 4:\n");  
    pq = PQCreate(&UserCmp, NULL);
    RUN_TEST(0 == PQEnqueue(pq, &x1), "enqueue");
    RUN_TEST(0 == PQEnqueue(pq, &x3), "enqueue");
    RUN_TEST(0 == PQEnqueue(pq, &x2), "enqueue");
    RUN_TEST(0 == PQEnqueue(pq, &x2), "enqueue");
    PQClear(pq);
    RUN_TEST(0 == PQSize(pq), "size");
 
    PQDestroy(pq); 
}

int main()
{
	Test();
	return 0;
}
