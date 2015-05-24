/*
 * GameCore Copyright (C) 2014 Matthew Vilim
 *
 * src/memory/memory.c
 */

#include "memory.h"

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