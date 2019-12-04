/*********************************/
/*    Data Structures            */
/*    Queue                      */       
/*    Author : Israel Drayfus    */
/*    Reviewed By:               */
/*    Date: 3/12/2019            */
/*                               */
/*********************************/

#ifndef __QUEUE_H__
#define __QUEUE_H__

#include <stddef.h> /* size_t */

#define UNUSED(x) (void)(x)

typedef struct Queue queue_t;

/* Creates new queue */
/*****time complexity: O(1) **************************/
/* return value: a ready-to-work queue */
/* parameter restrictions: none */
queue_t *QCreate();

/* Destroys the data structure */
/* WARNING: Doesnt get NULL pointer */
/*****time complexity: O(1) **************************/
/* return value: none */
/* parameter restrictions: NULL pointer */
void QDestroy(queue_t *queue);


/* Enter a new item to the queue */
/*****time complexity: O(1) **************************/
/* return value: 0/1 indicating success or failure */
/* parameter restrictions: NULL pointers */
int QEnqueue(queue_t *queue, void *data);

/* Get out the front item */
/* WARNING: Doesnt get NULL pointer */
/*****time complexity: O(1) **************************/
/* return value: none */
void QDequeue(queue_t *queue);

/* If empty returns 1, otherwise returns 0 */
/* WARNING: Doesnt get NULL pointer */
/*****time complexity: O(1) **************************/
/* return value: 0/1 indicating notempty or empty */
int QIsEmpty(const queue_t *queue);

/* Returns the front item */
/* WARNING: Doesnt get NULL pointer */
/*****time complexity: O(1) **************************/
/* return value: none */
void *QPeek(const queue_t *queue);

/* Returns the queue size */
/* WARNING: Doesnt get NULL pointer */
/*****time complexity: O(n) **************************/
/* return value: a non-negative number representing the size of queue */
size_t QSize(const queue_t *queue);

/* Appends the second queue to the first queue */
/* WARNING: Doesnt get NULL pointer */
/*****time complexity: O(1) **************************/
/* return value: a pointer to the new apended queue */
queue_t *QAppend(queue_t *queue1, queue_t *queue2);

#endif
