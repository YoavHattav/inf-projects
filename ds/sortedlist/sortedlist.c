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

struct SLL
{
	struct DLL *list;
	is_before func;
	void *param;
};

struct Iterator
{
	struct DLLNode *current;
};

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



sll_t *SortLLCreate(is_before func, void *param)
{
	sll_t *new_sll = (sll_t *)malloc(sizeof(sll_t));
	if (NULL == sll_t)
	{
		return NULL;
	}
	new_sll->list = DLLCreate();
	if (NULL == new_sll->list)
	{
		FREE(new_sll);
		return NULL;
	}

	new_sll->func = func;
	new_sll->param = param;

	return new_sll;
}

void SortLLDestroy(sll_t *sll)
{
	DLLDestroy(sll->list);
}

sll_iterator_t SortLLinsert(sll_t *sll, void *data)
{

}

sll_iterator_t SortLLRemove(sll_iterator_t it)
{
	return DLLRemove(it.current);
}

int SLLIsEmpty(const sll_t *sll)
{
	DLLIsEmpty(sll->list);
}

size_t SLLSize(const sll_t *sll)
{
	DLLSize(sll->list);
}

sll_iterator_t SLLBegin(sll_t *sll)
{
	DLLBegin(sll->list);
}

sll_iterator_t SLLEnd(sll_t *sll)
{
	DLLEnd(sll->list);
}

sll_iterator_t SLLNext(sll_iterator_t it)
{
	return DLLGetNext(it.current);
}

sll_iterator_t SLLPrev(sll_iterator_t it)
{
	return DLLGetPrev(it.current);
}

void *SLLGetData(sll_iterator_t it)
{
	return DLLGetData(it.current);
}

int SLLIsSameIter(const sll_iterator_t it1, const sll_iterator_t it2)
{
	return DLLIsSameIter(it1.current, it2.current);
}

void* SLLPopBack(sll_t *sll)
{
	return DLLPopBack(sll->list);
}

void* SLLPopFront(sll_t *sll)
{
	return DLLPopFront(sll->list);
}

int SLLForEach(sll_iterator_t start, sll_iterator_t end, action_func_ptr a_ptr, void *ap)
{
	return DLLForEach(start, end, a_ptr, ap);
}

sll_iterator_t SLLFind(const sll_t *sll, const void *data, sll_iterator_t start, sll_iterator_t end)
{

}

sll_iterator_t SLLFindBy(const sll_t *sll, sll_iterator_t start , sll_iterator_t end

                                        match_func_ptr m_ptr ,const void *data)
{

}

void SLLMerge(sll_t *dest, sll_t *src)
{

}
