#ifndef __POOL_H
#define __POOL_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "structs.h"
#include "block.h"

Pool* allocatePool(ptrdiff_t n);
void freePool(Pool* pool);
void store(Pool* pool, ptrdiff_t offset, ptrdiff_t size, void *object);
void *retrieve(Pool* pool, ptrdiff_t offset, ptrdiff_t size);


#endif