#include "pool.h"

Pool* allocatePool(ptrdiff_t n)
{
	if (n >= 0 && n < INT_MAX)
	{
		Pool* newPool = (Pool*)malloc(sizeof(Pool));
		if (newPool != NULL)
		{
			newPool->memory = malloc(sizeof(char)*n);
			if (newPool->memory)
			{
				newPool->size = n;

				/*Automatically create an unallocated block the size of the pool*/
				Block* poolFill = (Block*)malloc(sizeof(Block));
				poolFill->parent = newPool;
				poolFill->size = n;
				poolFill->offset = 0;
				poolFill->nextBlock = NULL;

				/*Set the filled Pool pointers*/
				newPool->unallocatedBlocks = poolFill;
				newPool->allocatedBlocks = NULL;
			}
			else
			{
				free(newPool);
				newPool = NULL;
			}
		}

		return newPool;
	}

	return NULL;
	
}

void freePool(Pool* pool)
{
	if (pool != NULL)
	{
		if (pool->memory != NULL)
		{
			free(pool->memory);
		}

		free(pool);
	}
	else
	{
		printf("Pool is already Free \n");
	}
}

void store(Pool* pool, ptrdiff_t offset, ptrdiff_t size, void *object)
{
	if (pool != NULL)
	{
		if (offset >= 0 && offset + size < pool->size)
		{
			memcpy((char*)pool->memory + offset, object, size);
		}
	}
}

void *retrieve(Pool* pool, ptrdiff_t offset, ptrdiff_t size)
{
	if (pool != NULL)
	{
		if (offset >= 0 && offset + size < pool->size)
		{
			return (char*)pool->memory + offset;
		}
	}

	return NULL;
}