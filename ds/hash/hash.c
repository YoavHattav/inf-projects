#include <stdlib.h> /* malloc */
#include <assert.h> /* assert */

#include "../include/dll.h"
#include "../include/hash.h"

#define FALSE 0
#define TRUE 1
#define SUCC 0
#define FAIL 1

struct Hash
{
	size_t table_size;
	match_func_t is_match;
	hash_func_t hash_func;
	dll_t *table[1];
};

static int DllsInit(hash_t *hash_table)
{
	int i = 0;

	for (i = 0; i < hash_table->table_size; ++i)
	{
		hash_table->table[i] = DLLCreate();

		if (NULL == hash_table->table[i])
		{
			for (;i >= 0; --i)
			{
				DLLDestroy(hash_table->table[i]);
			}

			return FAIL;
		}
	}

	return SUCC;
}

hash_t *
HashCreate(size_t table_size, hash_func_t hash_func, match_func_t is_match)
{
	hash_t *hash_table = NULL;

	assert(NULL != hash_func);
	assert(NULL != is_match);

	hash_table = malloc(offsetof(hash_t, table) + table_size * sizeof(dll_t *));
	if (NULL != hash_table)
	{
		return NULL;
	}

	hash_table->table_size = table_size;
	hash_table->is_match = is_match;
	hash_table->hash_func = hash_func;

	return (!DllsInit(hash_table)) ? NULL : hash_table;
}

void HashDestroy(hash_t *hash_table)
{
	int i = 0;

	assert(NULL != hash_table);

	for (i = 0; i < hash_table->table_size; ++i)
	{
		DLLDestroy(hash_table->table[i]);
	}

	free(hash_table);hash_table = NULL;
}

int HashInsert(hash_t *hash_table, void *data)
{
	dll_t *temp_dll_t = NULL; 
	
	assert(NULL != hash_table);
	assert(NULL != data);

	temp_dll_t = hash_table->table[hash_table->hash_func(data)];

	if (DLLIsSameIter(DLLEnd(temp_dll_t), DLLPushFront(temp_dll_t, data)))
	{
		return FAIL;
	}

	return SUCC;
}

void HashRemove(hash_t *hash_table, const void *data)
{
	assert(NULL != hash_table);
	assert(NULL != data);

	DLLRemove(DLLFind(DLLBegin(hash_table->table[hash_table->hash_func(data)]),
			 DLLEnd(hash_table->table[hash_table->hash_func(data)]),
			 hash_table->is_match, (void *)data));

}

void *HashFind(const hash_t *hash_table, const void *data)
{
	int i = 0;
	void *found_data = NULL;
	
	assert(NULL != hash_table);
	
	return DLLGetData(DLLFind(
			 DLLBegin(hash_table->table[hash_table->hash_func(data)]),
			 DLLEnd(hash_table->table[hash_table->hash_func(data)]),
			 hash_table->is_match, (void *)data));

}

int HashForeach(hash_t *hash_table, action_func_t action, void *param)
{
	int i = 0;
	size_t succ_flag = 0;
	
	assert(NULL != hash_table);

	for (i = 0; i < hash_table->table_size; i++)
	{
		succ_flag += 
		DLLForEach(DLLBegin(hash_table->table[i]),
		DLLEnd(hash_table->table[i]), action, param);
	}

	return (succ_flag == 0) ? TRUE : FALSE;
}

size_t HashSize(const hash_t *hash_table)
{
	int i = 0;
	size_t size = 0;

	assert(NULL != hash_table);

	for (i = 0; i < hash_table->table_size; i++)
	{
		size += DLLSize(hash_table->table[i]);
	}

	return size;
}

int HashIsEmpty(const hash_t *hash_table)
{
	int i = 0;
	size_t empty_flag = 0;

	assert(NULL != hash_table);

	for (i = 0; i < hash_table->table_size; i++)
	{
		empty_flag += DLLIsEmpty(hash_table->table[i]);
	}

	return (empty_flag == 0) ? TRUE : FALSE;
}

