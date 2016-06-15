#ifndef __BLOCK_H
#define __BLOCK_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "structs.h"
#include "pool.h"

Block* allocate(Pool* pool, ptrdiff_t size);
void write(Block* block, void *object, ptrdiff_t objectSize, ptrdiff_t offsetInBlock);
void* read(Block* block, ptrdiff_t objectSize, ptrdiff_t offsetInBlock);
void deallocate(Block* block);

void SortBlocks(Pool* pool);
Block* allocateFirstFit(Pool* pool, ptrdiff_t size);
Block* allocateWorstFit(Pool* pool, ptrdiff_t size);

#endif