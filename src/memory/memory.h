/*
 * GameCore Copyright (C) 2014 Matthew Vilim
 *
 * src/shared/macros.h
 */

#ifndef MEMORY_H
#define MEMORY_H

#define MEM_ADDRESSABILITY_BYTES     1
#define MEM_SEGMENT_ADDRESS_SPACE    (1 << 16) // 64 KB
#define MEM_MASK_SEGMENT_ADDRESS     (MEM_SEGMENT_ADDRESS_SPACE - 1)
#define MEM_LINEAR_ADDRESS_SPACE     (1 << 20) // 1 MB
#define MEM_MASK_LINEAR_ADDRESS      (MEM_LINEAR_ADDRESS_SPACE - 1)

// 8086 uses a 20 bit address bus
typedef uint32_t lin_addr_t;

typedef struct {
    void *base;
} mem_t;

GC_INLINE void *
mem_host_addr_calc(mem_t *mem, lin_addr_t lin_addr) {
    return (byte_t *)mem->base + lin_addr;
}

GC_INLINE byte_t
mem_readb(mem_t *mem, lin_addr_t addr) {
    return *(byte *)mem_host_addr_calc(mem, addr);
}

GC_INLINE word_t
mem_readw(mem_t *mem, lin_addr_t addr) {
    return *(word_t *)mem_host_addr_calc(mem, addr);
}

GC_INLINE void
mem_writeb(mem_t *mem, lin_addr_t addr, byte_t val) {
    *(byte_t *)mem_host_addr_calc(mem, addr)) = val;
}

GC_INLINE void
mem_writew(mem_t *mem, lin_addr_t addr, word_t val) {
    *(word_t *)mem_host_addr_calc(mem, addr) = val;
}

GC_INLINE lin_addr_t
mem_lin_addr_calc(word_t base, word_t offset) {
    return ((((lin_addr_t)base) << 4) + offset) & MEM_MASK_PHYS_ADDRESS;
}

#endif