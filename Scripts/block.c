#include "block.h"

/*Best Fit Algorithm*/
Block* allocate(Pool* pool, ptrdiff_t size)
{
	if (pool != NULL)
	{
		if (size >= 0 && size <= pool->size)
		{
			ptrdiff_t sorted = 0;
			Block* stepBlock = pool->unallocatedBlocks;
			Block* chosenBlock = NULL;

			/*If we have not already sorted the pool then attempt to find space for the block*/
			while (sorted < 2)
			{
				while (stepBlock != NULL)
				{
					if (stepBlock->size >= size)
					{
						if (chosenBlock != NULL)
						{
							/*We find the block closest to the size wanted*/
							if (stepBlock->size < chosenBlock->size)
							{
								chosenBlock = stepBlock;
							}
						}
						else
						{
							chosenBlock = stepBlock;
						}
					}
					
					/*Cycle through all unallocated blocks*/
					stepBlock = stepBlock->nextBlock;
				}

				/*If we have found a block which fits then create at the chosenBlock*/
				if (chosenBlock != NULL)
				{
					Block* newBlock = (Block*)malloc(sizeof(Block));
					newBlock->parent = pool;
					newBlock->size = size;
					newBlock->offset = chosenBlock->offset;

					/*The next block will always point to the last created block irrelevant of order*/
					newBlock->nextBlock = pool->allocatedBlocks;
					pool->allocatedBlocks = newBlock;

					chosenBlock->size = chosenBlock->size - size;
					chosenBlock->offset = chosenBlock->offset + size;
					return newBlock;
				}
				else
				{
					/*We have not found block to fit and must re-order the pool in an attempt to find one*/
					if (sorted < 1)
					{
						printf("\tPool has been sorted...\n");
						SortBlocks(pool);
						stepBlock = pool->unallocatedBlocks;
						sorted++;
					}
					else
					{
						printf("\tNo Blocks have been Found After Sorting\n");
						sorted++;
					}
					
				}
			}

			/*We cannot find a block with enough space even after sorting the pool*/
			return NULL;
		}
		else
		{
			printf("\tYou have not entered a valid number for a block size\n");
		}
	}

	/*If no space can be found OR pool doesnt exist due to unseen circumstances then return NULL*/
	return NULL;
}

/*First Fit Algorithm*/
Block* allocateFirstFit(Pool* pool, ptrdiff_t size)
{
	if (pool != NULL)
	{
		if (size >= 0 && size <= pool->size)
		{
			ptrdiff_t sorted = 0;
			Block* stepBlock = pool->unallocatedBlocks;
			Block* chosenBlock = NULL;

			/*Cycle through all unallocated blocks*/
			while (stepBlock != NULL)
			{
				if (stepBlock->size >= size)
				{
					/*Create a block here as it will fit*/
					Block* newBlock = (Block*)malloc(sizeof(Block));
					newBlock->parent = pool;
					newBlock->size = size;
					newBlock->offset = stepBlock->offset;

					/*The next block will always point to the last created block irrelevant of order*/
					newBlock->nextBlock = pool->allocatedBlocks;
					pool->allocatedBlocks = newBlock;

					stepBlock->size = stepBlock->size - size;
					stepBlock->offset = stepBlock->offset + size;
					return newBlock;
				}
				else
				{
					/*Step through the blocks*/
					if (stepBlock->nextBlock != NULL)
					{
						stepBlock = stepBlock->nextBlock;
					}
					else
					{
						/*If we have not already sorted the pool then sort the pool*/
						if (sorted < 1)
						{
							printf("\tPool has been sorted...\n");
							SortBlocks(pool);
							stepBlock = pool->unallocatedBlocks;
							sorted++;
						}
						else
						{
							/*We have sorted the pool and still cannot find space*/
							printf("\tNo Blocks have been Found After Sorting\n");
							return NULL;
						}
					}
				}
			}
		}
		else
		{
			printf("\tYou have not entered a valid number for a block size\n");
		}
	}

	/*If no space can be found OR pool doesnt exist due to unseen circumstances then return NULL*/
	return NULL;
}

