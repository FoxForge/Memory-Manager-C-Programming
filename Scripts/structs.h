#ifndef __STRUCTS_H
#define __STRUCTS_H

typedef struct _BLOCK Block;
typedef struct _POOL Pool;

struct _POOL
{
	ptrdiff_t size;
	void* memory;
	Block* allocatedBlocks;
	Block* unallocatedBlocks;
};

struct _BLOCK
{
	ptrdiff_t size;
	ptrdiff_t offset;
	Pool* parent;
	Block* nextBlock;
};
#endif