/*
 * GameCore Copyright (C) 2014 Matthew Vilim
 *
 * src/shared/macros.h
 */

#ifndef MEM_H
#define MEM_H

typedef struct mem mem;

typedef dword mem_addr_phys;

struct mem_conf {
    size_t size;
};

typedef struct mem {
    void *host;
    size_t size;
} mem;

enum mem_mask {
    MEM_MASK_B0 = 1 << 0,
    MEM_MASK_B1 = 1 << 1,
    MEM_MASK_B2 = 1 << 2,
    MEM_MASK_B3 = 1 << 3
};

gc_error mem_init(mem *mem, mem_conf *conf);
void mem_alloc_block(mem *mem, const size index);

#endif