/*Worst Fit Algorithm*/
Block* allocateWorstFit(Pool* pool, ptrdiff_t size)
{
	if (pool != NULL)
	{
		if (size >= 0 && size <= pool->size)
		{
			ptrdiff_t sorted = 0;
			Block* stepBlock = pool->unallocatedBlocks;
			Block* chosenBlock = NULL;

			/*If we have not already sorted the pool then attempt to find space for the block*/
			while (sorted < 2)
			{
				while (stepBlock != NULL)
				{
					if (stepBlock->size >= size)
					{
						if (chosenBlock != NULL)
						{
							/*We find the biggest unallocated block within the pool still provided it fits the size*/
							if (stepBlock->size > chosenBlock->size)
							{
								chosenBlock = stepBlock;
							}
						}
						else
						{
							chosenBlock = stepBlock;
						}
					}

					/*Cycle through all unallocated blocks*/
					stepBlock = stepBlock->nextBlock;
				}

				/*If we have found a block which fits then create at the chosenBlock*/
				if (chosenBlock != NULL)
				{
					Block* newBlock = (Block*)malloc(sizeof(Block));
					newBlock->parent = pool;
					newBlock->size = size;
					newBlock->offset = chosenBlock->offset;

					/*The next block will always point to the last created block irrelevant of order*/
					newBlock->nextBlock = pool->allocatedBlocks;
					pool->allocatedBlocks = newBlock;

					chosenBlock->size = chosenBlock->size - size;
					chosenBlock->offset = chosenBlock->offset + size;
					return newBlock;
				}
				else
				{
					if (sorted < 1)
					{
						/*We have not found block to fit and must re-order the pool in an attempt to find one*/
						printf("\tPool has been sorted...\n");
						SortBlocks(pool);
						stepBlock = pool->unallocatedBlocks;
						sorted++;
					}
					else
					{
						printf("\tNo Blocks have been Found After Sorting\n");
						sorted++;
					}
				}
			}

			/*We cannot find a block with enough space even after sorting the pool*/
			return NULL;
		}
		else
		{
			printf("\tYou have not entered a valid number for a block size\n");
		}
	}

	/*If no space can be found OR pool doesnt exist due to unseen circumstances then return NULL*/
	return NULL;
}

void write(Block* block, void *object, ptrdiff_t objectSize, ptrdiff_t offsetInBlock)
{
	if (block != NULL)
	{
		if (offsetInBlock >= 0 && offsetInBlock + objectSize < block->size)
		{
			memcpy((char*)block->parent->memory + block->offset + offsetInBlock, object, objectSize);
		}
	}
}

void* read(Block* block, ptrdiff_t objectSize, ptrdiff_t offsetInBlock)
{
	if (block != NULL)
	{
		if (offsetInBlock >= 0 && offsetInBlock + objectSize < block->size)
		{
			return (char*)block->parent->memory + block->offset + offsetInBlock;
		}
	}

	return NULL;
}

void SortBlocks(Pool* pool)
{
	if (pool != NULL)
	{
		Block* lastBlock = pool->unallocatedBlocks;

		/*Provided there are more than 1 unallocated blocks then we can merge blocks*/
		if (lastBlock->nextBlock != NULL)
		{
			/*Find the last block as will accumulate the free space here*/
			while (lastBlock->nextBlock != NULL)
			{
				lastBlock = lastBlock->nextBlock;
			}

			Block* thisBlock = pool->unallocatedBlocks;
			Block* stepBlock = pool->allocatedBlocks;

			while (thisBlock != lastBlock)
			{
				/*Move all allocated blocks back in their offset by this blocks size*/
				while (stepBlock != NULL)
				{
					if (stepBlock->offset >= thisBlock->offset + thisBlock->size)
					{
						stepBlock->offset = stepBlock->offset - thisBlock->size;
					}

					/*Cycle through allocated blocks checking each one*/
					stepBlock = stepBlock->nextBlock;
				}

				/*Reset the step Block back to start*/
				stepBlock = pool->allocatedBlocks;

				/*Increase the last unallocated block by this block's size and move it back too*/
				lastBlock->offset = lastBlock->offset - thisBlock->offset;
				lastBlock->size = lastBlock->size + thisBlock->size;

				/*Free the block from memory*/
				Block* blockToFree = thisBlock;
				thisBlock = thisBlock->nextBlock;
				blockToFree = NULL;
				free(blockToFree);
			}
		}
	}
}

void deallocate(Block* block)
{
	if (block != NULL && block->parent != NULL)
	{
		/*Check the block has not already been deallocated*/
		Block* alCheck = block->parent->unallocatedBlocks;
		while (alCheck != NULL)
		{
			if (block != alCheck)
			{
				alCheck = alCheck->nextBlock;
			}
			else
			{
				return;
			}
		}

		/*Move the next block chain along to take out this particular block from the sequence - move the next block pointers to the next block's next block*/
		Block* stepBlock = block->parent->allocatedBlocks;
		if (stepBlock != block)
		{
			while (stepBlock->nextBlock != NULL)
			{
				if (stepBlock->nextBlock != block)
				{
					/*Keep cycling through*/
					stepBlock = stepBlock->nextBlock;
				}
				else
				{
					/*Set the next block to the next block's next block*/
					stepBlock->nextBlock = stepBlock->nextBlock->nextBlock;
				}
			}
		}
		else
		{
			/*If it is the last placed block then we need to move the pointer to the next block*/
			block->parent->allocatedBlocks = block->parent->allocatedBlocks->nextBlock;
		}

		/*Chain the unallocated blocks irrespective of order*/
		block->nextBlock = block->parent->unallocatedBlocks;
		block->parent->unallocatedBlocks = block;
	}
	else
	{
		printf("\tThe Block to deallocate does not exist\n");
	}
}
