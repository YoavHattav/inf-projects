/*********************************/
/*    Data Structures            */
/*    priority queue             */
/*    Author :Yoav Hattav        */
/*    Reviewed By:         */
/*    Date:     26/01/2020       */
/*********************************/

#include <assert.h> /* assert */ 
#include <stdlib.h>	/* malloc */ 

#include "heapify.h"
#include "vector.h"

#define STARTING_SIZE 1
#define FIRST_POSITION 1
#define FIRST_RIGHT_CHILD 2
#define FIRST_LEFT_CHILD 1
#define ELEMENT_SIZE sizeof(void *)
#define FALSE 0
#define TRUE 1
#define SUCC 0
#define FAIL 1

struct PQueue 
{
	vector_t *queue;
	compare_func_ptr cmp;
	void *param;
};

static void SwapPlace(void **child, void **father)
{	
	void *temp = *child;

	*child  = *father;
	*father  = temp;
}

void HeapifyUp(void *arr, size_t size, size_t index, size_t element_size, compare_func_ptr cmp, void *param)
{
	size_t next_parent = index / 2;
	void **child = VectorGetItemAddress(arr, index);

	if ((1 < size) && (0 < next_parent))
	{
		void **parent = VectorGetItemAddress(arr, next_parent);

		while ((0 != next_parent) && (0 < cmp(*child, *parent, param)))
		{
			SwapPlace(child, parent);

			next_parent /= 2;
			child = parent;
			parent = VectorGetItemAddress(arr, next_parent);
		}
	}
}

void HeapifyDown(void *arr, size_t size, size_t index, size_t element_size, compare_func_ptr cmp, void *param)
{
	size_t parent_index = FIRST_POSITION;
	size_t child_left_index = parent_index * 2;
	size_t child_right_index = parent_index * 2 + 1;
	void **parent_addres = NULL;
	void **leaf_left_addres = NULL;
	void **leaf_right_addres = NULL;
	int res = 0;

	leaf_left_addres = VectorGetItemAddress(arr, child_left_index);
	leaf_right_addres = VectorGetItemAddress(arr, child_right_index);
	parent_addres = VectorGetItemAddress(arr, parent_index);

	if (child_right_index <= size)
	{
		while (child_right_index <= size)
		{
			res = cmp(*leaf_left_addres, *leaf_right_addres, param);

			if ((0 < res) && (0 < cmp(*leaf_left_addres, *parent_addres, param)))
			{
				SwapPlace(parent_addres, leaf_left_addres);
				parent_index = child_left_index;
			}
			else if ((0 >= res) && (0 < cmp(*leaf_right_addres, *parent_addres, param)))
			{
				SwapPlace(parent_addres, leaf_right_addres);
				parent_index = child_right_index;
			}
			else
			{
				break;
			}

			child_left_index = parent_index * 2;
			child_right_index = parent_index * 2 + 1;

			leaf_left_addres = VectorGetItemAddress(arr, child_left_index);
			leaf_right_addres = VectorGetItemAddress(arr, child_right_index);
			parent_addres = VectorGetItemAddress(arr, parent_index);
		}
	}

	else if ((child_left_index == size) && (0 < cmp(*leaf_left_addres, *parent_addres, param)))
	{
		SwapPlace(parent_addres, leaf_left_addres);
	}
}
	

pq_t *PQCreate(compare_func_ptr user_cmp, void *param)
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
		free(new_pq);new_pq = NULL;
	}

	return NULL;
}

void PQDestroy(pq_t *pq)
{
	assert(NULL != pq);

	VectorDestroy(pq->queue);

	free(pq);pq = NULL;
}

void *PQDequeue(pq_t *pq)
{
	void **child = NULL;
	void **parent = NULL;
	void *dequeued_data = NULL;
	size_t size = 0;

	assert(NULL != pq);
	
	child = VectorGetItemAddress(pq->queue, VectorSize(pq->queue));
	parent = VectorGetItemAddress(pq->queue, FIRST_POSITION);
	SwapPlace(child, parent);

	dequeued_data = *child;

	VectorPopBack(pq->queue);
	size = VectorSize(pq->queue);
	HeapifyDown(pq->queue, size, size -1, ELEMENT_SIZE, pq->cmp, pq->param);

	return dequeued_data;
}

int PQEnqueue(pq_t *pq, void *data)
{
	size_t size = 0;

	assert(NULL != pq);

	 
	if (VectorPushBack(pq->queue, &data))
	{
		return FAIL;
	}
	size = VectorSize(pq->queue);

	HeapifyUp(pq->queue, size, size, ELEMENT_SIZE, pq->cmp, pq->param);

	return SUCC;
}

void *PQPeek(const pq_t *pq)
{
	void **first_element_address = NULL;
	assert(NULL != pq);

	first_element_address = VectorGetItemAddress(pq->queue, FIRST_POSITION);

	return *first_element_address;
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
	void *tmp_holder = NULL;
	void **last_element = NULL;
	void **swapped_holder = NULL;
	size_t size = 0;
	int i = 0;
	int res = 0;

	assert(NULL != pq);
	assert(NULL != data);

	size = VectorSize(pq->queue);

	if (0 < size)
	{
		last_element = VectorGetItemAddress(pq->queue, size);

		for (i = 1; i <= size; ++i)
		{
			swapped_holder = VectorGetItemAddress(pq->queue, i);
			res = m_ptr(*swapped_holder, data);

			if (1 == res)
			{
				tmp_holder = *swapped_holder;
				SwapPlace(last_element, swapped_holder);

				if (*last_element != *swapped_holder)
				{
					HeapifyUp(pq->queue, size, i, ELEMENT_SIZE, pq->cmp, pq->param);
					HeapifyDown(pq->queue, size, i, ELEMENT_SIZE, pq->cmp, pq->param);	
				}

				VectorPopBack(pq->queue);

				return tmp_holder;
			}
		}

	}
	
	return NULL;
}

