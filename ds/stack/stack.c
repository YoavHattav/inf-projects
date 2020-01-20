/*********************************/
/*    Data Structures            */
/*    Stack DS                   */
/*    Author :Yoav Hattav        */
/*    Reviewed By: Guy Zedek     */
/*    Date:     27/11/2019       */
/*                               */
/*********************************/
#include <assert.h> /* assert usage */
#include <stdlib.h> /* memory aloocation */
#include <stdio.h>  /* printf function */  
#include <string.h> /* memcpy usage */

#include "stack.h" /* user API */

struct Stack
{
	void* start;
	void* current;
	void* end;
	size_t element_size;
};

/* This function creates new Stack */
stack_t* StackCreate(size_t element_size, size_t capacity)
{
	stack_t *newstack = (stack_t *) malloc(sizeof(stack_t));
	if (NULL == newstack)
	{
		return NULL;
	}

	newstack->start = (void *) malloc(capacity * element_size);
	if (NULL == newstack->start)
	{
		return NULL;
	}

	newstack->current = newstack->start;
	newstack->end = (char *)newstack->start + (capacity * element_size);
	newstack->element_size = element_size;

	return newstack;
}

/* This function destroys the Stack */
void StackDestroy(stack_t* mystack)
{
	assert(NULL != mystack);

	free(mystack->start); mystack->start = NULL;
	free(mystack); mystack = NULL; 
}

/* This function pushes the given element to the top of the Stack */
int StackPush(stack_t* mystack, const void* data)
{
	assert(NULL != mystack);
	assert(NULL != data);

	if (mystack->current == mystack->end)
	{
		printf("the stack is full, didnt add.\n");

		return 1;
	}

	memmove(mystack->current, data, mystack->element_size);
	mystack->current = (char *)mystack->current + mystack->element_size;

	return 0;
}

/* This function pops the element that is on the top of the Stack and removes it */
void StackPop(stack_t* mystack)
{
	assert(NULL != mystack);

	if (mystack->current != mystack->start)
	{
		mystack->current = (char *)mystack->current - mystack->element_size;
	}
	else
	{
		printf("the stack is empty, cant pop");
	}		
}

/* This function checkes if the Stack is empty */
int StackIsEmpty(const stack_t* mystack)
{
	assert(NULL != mystack);

	return (mystack->current == mystack->start);
}

/* This function return the number of elements in the stack */
size_t StackSize(const stack_t* mystack)
{
	assert(NULL != mystack);

	return (((char *)mystack->current - (char *)mystack->start)/(mystack->element_size));                 /* check if its current -1 */
}

/* This function returns the top most elemet on the Stack */
void* StackPeek(const stack_t* mystack)
{
	assert(NULL != mystack);

	if (mystack->current == mystack->start)
	{
		printf("the stack is empty, cant see anything\n");

		return NULL;
	}

	return ((char *)mystack->current - mystack->element_size);
}

void StackSortRec(stack_t *stack)
{
	int first_holder = 0;
	int second_holder = 0;

	if (StackIsEmpty(stack))
	{	
		return;
	}

	if (1 == StackSize(stack))
	{
		return;
	}

	first_holder = *(int *)StackPeek(stack);
	StackPop(stack);

	StackSortRec(stack);

	if (first_holder < *(int *)StackPeek(stack))
	{
		second_holder = *(int *)StackPeek(stack);
		StackPop(stack);
		StackPush(stack, &first_holder);

		StackSortRec(stack);

		StackPush(stack, &second_holder);	
	}
	else
	{
		StackPush(stack, &first_holder);
	}
}
