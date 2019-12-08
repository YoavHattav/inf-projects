/*********************************/
/*    Data Structures            */
/*    Bits Array                 */
/*    Author :Yoav Hattav        */
/*    Reviewed By: Shye Shapira  */
/*    Date:     26/11/2019       */
/*********************************/
#include <assert.h> /* assert */ 
#include <stdlib.h> /* malloc */ 
#include <string.h> /* memcpy */
#include <sys/types.h> /* ssize_t */

#include "circularbuffer.h" /* USER API */

typedef char byte_t;

#define OFFSET(type, member) offsetof(type, member)
#define ZERO 0
#define FREE(x) free(x); x = NULL;

struct CBuffer 
{
	size_t read_index;
	size_t size;
	size_t capacity;
	byte_t arr[1];
};

cbuffer_t *CBufferCreate(size_t capacity)
{
	cbuffer_t *new_cb = (cbuffer_t *)malloc(OFFSET(cbuffer_t, arr)+capacity);
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

	FREE(cb);
}

ssize_t CBufferRead(cbuffer_t *cb , void *buffer, size_t count)
{
	void *run_buff = NULL;
	size_t count_return;

	assert(NULL != buffer);
	assert(NULL != cb);
	
	count_return = count;
	run_buff = buffer;

	if (count > cb->size)
	{
		count = cb->size;
		count_return = cb->size;	
	}

	if (cb->capacity < (count + cb->read_index))
	{
		memcpy(run_buff, &cb->arr[cb->read_index % cb->capacity], cb->capacity - cb->read_index);
		count -= (cb->capacity - cb->read_index);
		run_buff = (byte_t *)run_buff + cb->capacity - cb->read_index;
		cb->read_index = ZERO;
	}
	
	memcpy(run_buff, &cb->arr[cb->read_index], count);
	cb->size -= count_return;
	cb->read_index += count;

	return count_return;
}

ssize_t CBufferWrite(cbuffer_t *cb ,const void *buffer, size_t count)
{
	const void *run_buff = NULL;
	size_t count_return;
	size_t write_index = (cb->read_index + cb->size) % cb->capacity;

	assert(NULL != buffer);
	assert(NULL != cb);

	count_return = count;
	run_buff = buffer;

	if ((cb->capacity - cb->size) < count)
	{
		count = cb->capacity - cb->size;
		count_return = cb->capacity - cb->size;
	}

	if (cb->capacity < (count + write_index))
	{
		memcpy(&cb->arr[cb->read_index + cb->size], run_buff, cb->capacity - write_index);
		count -= cb->capacity - write_index;
		run_buff = (byte_t *)run_buff + cb->capacity - write_index;
		cb->size -= (cb->capacity - write_index);
		write_index = ZERO;
	}
	
	memcpy(&cb->arr[write_index], run_buff, count);
	cb->size += count;
	
	return count_return;
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