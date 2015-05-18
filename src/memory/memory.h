/*
 * Core 8086 Copyright (C) 2014 Matthew Vilim
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

typedef uint8_t byte_t;
typedef uint16_t word_t;
typedef uint32_t dword_t;

typedef struct {
    uint8_t *base;
} mem_t;

static inline uint8_t mem_read_b(mem_t *mem, dword_t addr) {
    return *(mem->base + addr);
}

static inline uint16_t mem_read_w(mem_t *mem, dword_t addr) {
    return *(uint16_t *)(base + addr);
}

static inline void mem_write_b(mem_t *mem, dword_t addr, uint8_t val) {
    return *(base + addr) = val;
}

static inline void mem_write_w(mem_t *mem, dword_t addr, uint16_t val) {
    *(uint16_t *)(base + addr) = val;
}

static inline linear_addr_t mem_calc_linear_addr(seg_addr_t base, seg_addr_t offset) C86_INLINE {
    return ((((linear_addr_t)base) << 4) + offset) & MEM_MASK_PHYS_ADDRESS;
}

#endif