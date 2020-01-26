/*********************************/
/*   Hash                        */
/*   Yoav Hattav                 */
/*   Last Updated 22/01/20       */
/*   Reviewed by: Yonatan        */
/*********************************/

#include <stdlib.h> /* malloc */
#include <assert.h> /* assert */

#include "../include/dll.h"
#include "../include/hash.h"

#define FALSE 0
#define TRUE 1
#define SUCC 0
#define FAIL 1
#define START 1

struct Hash
{
	size_t table_size;
	match_func_t is_match;
	hash_func_t hash_func;
	dll_t *table[START];
};

static dll_t *GetDll(const hash_t *table, const void *data)
{
	return (table->table[table->hash_func(data) % table->table_size]);
}

static int DllsInit(hash_t *hash_table)
{
	int i = 0;

	for (i = 0; i < hash_table->table_size; ++i)
	{
		hash_table->table[i] = DLLCreate();

		if (NULL == hash_table->table[i])
		{
			for (--i; i >= 0; --i)
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
	if (NULL == hash_table)
	{
		return NULL;
	}

	hash_table->table_size = table_size;
	hash_table->is_match = is_match;
	hash_table->hash_func = hash_func;

	if (1 == DllsInit(hash_table))
	{
		free(hash_table);hash_table = NULL;
	}
	return hash_table;
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

	temp_dll_t = GetDll(hash_table, data);

	if (DLLIsSameIter(DLLEnd(temp_dll_t), DLLPushFront(temp_dll_t, data)))
	{
		return FAIL;
	}

	return SUCC;
}

void HashRemove(hash_t *hash_table, const void *data)
{
	dll_t *table_dll = NULL;

	assert(NULL != hash_table);
	assert(NULL != data);

	table_dll = GetDll(hash_table, data);

	DLLRemove(DLLFind(
			 DLLBegin(table_dll),
			 DLLEnd(table_dll),
			 hash_table->is_match, (void *)data));

}

void *HashFind(const hash_t *hash_table, const void *data)
{	
	void *found = NULL;
	dll_t *table_dll = NULL;

	assert(NULL != hash_table);

	table_dll = GetDll(hash_table, data);

	found = DLLGetData(DLLFind(
			 DLLBegin(table_dll),
			 DLLEnd(table_dll),
			 hash_table->is_match, (void *)data));
	if (NULL != found)
	{
		HashRemove((hash_t *)hash_table, found);
		HashInsert((hash_t *)hash_table, found);
	}

	return found;
}

int HashForeach(hash_t *hash_table, action_func_t action, void *param)
{
	int i = 0;
	size_t size = 0;

	assert(NULL != hash_table);

	size = hash_table->table_size;

	for (i = 0; i < size; i++)
	{
		 
		if (1 == DLLForEach(DLLBegin(hash_table->table[i]),
		DLLEnd(hash_table->table[i]), action, param))
		{
			return FAIL;
		}
	}

	return SUCC;
}

size_t HashSize(const hash_t *hash_table)
{
	int i = 0;
	size_t size = 0;
	size_t table_size = 0;

	assert(NULL != hash_table);

	table_size = hash_table->table_size;

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
	size_t table_size = 0;

	assert(NULL != hash_table);

	table_size = hash_table->table_size;

	for (i = 0; i < hash_table->table_size; i++)
	{
		empty_flag += DLLIsEmpty(hash_table->table[i]);
	}

	return (empty_flag == hash_table->table_size) ? TRUE : FALSE;
}

