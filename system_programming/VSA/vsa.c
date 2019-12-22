/*********************************/
/*   System Programming          */
/*   vsa                         */
/*   Yoav Hattav                 */
/*   Last Updated 19/12/19       */
/*   Reviewed by: Itay           */   
/*********************************/

#include <stddef.h>	/*size_t*/
#include <assert.h> /* assert */
#include <stdio.h> /*sizeof*/

#include "vsa.h" /* priority functions */

#define MAGIC_NUMBER 0xDEADBEEF
#define LAST_HEADER_SIZE 0xFFFFFFFFFFFFFFFF

struct BlockHeader
{
	long block_size;

	#ifndef NDEBUG
    long magic_num;
    #endif
};

typedef struct BlockHeader block_header_t;

vsa_t *VSAInit(void *allocated, size_t segment_size)
{
	vsa_t *runner_start = NULL;
	vsa_t *runner_end = NULL;


	assert(NULL != allocated);

	runner_start = (vsa_t *)allocated;
	runner_end = (vsa_t *)((char *)allocated + (segment_size - sizeof(vsa_t)));

	runner_start->block_size = segment_size - (sizeof(vsa_t) * 2);
	runner_end->block_size = (long)LAST_HEADER_SIZE;

	#ifndef NDEBUG
    runner_start->magic_num = MAGIC_NUMBER;
    runner_end->magic_num = MAGIC_NUMBER;
    #endif

    return runner_start;
}

void VSAFree(void *block)
{
	assert(NULL != block);
    
    assert(MAGIC_NUMBER == ((vsa_t *)((char *)block 
    									- sizeof(block_header_t)))->magic_num);
    
    ((vsa_t *)((char *)block - sizeof(block_header_t)))->block_size *= -1;
}

static void BlockDefragmentation(vsa_t *header)
{
	block_header_t *defrag_runner = NULL;

	assert(NULL != header);

	defrag_runner = header;

	if(((block_header_t *)((char *)header + header->block_size + sizeof(vsa_t)))
										->block_size != (long)LAST_HEADER_SIZE)
	{
		defrag_runner = ((block_header_t *)((char *)header + 
										header->block_size + sizeof(vsa_t)));
	
		while ((0 <= defrag_runner->block_size) && (defrag_runner->block_size
													 != (long)LAST_HEADER_SIZE))
		{
			header->block_size += defrag_runner->block_size + sizeof(vsa_t);
			defrag_runner = (block_header_t *)((char *)defrag_runner + 
									defrag_runner->block_size + sizeof(vsa_t));
		}
	}
}


void *VSAAlloc(vsa_t *vsa, size_t block_size)
{
	block_header_t *alloc_runner = NULL;
	block_header_t *alloc_base = NULL;

	size_t t_new_block_size = 0;

	assert(NULL != vsa);

	alloc_runner = vsa;

    while (alloc_runner->block_size != (long)LAST_HEADER_SIZE)
    {
    	t_new_block_size = 0;

    	if(0 > alloc_runner->block_size)
    	{
    		alloc_runner = (block_header_t *)((char *)alloc_runner + 
    						(alloc_runner->block_size * -1) + sizeof(vsa_t));

    		continue;
    	}

		BlockDefragmentation(alloc_runner);

    	if(alloc_runner->block_size >= (long)(block_size + sizeof(vsa_t)))
    	{
    		alloc_base = (block_header_t *)((char *)alloc_runner + sizeof(vsa_t));
    		t_new_block_size = alloc_runner->block_size;
    		alloc_runner->block_size = block_size * -1;
    		alloc_runner = (block_header_t *)((char *)alloc_runner + 
    												block_size + sizeof(vsa_t));
    		alloc_runner->block_size = t_new_block_size - sizeof(vsa_t) - 
    																block_size;

    		#ifndef NDEBUG
    			alloc_runner->magic_num = MAGIC_NUMBER;
    		#endif

    		return alloc_base;
    	}

    	alloc_runner = (block_header_t *)((char *)alloc_runner + sizeof(vsa_t) +
    											 (alloc_runner->block_size));
    }

	return NULL;
}


size_t VSALargestChunkSize(vsa_t *vsa)
{
	size_t largest_chunk = 0;
	block_header_t *chunk_runner = NULL;

	assert(NULL != vsa);

	chunk_runner = vsa;

	while (chunk_runner->block_size != (long)LAST_HEADER_SIZE)
	{
		if(0 > chunk_runner->block_size)
    	{
    		chunk_runner = (block_header_t *)((char *)chunk_runner +
							   (chunk_runner->block_size * -1) + sizeof(vsa_t));

    		continue;
    	}

    	BlockDefragmentation(chunk_runner);

    	if ((long)largest_chunk < chunk_runner->block_size)
    	{
    		largest_chunk = chunk_runner->block_size;
    	}

    	chunk_runner = (block_header_t *)((char *)chunk_runner + sizeof(vsa_t) +
    											 (chunk_runner->block_size));
	}

	return (largest_chunk - sizeof(vsa_t));
}