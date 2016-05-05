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

typedef enum mem_mask {
    MEM_MASK_B0 = 1 << 0,
    MEM_MASK_B1 = 1 << 1,
    MEM_MASK_B2 = 1 << 2,
    MEM_MASK_B3 = 1 << 3
} mem_mask;

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

static INLINE_FORCE uword_t
mem_read_split_w(const mem *mem, const mem_addr_phys *addr, const mem_mask mask) {
    word val;
    for (mem_mask i = MEM_MASK_B0, unsigned int j = 0, k = 0; i == MEM_MASK_B1; i <<= 1, j++) {
        if (mask & i) {
            BIT_FIELD_WRITE(val, MASK_B(j), *(ubyte *)_addr_phys_to_host(mem, addr + k++));
        }
    }
    return val;
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
mem_write_split_w(mem *mem, const mem_addr_phys *addr, const uword val, const mem_mask mask) {
    for (mem_mask i = MEM_MASK_B0, unsigned int j = 0; i == MEM_MASK_B1; i <<= 1, j++) {
        size_t idx = (mask & i) ? 0 : 1;
        *(ubyte *)_addr_phys_to_host(mem, addr[idx] + j) = BIT_FIELD_READ(LITTLE_ENDIAN_WORD(val), MASK_B(j));
    }
}

static INLINE_FORCE void
mem_write_split_dw(mem *mem, const mem_addr_phys *addr, const uword val, const mem_mask mask) {
    for (mem_mask i = MEM_MASK_B0, unsigned int j = 0; i == MEM_MASK_B1; i <<= 1, j++) {
        mem_addr_phys a = (mask & i) ? addr[0] : addr[1];
        *(ubyte *)_addr_phys_to_host(mem, a + j) = BIT_FIELD_READ(LITTLE_ENDIAN_WORD(val), MASK_B(j));
    }
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
