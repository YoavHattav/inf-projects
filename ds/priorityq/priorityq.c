/*********************************/
/*    Data Structures            */
/*    priority queue             */
/*    Author :Yoav Hattav        */
/*    Reviewed By: Israel        */
/*    Date:     12/12/2019       */
/*********************************/

#include <assert.h> /* assert */ 
#include <stdlib.h>	/* malloc */ 

#include "priorityqueue.h" /* API */
#include "sortedlist.h"    /* API */ 

#define FREE(ptr) free(ptr); ptr = NULL;

typedef struct Wraper
{
	void *param;
	compare_func_ptr pq_user_cmp;
}wrap_t;

struct PQueue 
{
	sll_t *queue;  
	wrap_t rap;
};

int MyIsBefore(const void *data1, const void *data2, void *param)
{
	wrap_t *rap = (wrap_t *)param;

	return (0 < rap->pq_user_cmp((void *)data1, (void *)data2, rap->param));
}

pq_t *PQCreate(compare_func_ptr user_cmp, void *param)
{	

	pq_t *new_pq = (pq_t *)malloc(sizeof(pq_t));
	if (NULL != new_pq)
	{
		new_pq->queue = SortLLCreate(&MyIsBefore, &new_pq->rap);
		if (NULL != new_pq->queue)
		{
			new_pq->rap.pq_user_cmp = user_cmp;
			new_pq->rap.param = param;

			return new_pq;
		}
		FREE(new_pq);
	}

	return NULL;
}

void PQDestroy(pq_t *pq)
{
	assert(NULL != pq);

	SortLLDestroy(pq->queue);

	FREE(pq);
}

void *PQDequeue(pq_t *pq)
{
	assert(NULL != pq);

	return SLLPopFront(pq->queue);
}

int PQEnqueue(pq_t *pq, void *data)
{
	assert(NULL != pq);

	return (1 == SLLIsSameIter(SLLEnd(pq->queue), SortLLInsert(pq->queue, data)));
}

void *PQPeek(const pq_t *pq)
{
	assert(NULL != pq);

	return SLLGetData(SLLBegin(pq->queue));
}

size_t PQSize(const pq_t *pq)
{	
	assert(NULL != pq);

	return SLLSize(pq->queue);
}

int PQIsEmpty(const pq_t *pq)
{
	assert(NULL != pq);

	return SLLIsEmpty(pq->queue);
}

void PQClear(pq_t *pq)
{
	assert(NULL != pq);

	while (!PQIsEmpty(pq))
	{
		PQDequeue(pq);
	}
}

void *PQErase(pq_t *pq, match_func m_ptr, void *data)
{
	void *tmp_data = NULL;
	sll_iterator_t it;

	assert(NULL != pq);
	assert(NULL != data);

	it = SLLFindBy(pq->queue, SLLBegin(pq->queue), SLLEnd(pq->queue), m_ptr, data);

	tmp_data = SLLGetData(it); 

	if (!SLLIsSameIter(it, SLLEnd(pq->queue)))
	{
		SortLLRemove(it);
	}

	return tmp_data;
}
