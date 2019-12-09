/*********************************/
/*    Data Structures            */
/*    DLL                        */
/*    Author :Yoav Hattav        */
/*    Reviewed By: Razul         */
/*    Date:     09/12/2019       */
/*********************************/
#include <assert.h> /* assert */ 
#include <stdlib.h>	/* malloc */ 

#include "dllist.h" /* API */ 

#define FREE(ptr) free(ptr); ptr = NULL;

struct DLLNode
{
	void *data;
	struct DLLNode *next;
	struct DLLNode *prev;
};
struct DLL 
{
	struct DLLNode head;
	struct DLLNode tail;
};

dll_t *DLLCreate()
{
	dll_t *new_dll = (dll_t *)malloc(sizeof(dll_t));
	if (NULL == new_dll)
	{
		return NULL;
	}

	new_dll->head.data = NULL;
	new_dll->head.next = &new_dll->tail;
	new_dll->head.prev = NULL;

	new_dll->tail.data = NULL;
	new_dll->tail.next = NULL;
	new_dll->tail.prev = &new_dll->head;

	return new_dll;
}

void DLLDestroy(dll_t *dll)
{
	iterator_t current = dll->head.next;
	iterator_t next_node = dll->head.next;

	assert(NULL != dll);

	while (current != &dll->tail)
	{		
		next_node = next_node->next;
		FREE(current);
		current = next_node;
	}
	FREE(dll);
}

iterator_t DLLGetNext(iterator_t it)
{
	it = it->next;

	return it;
}

iterator_t DLLGetPrev(iterator_t it)
{
	it = it->prev;

	return it;
}

iterator_t DLLInsert(dll_t *dll, iterator_t it, void *data)
{

	iterator_t new_node = (iterator_t)malloc(sizeof(dllnode_t));
	if (NULL == new_node)
	{
		it = &dll->tail;
		return it;
	}

	new_node->data = data;
	new_node->next = it;
	new_node->prev = it->prev;
	it->prev = new_node;
	(new_node->prev)->next = new_node;

	it = new_node;

	return it;
}

iterator_t DLLRemove(iterator_t it)
{	
	iterator_t it_temp = it;

	it = it->next;
	it_temp->next->prev = it_temp->prev;
	it_temp->prev->next = it_temp->next;

	FREE(it_temp); 

	return it;

}

int DLLIsEmpty(const dll_t *dll)
{
	assert(NULL != dll);

	return ((dll->head.next == &dll->tail) && (&dll->head == dll->tail.prev));
}

size_t DLLSize(const dll_t *dll)
{
	const dllnode_t  *dll_run = dll->head.next;
	size_t size_of_dll = 0;

	assert(NULL != dll);

	while (dll_run != &dll->tail)
	{
		++size_of_dll;
		dll_run = dll_run->next;
	}

	return size_of_dll;
}

iterator_t DLLBegin(dll_t *dll)
{
	iterator_t it;

	it = dll->head.next;

	return it;
}

iterator_t DLLEnd(dll_t *dll)
{
	iterator_t it;

	it = (dllnode_t *)&(dll->tail);

	return it;
}

void *DLLGetData(iterator_t it)
{
	return it->data;
}

int DLLIsSameIter(const iterator_t it1, const iterator_t it2)
{
	return ((it1->next == it2->next) && (it1->prev == it2->prev) && (it1->data == it2->data));
}

iterator_t DLLPushBack(dll_t *dll, void *data)
{
	assert(NULL != dll);

	return (DLLInsert(dll, DLLEnd(dll), data));
}

void *DLLPopBack(dll_t *dll)
{
	void *data = dll->tail.prev->data;

	assert(NULL != dll);

	DLLRemove(DLLGetPrev(DLLEnd(dll)));

	return data;
}

iterator_t DLLPushFront(dll_t *dll, void *data)
{
	assert(NULL != dll);

	return (DLLInsert(dll, DLLBegin(dll), data));
}

void *DLLPopFront(dll_t *dll)
{
	void *data = dll->head.next->data;

	assert(NULL != dll);

	DLLRemove(DLLBegin(dll));

	return data;
}

iterator_t DLLSplice(iterator_t start, iterator_t end, iterator_t where)
{
	start->prev->next = end;
	end->prev->next = where->next;
	where->next->prev = end->prev;
	where->next = start;
	end->prev = start->prev;
	start->prev = where;

	return where;
}

int DLLForEach(iterator_t start, iterator_t end, action_func_ptr a_ptr, void *ap)
{
	iterator_t i = start;

	for (i = start ; i != end ; i = DLLGetNext(i))
	{
		if (0 != a_ptr(i->data, ap))
		{
			return 1;
		}
	}

	return 0;
}


iterator_t DLLFind(iterator_t start, iterator_t end, match_func_ptr m_ptr, void *ap)
{
	iterator_t i = start;

	for (i = start ; i != end ; i = DLLGetNext(i))
	{
		if (1 == m_ptr(i->data, ap))
		{
			return i;
		}
	}

	return end;
}
