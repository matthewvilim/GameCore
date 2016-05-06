/*
 * GameCore Copyright (C) 2014 Matthew Vilim
 *
 * src/memory/memory.c
 */

#include "_mem.h"

gc_error_t
mem_init(mem *mem, mem_conf *conf) {
    ASSERT(mem && conf);
    mem->size_mb = conf->size_mb;

    mem->block_table = malloc(mem->size_mb * sizeof(ubyte *));
    for (size i = 0; i < mem->size_mb; i += MEM_BLOCK_SIZE_MBYTES) {
        mem->block_table[i] = NULL;
    }
    if (!mem->block_table) return C86_NO_MEM_ERROR;

    return GC_NO_ERROR;
}

gc_error_t
mem_delete(mem *mem) {
    ASSERT(mem);

    for (size i = 0; i < mem->size_mb; i += MEM_BLOCK_SIZE_MBYTES) {
        mem_release_block(mem, i);
    }
    free(mem->block_table);
    mem->block_table = NULL;
    return GC_NO_ERROR;
}

void
mem_alloc_block(mem *mem, const size index) {
    ubyte *block = malloc(MEM_BLOCK_SIZE_BYTES);
    if (!block) {
        ERROR("host memory allocation failed for table: 0x%x block: 0x%x", table_index, block_index);
    }
    mem->block_table[index] = block;
}

void
mem_release_block(mem *mem, const size index) {
    ubyte **block  = mem->block_table + index;
    if (*block) {
        INFO("releasing block: 0x%x", index);
        free(*block);
        *block = NULL;
    }
}

static inline void *
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
