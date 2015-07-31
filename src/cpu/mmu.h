/*
 * Core 8086 Copyright (C) 2014 Matthew Vilim
 *
 * src/cpu/mmu.h
 */

#ifndef MMU_H
#define MMU_H

#include "cpu.h"

gc_error_t mmu_init(mmu_t *mmu, mem_t *mem);
void mmu_term(mmu_t *mmu);

#endif
