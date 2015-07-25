/*
 * GameCore Copyright (C) 2014 Matthew Vilim
 *
 * src/shared/macros.h
 */

#ifndef MEM_H
#define MEM_H

struct mem_t;
struct mem_conf_t;

gc_error_t mem_init(mem_t *mem, mem_conf_t *conf);
void mem_alloc_block(mem_t *mem, const size_t index);

#endif
