/*
 * Game Core Copyright (C) 2014 Matthew Vilim
 *
 * src/shared/pool.h
 */

#ifndef POOL_H
#define POOL_H

typedef struct pool {
    struct list free;
    size_t size, count;
    void *buf;
} pool;

void pool_init(pool *pool, size_t size, size_t count);
void pool_term(pool *pool);

void * pool_reserve(pool *pool);
void pool_release(pool *pool, void *buf);

#endif
