/*********************************/
/*    Data Structures            */
/*    Bits Array                 */
/*    Author :Yoav Hattav        */
/*    Reviewed By:               */
/*    Date:     26/11/2019       */
/*                               */
/*********************************/
#include <stdlib.h> /* calloc usage*/
#include <string.h> /* strcmp usage */
#include <stdio.h>

#include "queue.h"
#include "linkedlist.h"


#define GREEN "\033[0;32m"
#define RED "\033[1;31m"
#define WHITE "\033[0m"



#define RUN_TEST(Test, msg) if (Test)\
                        {\
                            printf(GREEN);\
                            printf("SUCCESS- %s\n", msg);\
                        }\
                        else\
                        {\
                            printf(RED);\
                            printf("FAIL- %s\n", msg);\
                        }\
                        printf(WHITE);
struct Queue
{
    node_t *front;
    node_t *rear;
};

static void TestQueue()
{
    int x1 = 1, x2 = 2;
    
    queue_t *new_queue = NULL;
    queue_t *new_queue1 = NULL;
    queue_t *new_queue2 = NULL;
    queue_t *new_queue3 = NULL;
    
    printf("Queue Test 1:\n");
    new_queue = QCreate();
    RUN_TEST(0 == QEnqueue(new_queue, &x1),"enqueue");
    RUN_TEST(0 == QEnqueue(new_queue, &x2),"enqueue");
    RUN_TEST(2 == QSize(new_queue), "size");
    QDestroy(new_queue);
    
    printf("Queue Test 2:\n");
    new_queue = QCreate();
    RUN_TEST(0 == QEnqueue(new_queue, &x1),"enqueue");
    QDequeue(new_queue);
    RUN_TEST(0 == QSize(new_queue), "size");
    QDestroy(new_queue);
      
    printf("Queue Test 3:\n");
    new_queue = QCreate();
    RUN_TEST(1 == QIsEmpty(new_queue),"is empty");
    RUN_TEST(0 == QEnqueue(new_queue, &x1),"enqueue");
    RUN_TEST(1 == QSize(new_queue), "size");
    RUN_TEST(0 == QIsEmpty(new_queue),"is empty");
    QDestroy(new_queue);
    
    printf("Queue Test 4:\n");
    new_queue = QCreate();
    RUN_TEST(0 == QEnqueue(new_queue, &x1),"enqueue");
    RUN_TEST(0 == QEnqueue(new_queue, &x2),"enqueue");
    RUN_TEST(1 == *(int*)QPeek(new_queue),"peek");
    QDequeue(new_queue);
    RUN_TEST(2 == *(int*)QPeek(new_queue),"peek");
    QDestroy(new_queue);
    
    printf("Queue Test 5:\n");
    new_queue = QCreate();
    RUN_TEST(0 == QEnqueue(new_queue, &x1),"enqueue");
    RUN_TEST(0 == QEnqueue(new_queue, &x2),"enqueue");
    RUN_TEST(0 == QEnqueue(new_queue, &x2),"enqueue");
    RUN_TEST(3 == QSize(new_queue), "size");
    
    new_queue1 = QCreate();
    RUN_TEST(0 == QEnqueue(new_queue1, &x1),"enqueue");
    RUN_TEST(0 == QEnqueue(new_queue1, &x2),"enqueue");
    RUN_TEST(0 == QEnqueue(new_queue1, &x2),"enqueue");
    RUN_TEST(3 == QSize(new_queue1), "size");
      
    QAppend(new_queue,new_queue1);
    RUN_TEST(6 == QSize(new_queue), "size append");
    QDestroy(new_queue);

    printf("Queue test 6:\n");
    new_queue = QCreate();
    RUN_TEST(0 == QEnqueue(new_queue, &x2), "omg");
    RUN_TEST(0 == QEnqueue(new_queue, &x1), "betty");
    RUN_TEST(0 == QEnqueue(new_queue, &x2), "omg");



}

int main()
{   
    TestQueue();
    return 0;
}
