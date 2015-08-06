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

typedef struct addr_log {
    uint8_t seg;
    uword_t offset;
} addr_log_t;
typedef dword_t addr_lin_t;
typedef dword_t addr_phys_t;

typedef struct mem_conf {
    size_t size_mb;
} mem_conf_t;

typedef struct mem {
    void **block_table;
    size_t size_mb;

    mem_handler_read_t read;
    mem_handler_write_t write;
} mem_t;

static INLINE_FORCE void *
mem_addr_phys_to_host(mem_t *mem, const addr_phys_t addr) {
    size_t table_index = BIT_FIELD_READ(addr, MEM_BLOCK_TABLE_INDEX_MASK);
    size_t block_index = BIT_FIELD_READ(addr, MEM_BLOCK_INDEX_MASK);
    void **block = mem->block_table + table_index;
    if (UNLIKELY(!*block)) {
        mem_alloc_block(mem, table_index);
    }
    return (ubyte_t *)*block + block_index;
}

static INLINE_FORCE ubyte_t
mem_host_read_b(ubyte_t *b) {
    return *b;
}

static INLINE_FORCE uword_t
mem_host_read_w(uword_t *w) {
    return ENDIAN_CONV_WORD(*w);
}

static INLINE_FORCE udword_t
mem_host_read_dw(udword_t *dw) {
    return ENDIAN_CONV_DWORD(*dw);
}

static INLINE_FORCE void
mem_host_write_b(ubyte_t *b, ubyte_t val) {
    *b = val;
}

static INLINE_FORCE void
mem_host_write_w(uword_t *w, uword_t val) {
    *w = ENDIAN_CONV_WORD(val);
}

static INLINE_FORCE void
mem_host_write_dw(udword_t *dw, udword_t val) {
    *dw = ENDIAN_CONV_DWORD(val);
}

static INLINE_FORCE ubyte_t
mem_addr_phys_read_b(mem_t *mem, const addr_phys_t addr) {
    return mem_read_host_b(mem_addr_phys_to_host(mem, addr));
}

static INLINE_FORCE uword_t
mem_addr_phys_read_w(mem_t *mem, const addr_phys_t addr) {
    return mem_host_read_w(mem_addr_phys_to_host(mem, addr));
}

static INLINE_FORCE void
mem_addr_phys_write_b(mem_t *mem, const addr_phys_t addr, const ubyte_t val) {
    mem_host_write_b(mem_addr_phys_to_host(mem, addr), val);
}

static INLINE_FORCE udword_t
mem_addr_phys_read_dw(mem_t *mem, const addr_phys_t addr) {
    return mem_host_read_dw(mem_addr_phys_to_host(mem, addr));
}

static INLINE_FORCE void
mem_addr_phys_write_w(mem_t *mem, const addr_phys_t addr, const uword_t val) {
    mem_host_write_w(mem_addr_phys_to_host(mem, addr), val);
}

static INLINE_FORCE void
mem_addr_phys_write_dw(mem_t *mem, const addr_phys_t addr, udword_t val) {
    mem_host_write_dw(mem_addr_phys_to_host(mem, addr), val);
}

#endif MEM_C_H
