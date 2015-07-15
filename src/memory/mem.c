/*
 * GameCore Copyright (C) 2014 Matthew Vilim
 *
 * src/memory/memory.c
 */

#include "mem.h"

const mem_real_read = {
    .b  = _real_read_b,
    .w  = _real_read_w,
    .dw = _real_read_dw
}

const mem_real_write = {
    .b  = _real_write_b,
    .w  = _real_write_w,
    .dw = _real_write_dw
}

const mem_protected_read = {
    .b  = _protected_read_b,
    .w  = _protected_read_w,
    .dw = _protected_read_dw
}

const mem_protected_write = {
    .b  = _protected_write_b,
    .w  = _protected_write_w,
    .dw = _protected_write_dw
}

GC_INLINE void *
mem_addr16_host(mem_t *mem, const addr16_t lin_addr) {
    return mem->base + mem_addr16_calc(lin_addr);
}

GC_INLINE size_t
mem_addr16_calc(const addr16_t lin_addr) {
    return ((lin_addr.base << 4) + lin_addr.offset) & MEM_MASK_LINEAR_ADDRESS;
}



c86_status_t mem_init(mem_t *mem) {
    if (!mem) return GC_ARG_ERROR;

    mem->base = malloc(MEM_PHYS_ADDR_SPACE * MEM_ADDRESSABILITY_BYTES);

    if (!mem->base) return C86_MALLOC_ERROR;

    return GC_NO_ERROR;
}

c86_status_t mem_delete(mem_t *mem) {
    if (!mem) return GC_ARG_ERROR;

    free(mem->base);
    return GC_NO_ERROR;
}

ubyte_t
_protected_read_b(const cpu_t *cpu) {

}

uword_t
_protected_read_w(const cpu_t *cpu) {

}

udword_t
_protected_read_dw(const cpu_t *cpu) {

}

void
_protected_write_b(const cpu_t *cpu, const ubyte_t val) {

}

void
_protected_write_w(const cpu_t *cpu, const uword_t val) {

}

void
_protected_write_dw(const cpu_t *cpu, const udword_t val) {

}

ubyte_t
_real_read_b(const cpu_t *cpu) {

}

uword_t
_real_read_w(const cpu_t *cpu) {

}

udword_t
_real_read_dw(const cpu_t *cpu) {

}

void
_real_write_b(const cpu_t *cpu, const ubyte_t val) {

}

void
_real_write_w(const cpu_t *cpu, const uword_t val) {

}

void
_real_write_dw(const cpu_t *cpu, const udword_t val) {

}
