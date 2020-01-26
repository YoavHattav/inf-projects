/*********************************/
/*    Data Structures            */
/*    priority queue             */
/*    Author :Yoav Hattav        */
/*    Reviewed By: Israel        */
/*    Date:     12/12/2019       */
/*********************************/

#include <assert.h> /* assert */ 
#include <stdlib.h>	/* malloc */ 

#include "../include/priorityq.h" /* API */
#include "../include/vector.h"    /* API */ 
#include "../include/heapify.h"

#define FREE(ptr) free(ptr); ptr = NULL;
#define STARTING_SIZE 1
#define FIRST_POSITION 0
#define ELEMENT_SIZE sizeof(void *)
#define FALSE 0
#define TRUE 1
#define SUCC 0
#define FAIL 1

/*typedef struct Wraper
{
	void *param;
	compare_func_ptr pq_user_cmp;
}wrap_t;

struct PQueue 
{
	vector_t *queue;  
	wrap_t rap;
};*/

struct PQueue 
{
	vector_t *queue;
	cmp_func_t cmp;
	void *param;
};

pq_t *PQCreate(cmp_func_t user_cmp, void *param)
{	
	pq_t *new_pq = NULL;

	assert(NULL != user_cmp);

	new_pq = malloc(sizeof(*new_pq));
	if (NULL != new_pq)
	{
		new_pq->queue = VectorCreate(ELEMENT_SIZE, STARTING_SIZE);
		if (NULL != new_pq->queue)
		{
			new_pq->cmp = user_cmp;
			new_pq->param = param;

			return new_pq;
		}
		FREE(new_pq);
	}

	return NULL;
}

/*int MyCmp(const void *data1, const void *data2, void *param)
{
	wrap_t *rap = (wrap_t *)param;

	return (0 < rap->pq_user_cmp((void *)data1, (void *)data2, rap->param));
}

pq_t *PQCreate(compare_func_ptr user_cmp, void *param)
{	
	pq_t *new_pq = malloc(sizeof(*new_pq));
	if (NULL != new_pq)
	{
		new_pq->queue = VectorCreate(ELEMENT_SIZE, STARTING_SIZE);
		if (NULL != new_pq->queue)
		{
			new_pq->rap.pq_user_cmp = user_cmp;
			new_pq->rap.param = param;

			return new_pq;
		}
		FREE(new_pq);
	}

	return NULL;
}*/

void PQDestroy(pq_t *pq)
{
	assert(NULL != pq);

	VectorDestroy(pq->queue);

	FREE(pq);
}

void *PQDequeue(pq_t *pq)
{
	void **dequeued_data = NULL;

	assert(NULL != pq);
	
	dequeued_data = (VectorGetItemAddress(pq->queue, FIRST_POSITION));
	VectorPopBack(pq->queue);

	return *dequeued_data;
}

int PQEnqueue(pq_t *pq, void *data)
{
	size_t size = 0;

	assert(NULL != pq);

	size = VectorSize(pq->queue);
	 
	if (VectorPushBack(pq->queue, data))
	{
		return FAIL;
	}
	HeapifyUp(pq->queue, size, size -1, ELEMENT_SIZE, pq->rap.pq_user_cmp, pq->rap.param);

	return SUCC;
}

void *PQPeek(const pq_t *pq)
{
	assert(NULL != pq);

	return VectorGetItemAddress(pq->queue, FIRST_POSITION);
}

size_t PQSize(const pq_t *pq)
{	
	size_t size = 0;

	assert(NULL != pq);

	return VectorSize(pq->queue);
}

int PQIsEmpty(const pq_t *pq)
{
	assert(NULL != pq);

	return (0 == VectorSize(pq->queue));
}

void PQClear(pq_t *pq)
{

	assert(NULL != pq);

	while (VectorSize(pq->queue))
	{
		VectorPopBack(pq->queue);
	}
	
}

void *PQErase(pq_t *pq, match_func m_ptr, void *data)
{
	void *tmp_data = NULL;

	assert(NULL != pq);
	assert(NULL != data);

	


	return tmp_data;
}

static void SwapPlace(void **child, void **father)
{	
	void *temp = *child;

	*child  = *father;
	*father  = temp;
}

void HeapifyUp(void *arr, size_t size, size_t index, size_t element_size, cmp_func_t cmp, void *param)
{
	size_t next_parent = size;
	void **child = VectorGetItemAddress(arr, size);
	void **parent = VectorGetItemAddress(arr, size / 2);

	while ((1 == cmp(*child, *parent, param)) && (0 != next_parent))
	{
		SwapPlace(child, parent);

		next_parent /= 2;
		child = parent;
		parent = VectorGetItemAddress(arr, next_parent);
	}
}

void HeapifyDown(void *arr, size_t size, size_t index, size_t element_size, cmp_func_t cmp, void *param)
{
	size_t psition = 1;
	void **child = VectorGetItemAddress(arr, psition);
	void **father = VectorGetItemAddress(arr, FIRST_POSITION);


}
