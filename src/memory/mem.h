/*
 * GameCore Copyright (C) 2014 Matthew Vilim
 *
 * src/shared/macros.h
 */

#ifndef MEM_H
#define MEM_H

struct mem;
struct mem_conf;

gc_error mem_init(mem *mem, mem_conf *conf);
void mem_alloc_block(mem *mem, const size index);

#endif
