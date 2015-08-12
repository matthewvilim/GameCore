/*
 * Game Core Copyright (C) 2014 Matthew Vilim
 *
 * src/shared/pool.c
 */

#include "pool.h"

typedef struct _block {
    struct _block *next;
    char data[];
} _block_t;

typedef struct pool {
    int block_size, count;
    _block_t *head;
    _block_t *tail;
} pool_t;

void
pool_init(pool_t *pool, int block_size, int count) {
    ASSERT(pool);

    pool->block_size = block_size;
    pool->count = count;

    pool->head = malloc((sizeof(_block_t) + pool->block_size) * pool->count);
}
