/*********************************/
/*    Data Structures            */
/*    Vector                     */
/*    Author : Yoav Hattav       */
/*    Reviewed By:               */
/*    Date:      01/12/2019      */
/*                               */
/*********************************/

#include <assert.h> /* assert usage */
#include <stdlib.h> /* malloc/realloc usage */
#include <string.h> /* memmove usage */

#include "vector.h" /* USER API */

#define TIMESTWO 2
#define QUARTER 4

struct Vector{

	void* start;
	size_t size;
	size_t capacity;
	size_t element_size;
};

vector_t* VectorCreate(size_t element_size, size_t capacity)
{
	vector_t *newvector = NULL;

	if (0 == element_size || 0 == capacity)
	{
		return NULL;
	}

	newvector = (vector_t *) malloc(sizeof(vector_t));
	if (NULL == newvector)
	{
		return NULL;
	}

	newvector->start = (void *) malloc(capacity*element_size);
	if (NULL == newvector->start)
	{
		return NULL;
	}

	newvector->capacity = capacity;
	newvector->size = 0;
	newvector->element_size = element_size;

	return newvector;
}

/* This function destroy the vector */
/* Warning: the function doesn't get NULL pointer */
void VectorDestroy(vector_t* myvector)
{
	assert(NULL != myvector);

	free(myvector->start); myvector->start = NULL;
	free(myvector); myvector = NULL; 
}

/* This function push new item at the end of the vector */
/* 0 - success , 1- failure */
/* Warning: Could resize the capacity in an unpredictable manner */
/* Warning: the function doesn't get NULL pointer */
int VectorPushBack(vector_t* myvector, const void* data)
{
	assert(NULL != myvector);
	assert(NULL != data);
	
	if (myvector->capacity == myvector->size)
	{
		if (1 == VectorReserve(myvector, myvector->capacity*TIMESTWO))
		{

			return 1;
		}
	}
	
	memmove((char *)myvector->start + myvector->size * myvector->element_size, data, myvector->element_size);
	myvector->size = (char)myvector->size + 1;

	return 0;
		
}

void VectorPopBack(vector_t* myvector)
{
	assert(NULL != myvector);

	if (0 != myvector->size)
	{
		myvector->size = (char)myvector->size - 1;
		
		if ((myvector->size <= (myvector->capacity/QUARTER)))
		{
			VectorReserve(myvector, myvector->capacity-myvector->capacity/TIMESTWO);
		}
    }
}

/* This function resizing the vector size as needed with extra space */
/* 0 - success , 1- failure */
/* Warning: the function doesn't get NULL pointer */
int VectorReserve(vector_t* myvector, size_t new_capacity)
{
	assert(NULL != myvector);

	myvector->capacity = new_capacity;
	myvector->start = (void*)realloc(myvector->start, 
					(myvector->capacity*myvector->element_size));

	if(NULL == myvector->start)
	{
		return 1;
	}

	return 0;
}

/* This function return the total size of the vetor */
/* Warning: the function doesn't get NULL pointer */
size_t VectorCapacity(const vector_t* myvector)
{
	assert(NULL != myvector);

	return myvector->capacity;
}

/* This function return the current number of elements in the vetor */
/* Warning: the function doesn't get NULL pointer */
size_t VectorSize(const vector_t* myvector)
{
	assert(NULL != myvector);

	return myvector->size;
}

/* This function return specific item address to the user */
/* Warning: the address is valid until using PopBack/PushBack over the limit */
/* Warning: the function doesn't get NULL pointer */
void* VectorGetItemAddress(const vector_t* myvector, size_t position)
{
	assert(NULL != myvector);

	if (position > myvector->size || 0 == position)
	{
		return NULL;
	}
	return ((char *)myvector->start + (myvector->element_size * (position - 1)));
}
