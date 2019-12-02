int VectorPushBack(vector_t* myvector, const void* data)
{
	assert(NULL != myvector);

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
int VectorPushBack(vector_t* myvector, const void* data)
{
	assert(NULL != myvector);

	if (myvector->capacity == myvector->size)
	{
		if (0 == VectorReserve(myvector, myvector->capacity*TIMESTWO))
		{
			memmove((char *)myvector->start + myvector->size * myvector->element_size, data, myvector->element_size);
			myvector->size = /*(char *)*/myvector->size + 1;

			return 0;
		}
		else
		{
			return 1;
		}
	}

	else
	{
		memmove((char *)myvector->start + myvector->size * myvector->element_size, data, myvector->element_size);
		myvector->size = (char)myvector->size + 1;

		return 0;
	}	
}