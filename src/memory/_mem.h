/*
 * GameCore Copyright (C) 2014 Matthew Vilim
 *
 * src/mem/mem_c.h
 */

#ifndef _MEM_H
#define _MEM_H

#define MEM_BLOCK_SIZE_BYTES_LOG2     MBYTES_LOG2(0)
#define MEM_BLOCK_SIZE_BYTES          BIT(MEM_BLOCK_SIZE_LOG2)
#define MEM_BLOCK_SIZE_MBYTES_LOG2   (MEM_BLOCK_SIZE_BYTES_LOG2 - MBYTES_LOG2(0))
#define MEM_BLOCK_SIZE_MBYTES         BIT(MEM_BLOCK_SIZE_MBYTES_LOG2)

#define MEM_BLOCK_TABLE_INDEX_MASK    MASK_RANGE(X86_MEM_PHYS_BUS_SIZE_80386 - 1, MEM_BLOCK_SIZE_LOG2)
#define MEM_BLOCK_INDEX_MASK          MASK_RANGE(MEM_BLOCK_SIZE_LOG2 - 1, 0)

typedef dword_t mem_addr_phys_t;

typedef struct mem_conf {
    size_t size_mb;
} mem_conf_t;

typedef struct mem {
    void **block_table;
    size_t size;


} mem_t;

static INLINE_FORCE void *
_addr_phys_to_host(mem_t *mem, const mem_addr_phys_t addr) {
    size_t table_index = BIT_FIELD_READ(addr, MEM_BLOCK_TABLE_INDEX_MASK);
    size_t block_index = BIT_FIELD_READ(addr, MEM_BLOCK_INDEX_MASK);
    void **block = mem->block_table + table_index;
    if (UNLIKELY(!*block)) {
        mem_alloc_block(mem, table_index);
    }
    return (ubyte_t *)*block + block_index;
}

static INLINE_FORCE ubyte_t
mem_read_b(mem_t *mem, const mem_addr_phys_t addr) {
    return *(ubyte_t *)_addr_phys_to_host(mem, addr);
}

static INLINE_FORCE uword_t
mem_read_w(mem_t *mem, const mem_addr_phys_t addr) {
    return LITTLE_ENDIAN_WORD(*(uword_t *)_addr_phys_to_host(mem, addr);
}

static INLINE_FORCE udword_t
mem_read_dw(mem_t *mem, const mem_addr_phys_t addr) {
    return LITTLE_ENDIAN_DWORD(*(udword_t *)_addr_phys_to_host(mem, addr));
}

static INLINE_FORCE void
mem_write_b(mem_t *mem, const mem_addr_phys_t addr, const ubyte_t val) {
    *(ubyte_t *)_addr_phys_to_host(mem, addr) = val;
}

static INLINE_FORCE void
mem_write_w(mem_t *mem, const mem_addr_phys_t addr, const uword_t val) {
    *(uword_t *)_addr_phys_to_host(mem, addr) = LITTLE_ENDIAN_WORD(val);
}

static INLINE_FORCE void
mem_write_dw(mem_t *mem, const mem_addr_phys_t addr, const udword_t val) {
    *(udword_t *)_addr_phys_to_host(mem, addr) = LITTLE_ENDIAN_DWORD(val);
}

static INLINE_FORCE void
mem_read(mem_t *mem, const mem_addr_phys_t addr, const void *buf, const size_t n) {
    memcpy(buf, _addr_phys_to_host(mem, addr), n);
}

static INLINE_FORCE void
mem_write(mem_t *mem, const mem_addr_phys_t addr, const void *buf, const size_t n) {
    memcpy(_addr_phys_to_host(mem, addr), buf, n);
}

#endif MEM_C_H
