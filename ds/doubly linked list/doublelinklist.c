#include <assert.h>
#include <stdlib.h>

#include "dllist.h"

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
struct Iterator
{
	struct DLLNode *node;
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
	iterator_t it = DLLBegin(dll);

	assert(NULL != dll);

	while (it.node != DLLEnd(dll).node)
	{
		it = DLLRemove(it);
	}
}

iterator_t DLLGetNext(iterator_t it)
{
	it.node = it.node->next;

	return it;
}

iterator_t DLLGetPrev(iterator_t it)
{
	it.node = it.node->prev;

	return it;
}

iterator_t DLLInsert(dll_t *dll, iterator_t it, void *data)
{

	dllnode_t *new_node = (dllnode_t *)malloc(sizeof(dllnode_t));
	if (NULL == new_node)
	{
		 it.node = &dll->tail;
		return it;
	}

	new_node->data = data;
	new_node->next = it.node;
	new_node->prev = it.node->prev;
	it.node->prev = new_node;
	(new_node->prev)->next = new_node;

	it.node = new_node;

	return it;
}

iterator_t DLLRemove(iterator_t it)
{	
	iterator_t it_temp = it;

	it.node = it.node->next;
	it_temp.node->next->prev = it_temp.node->prev;
	it_temp.node->prev->next = it_temp.node->next;

	free(it_temp.node); it_temp.node = NULL;

	return it;

}

int DLLIsEmpty(const dll_t *dll)
{
	assert(NULL != dll);

	return (dll->head.next == dll->tail.prev);
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

	it.node = dll->head.next;

	return it;
}

iterator_t DLLEnd(const dll_t *dll)
{

	iterator_t it;

	it.node = (dllnode_t *)&(dll->tail.prev);

	return it;
}

void *GetData(iterator_t it)
{
	return it.node->data;
}

int DLLIsSameIter(const iterator_t it1, const iterator_t it2)
{
	return ((it1.node->next == it2.node->next) && (it1.node->prev == it2.node->prev) && (it1.node->data == it2.node->data));
}

iterator_t DLLPushBack(dll_t *dll, void *data)
{
	assert(NULL != dll);

	return (DLLInsert(dll, DLLEnd(dll), data));
}

void *DLLPopBack(dll_t *dll)
{
	assert(NULL != dll);

	DLLRemove(DLLEnd(dll));
}

iterator_t DLLPushFront(dll_t *dll, void *data)
{
	assert(NULL != dll);

	return (DLLInsert(dll, DLLBegin(dll), data));
}

void *DLLPopFront(dll_t *dll)
{
	assert(NULL != dll);

	DLLRemove(DLLBegin(dll));
}

iterator_t DLLSplice(iterator_t start, iterator_t end, iterator_t where)
{
	start.node->prev->next = end.node;
	end.node->prev->next = where.node->next;
	where.node->next->prev = end.node->prev;
	where.node->next = start.node;
	end.node->prev = start.node->prev;
	start.node->prev = where.node;

	return where;
}

int DLLForEach(iterator_t start, iterator_t end, action_func_ptr a_ptr, void *ap)
{

}

iterator_t DLLFind(iterator_t start, iterator_t end, match_func_ptr m_ptr, void *ap)
{

}
