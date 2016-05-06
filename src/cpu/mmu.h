/*
 * Core 8086 Copyright (C) 2014 Matthew Vilim
 *
 * src/cpu/mmu.h
 */

#ifndef MMU_H
#define MMU_H

typedef struct mmu mmu;

typedef dword mmu_addr_log;
typedef dword mmu_addr_lin;

gc_error mmu_init(mmu *mmu, mem *mem);
void mmu_term(mmu *mmu);

#endif
