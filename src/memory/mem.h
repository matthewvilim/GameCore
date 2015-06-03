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

// 8086 uses a 20 bit address bus
typedef uint32_t lin_addr_calc_t;

typedef struct lin_addr {
    word_t base;
    word_t offset;
} lin_addr_t;

typedef struct {
    void *base;
} mem_t;

GC_INLINE void *
mem_host_addr_calc(mem_t *mem, const lin_addr_t lin_addr) {
    return (byte_t *)mem->base + mem_lin_addr_calc(lin_addr);
}

GC_INLINE byte_t
mem_read_b(const mem_t *mem, const lin_addr_t addr) {
    return *(byte *)mem_host_addr_calc(mem, addr);
}

GC_INLINE word_t
mem_read_w(const mem_t *mem, const lin_addr_t addr) {
    return ENDIAN_CONV_WORD(*(word_t *)mem_host_addr_calc(mem, addr));
}

GC_INLINE void
mem_write_b(mem_t *mem, const lin_addr_t addr, const byte_t val) {
    *(byte_t *)mem_host_addr_calc(mem, addr)) = val;
}

GC_INLINE void
mem_write_w(mem_t *mem, const lin_addr_t addr, const word_t val) {
    *(word_t *)mem_host_addr_calc(mem, addr) = ENDIAN_CONV_WORD(val);
}

GC_INLINE lin_addr_calc_t
mem_lin_addr_calc(const lin_addr_t lin_addr) {
    return ((((lin_addr_calc_t)lin_addr.base) << 4) + lin_addr.offset) & MEM_MASK_PHYS_ADDRESS;
}

#endif
