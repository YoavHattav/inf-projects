/*********************************/
/*    Data Structures            */
/*    sorted linked list         */
/*    Author :Yoav Hattav        */
/*    Reviewed By:               */
/*    Date:     11/12/2019       */
/*********************************/

#include <assert.h> /* assert */ 
#include <stdlib.h>	/* malloc */ 

#include "dllist.h" /* API */ 
#include "sortedlist.h" /* API */ 

#define FREE(ptr) free(ptr); ptr = NULL;

struct SLL
{
	struct DLL *list;
	is_before func;
	void *param;
};

sll_t *SortLLCreate(is_before func, void *param)
{
	sll_t *new_sll = (sll_t *)malloc(sizeof(sll_t));
	if (NULL == new_sll)
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
	assert(NULL != sll);

	DLLDestroy(sll->list);

	FREE(sll);
}

sll_iterator_t SortLLInsert(sll_t *sll, void *data)
{
	sll_iterator_t runner;
	runner.current = DLLBegin(sll->list);

	assert(NULL != sll);
	assert(NULL != data);

	while (DLLEnd(sll->list) != runner.current)
	{
		if (1 == sll->func(DLLGetData(runner.current), data, sll->param))
		{
			runner.current = DLLInsert(sll->list, runner.current, data);

			return runner;
		}

		runner.current = DLLGetNext(runner.current);
	}

	runner.current = DLLInsert(sll->list, runner.current, data);

	return runner;
}

sll_iterator_t SortLLRemove(sll_iterator_t it)
{
	it.current = DLLRemove(it.current);

	return it;
}

int SLLIsEmpty(const sll_t *sll)
{
	assert(NULL != sll);

	return DLLIsEmpty(sll->list);
}

size_t SLLSize(const sll_t *sll)
{
	assert(NULL != sll);

	return DLLSize(sll->list);
}

sll_iterator_t SLLBegin(sll_t *sll)
{
	sll_iterator_t it;

	assert(NULL != sll);

	it.current =  DLLBegin(sll->list);
	
	return it;
}

sll_iterator_t SLLEnd(sll_t *sll)
{
	sll_iterator_t it;

	assert(NULL != sll);

	it.current =  DLLEnd(sll->list);
	
	return it;
}

sll_iterator_t SLLNext(sll_iterator_t it)
{
	 it.current = DLLGetNext(it.current);

	 return it;
}

sll_iterator_t SLLPrev(sll_iterator_t it)
{
	it.current = DLLGetPrev(it.current);

	return it;
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
	assert(NULL != sll);

	return DLLPopBack(sll->list);
}

void* SLLPopFront(sll_t *sll)
{
	assert(NULL != sll);

	return DLLPopFront(sll->list);
}

int SLLForEach(sll_iterator_t start, sll_iterator_t end, action_func_ptr a_ptr,
																	 void *ap)
{
	return DLLForEach(start.current, end.current, a_ptr, ap);
}

sll_iterator_t SLLFind(const sll_t *sll, const void *data, sll_iterator_t start,
															 sll_iterator_t end)
{
	sll_iterator_t runner;

	assert(NULL != sll);
	assert(NULL != data);

	runner.current = DLLBegin(sll->list);

	while (end.current != runner.current)
	{
		if (1 == sll->func(DLLGetData(runner.current), data, sll->param))
		{
			runner = SLLPrev(runner);
            break;	
		}
		runner.current = DLLGetNext(runner.current);
	}
	
	if ((0 == sll->func(data, DLLGetData(runner.current) , sll->param)) && 
				(0 == sll->func(DLLGetData(runner.current), data, sll->param)))
    {
		return runner;
	}
    
	return end;
}

sll_iterator_t SLLFindBy(const sll_t *sll, sll_iterator_t start , 
					sll_iterator_t end, match_func_ptr m_ptr ,const void *data)
{
	sll_iterator_t it;

	assert(NULL != sll);

	it.current = DLLFind(start.current, end.current, m_ptr, (void *)data);

	return it;
}

void SLLMerge(sll_t *dest, sll_t *src)
{
	sll_iterator_t src_start = SLLBegin(src);
	sll_iterator_t src_end = SLLBegin(src);
	sll_iterator_t dest_current = SLLBegin(dest);

	assert(NULL != dest);
	assert(NULL != src);

	while (!(SLLIsSameIter(dest_current, SLLEnd(dest))) && 
										!(SLLIsSameIter(src_end, SLLEnd(src))))
	{
		while (!(dest->func(SLLGetData(src_end), 
										SLLGetData(dest_current), dest->param)))
		{
			if(!(SLLIsSameIter(dest_current, SLLEnd(dest))))
			{
				dest_current = SLLNext(dest_current);
			}
			
		}
		if((SLLIsSameIter(dest_current, SLLEnd(dest))))
		{
			break;
		}
		while (dest->func(SLLGetData(src_end), 
										SLLGetData(dest_current), dest->param))
		{
			if(!(SLLIsSameIter(src_end, SLLEnd(src))))
			{
				src_end = SLLNext(src_end);
			}	
		}

		DLLSplice(src_start.current, src_end.current, 
											DLLGetPrev(dest_current.current));
		dest_current = SLLNext(dest_current);
		src_start = src_end;
	}

	if(SLLIsSameIter(dest_current, SLLEnd(dest)))
	{
		src_end = SLLEnd(src);
		DLLSplice(src_start.current, src_end.current,
											 DLLGetPrev(dest_current.current));
	}
}
