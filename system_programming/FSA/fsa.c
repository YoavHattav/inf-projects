#include <stddef.h> /*size_t*/
#include <assert.h>

#include "../include/fsa.h"

#define BYTES_IN_SMALL_WORD sizeof(size_t)
#define SIZE_OF_FSA sizeof(fsa_t)
#define SIZE_OF_BLOCK_HEAD sizeof(header_block_t)
#define FACTOR_OF_ALIGNING 7
#define ONE_BYTE 1


typedef struct BlockHeader
{
	size_t next_free_index;
}header_block_t;

struct FixedSizeAllocator
{
	size_t next_available_index;
	size_t block_size;
	size_t segment_size;
};

size_t RevisedBlockSize(const size_t block_size)
{
	size_t revised_block_size = block_size;

	while (0 != (revised_block_size % BYTES_IN_SMALL_WORD))
	{
		++revised_block_size;
	}

	return revised_block_size;
}

size_t BlockCounter(fsa_t *fsa)
{
	assert(NULL != fsa);

	return  (fsa->segment_size - SIZE_OF_FSA - FACTOR_OF_ALIGNING) / (fsa->block_size + SIZE_OF_BLOCK_HEAD);
}

fsa_t *FSAInit(void *allocated, const size_t segment_size, const size_t block_size)
{
	fsa_t *new_fsa = NULL;
	char *fsa_aligner = NULL;
	header_block_t *block_header = NULL;
	size_t number_of_blocks = 0;

	assert(NULL != allocated);

	fsa_aligner = (char *)allocated;
	while (0 != (size_t)fsa_aligner % BYTES_IN_SMALL_WORD)
	{
		++fsa_aligner;
	}

	new_fsa = (fsa_t *)fsa_aligner;
	new_fsa->next_available_index = SIZE_OF_FSA + SIZE_OF_BLOCK_HEAD;
	new_fsa->block_size = RevisedBlockSize(block_size);
	new_fsa->segment_size = segment_size;

	block_header = (header_block_t *)((char *)new_fsa + SIZE_OF_FSA);
	block_header->next_free_index = new_fsa->next_available_index;
	number_of_blocks = BlockCounter(new_fsa);

	while (0 < (number_of_blocks))
	{
		block_header->next_free_index = block_header->next_free_index + new_fsa->block_size + SIZE_OF_BLOCK_HEAD;
		block_header = (header_block_t *)((char *)block_header + (SIZE_OF_BLOCK_HEAD + new_fsa->block_size));
		--number_of_blocks;
	}

	return new_fsa;
}

void *FSAAlloc(fsa_t *fsa)
{
	size_t temp_index_for_swap = 0UL;
	header_block_t *jump_to_available = NULL;

	assert(NULL != fsa);

	if (!FSACountFree(fsa))
	{
		return NULL;
	}

	temp_index_for_swap = fsa->next_available_index;
	jump_to_available = (header_block_t *)(char *)fsa + fsa->next_available_index;
	jump_to_available = (header_block_t *)(char *)(jump_to_available - SIZE_OF_BLOCK_HEAD);
	fsa->next_available_index = (size_t)jump_to_available->next_free_index;
	jump_to_available->next_free_index = temp_index_for_swap;

	return ((void *)((char *)jump_to_available + SIZE_OF_BLOCK_HEAD));
}

void FSAFree(void *block)
{
	header_block_t *new_ptr = 
	size_t temp_index =

	assert(NULL != block);

	 
}

size_t FSACountFree(const fsa_t *fsa)
{	
	header_block_t *runner = NULL;
	size_t counter_for_free = 0;
	size_t end_of_fsa = 0;

	assert(NULL != fsa);

	end_of_fsa = SIZE_OF_FSA + (BlockCounter(fsa) * (SIZE_OF_BLOCK_HEAD + fsa->block_size));

	if (fsa->next_available_index != end_of_fsa)
	{
		runner = (fsa + (header_block_t *)fsa->next_available_index);
		++counter_for_free;

		while (end_of_fsa != (size_t)((char *)runner - SIZE_OF_BLOCK_HEAD))
		{
			++counter_for_free;
			runner = (header_block_t *)runner->next_free_index;
		}
		
		return counter_for_free;
	}
	
	return 0;	
}

size_t FSASuggestSize(const size_t blocks_count, const size_t block_size)
{	
	return ((blocks_count * (RevisedBlockSize(block_size) + SIZE_OF_BLOCK_HEAD))
	                                         + SIZE_OF_FSA + FACTOR_OF_ALIGNING);
}
