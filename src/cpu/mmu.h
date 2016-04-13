/*
 * Core 8086 Copyright (C) 2014 Matthew Vilim
 *
 * src/cpu/mmu.h
 */

#ifndef MMU_H
#define MMU_H

#include "cpu.h"

typedef dword_t mmu_addr_log_t;
typedef dword_t mmu_addr_lin_t;

gc_error_t mmu_init(mmu_t *mmu, mem_t *mem);
void mmu_term(mmu_t *mmu);

#endif
