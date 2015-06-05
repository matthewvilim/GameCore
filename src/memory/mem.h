/*
 * GameCore Copyright (C) 2014 Matthew Vilim
 *
 * src/shared/macros.h
 */

#ifndef MEM_H
#define MEM_H

#define MEM_ADDRESSABILITY_BYTES     1
#define MEM_SEGMENT_ADDRESS_SPACE    (1 << 16) // 64 KB
#define MEM_MASK_SEGMENT_ADDRESS     (MEM_SEGMENT_ADDRESS_SPACE - 1)
#define MEM_LINEAR_ADDRESS_SPACE     (1 << 20) // 1 MB
#define MEM_MASK_LINEAR_ADDRESS      (MEM_LINEAR_ADDRESS_SPACE - 1)

typedef struct lin_addr {
    word_t base;
    word_t offset;
} lin_addr_t;

typedef struct {
    byte_t *base;
} mem_t;

GC_INLINE void *
mem_addr_host(mem_t *mem, const lin_addr_t lin_addr) {
    return mem->base + mem_lin_addr_calc(lin_addr);
}

GC_INLINE uint32_t
mem_lin_addr_calc(const lin_addr_t lin_addr) {
    return ((lin_addr.base << 4) + lin_addr.offset) & MEM_MASK_LINEAR_ADDRESS;
}

#endif
