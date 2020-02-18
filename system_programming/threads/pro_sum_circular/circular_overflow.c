/*********************************/
/*    CIRCULAR_FOR_PRO_CONS      */
/*    Author :Yoav Hattav        */
/*    Date:     17/02/2020       */
/*********************************/

#include <stdlib.h> /* malloc */ 
#include <assert.h> /* assert */ 
#include <string.h> /* memcpy */

#include "circular_overflow.h" /* USER API */

#define ZERO 0

struct CBuffer 
{
	size_t read_index;
	size_t write_index;
	size_t size;
	size_t capacity;
	int arr[1];
};

cbuffer_t *CBufferCreate(size_t capacity)
{
	cbuffer_t *new_cb = (cbuffer_t *)malloc(offsetof(cbuffer_t, arr) + (capacity * sizeof(int)));
	if (NULL == new_cb)
	{
		return NULL;
	}

	new_cb->read_index = 0;
	new_cb->size = 0;
	new_cb->capacity = capacity;

	return new_cb;
}

void CBufferDestroy(cbuffer_t *cb)
{
	assert(NULL != cb);

	free(cb);cb = NULL;
}

void *CBufferRead(cbuffer_t *cb , void *buffer)
{
	assert(NULL != buffer);
	assert(NULL != cb);

	memcpy(buffer, &cb->arr[cb->read_index], sizeof(int));
	--cb->size;
	++cb->read_index;

	if (cb->capacity == cb->read_index)
	{
		cb->read_index = ZERO;
	}

	return buffer;
}

void CBufferWrite(cbuffer_t *cb ,const void *buffer)
{
	assert(NULL != buffer);
	assert(NULL != cb);
	
	memcpy(&cb->arr[cb->write_index % cb->capacity], buffer, sizeof(int));

	++cb->write_index;
	++cb->size;
	if (cb->capacity == cb->read_index)
	{
		cb->write_index = ZERO;
	}
}

int CBufferIsEmpty(const cbuffer_t *cb)
{
	assert(NULL != cb);

	return (0 == cb->size);
}

size_t CBufferCapacity(const cbuffer_t *cb)
{
	assert(NULL != cb);

	return cb->capacity;
}

size_t CBufferFreeSpace(const cbuffer_t *cb)
{
	assert(NULL != cb);


	return (cb->capacity - cb->size);
}