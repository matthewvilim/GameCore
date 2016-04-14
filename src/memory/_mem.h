/*
 * GameCore Copyright (C) 2014 Matthew Vilim
 *
 * src/mem/mem_c.h
 */

#ifndef _MEM_H
#define _MEM_H

typedef dword mem_addr_phys;

typedef struct mem_conf {
    size_t size;
} mem_conf;

typedef struct mem {
    void *host;
    size_t size;
} mem;

static INLINE_FORCE void *
_addr_phys_to_host(const mem *mem, const mem_addr_phys addr) {
    assert(addr < mem->size);
    return (ubyte *)mem->host + addr;
}

static INLINE_FORCE ubyte_t
mem_read_b(const mem *mem, const mem_addr_phys addr) {
    return *(ubyte *)_addr_phys_to_host(mem, addr);
}

static INLINE_FORCE uword_t
mem_read_w(const mem *mem, const mem_addr_phys addr) {
    return LITTLE_ENDIAN_WORD(*(uword *)_addr_phys_to_host(mem, addr);
}

static INLINE_FORCE udword_t
mem_read_dw(const mem *mem, const mem_addr_phys addr) {
    return LITTLE_ENDIAN_DWORD(*(udword *)_addr_phys_to_host(mem, addr));
}

static INLINE_FORCE void
mem_write_b(mem *mem, const mem_addr_phys addr, const ubyte val) {
    *(ubyte *)_addr_phys_to_host(mem, addr) = val;
}

static INLINE_FORCE void
mem_write_w(mem *mem, const mem_addr_phys addr, const uword val) {
    *(uword *)_addr_phys_to_host(mem, addr) = LITTLE_ENDIAN_WORD(val);
}

static INLINE_FORCE void
mem_write_dw(mem *mem, const mem_addr_phys addr, const udword val) {
    *(udword *)_addr_phys_to_host(mem, addr) = LITTLE_ENDIAN_DWORD(val);
}

static INLINE_FORCE void
mem_read(const mem *mem, const mem_addr_phys addr, void *buf, const size_t n) {
    memcpy(buf, _addr_phys_to_host(mem, addr), n);
}

static INLINE_FORCE void
mem_write(mem *mem, const mem_addr_phys addr, const void *buf, const size_t n) {
    memcpy(_addr_phys_to_host(mem, addr), buf, n);
}

#endif MEM_C_H
