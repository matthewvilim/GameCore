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
