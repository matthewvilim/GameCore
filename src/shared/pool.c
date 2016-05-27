/*
 * Game Core Copyright (C) 2014 Matthew Vilim
 *
 * src/shared/pool.c
 */

#include "pool.h"

#include "list.h"

void
pool_init(pool *pool, size_t size, size_t count) {
    list_init(&pool->list);

    pool->size = max(sizeof(list_node), size);
    pool->count = count;

    pool->buf = malloc(pool->size * pool->count);

    struct list_iter iter;
    list_head(&pool->list, &iter);
    for (size_t i = 0; i < pool->count; i++) {
        list_iter_append(iter, pool->buf + (i * pool->size));
    }
}

void
pool_term(pool *pool) {
    free(pool->buf);
}

void *
pool_reserve(pool *pool) {
    struct list_iter iter;
    list_head(&pool->list, &iter);
    list_iter_remove(&iter);
    return iter->node;
}

void
pool_release(pool *pool, void *buf) {
    struct list_iter iter;
    list_tail(&pool->list, &iter);
    list_iter_append(&iter, buf);
}
