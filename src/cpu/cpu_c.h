/*
 * Core 8086 Copyright (C) 2014 Matthew Vilim
 *
 * src/shared/macros.h
 */

#ifndef CPU_C_H
#define CPU_C_H

#include "cpu.h"

#include "mmu.h"
#include "reg_file.h"

typedef struct seg_desc {
    udword_t dword[2];
} seg_desc_t;

typedef struct tss_desc {
    udword_t dword[2];
} tss_desc_t;

typedef struct tss32 {
    udword_t link, esp0, ss0, esp1, ss1, esp2, ss2, cr3, eip, eflags, gen[8], seg[6], io_map_base;
} tss32_t;

typedef struct tss16 {
    uword_t link, sp0, ss0, sp1, ss1, sp2, ss2, cr3, ip, flags, gen[8], seg[6], io_map_base;
} tss16_t;

typedef struct tlb_entry {
    addr_virt_t virt;
    addr_phys_t phys;
    void *host;
    uint8_t permission;
} tlb_entry_t;

typedef struct cpu {
    reg_file_t reg_file;
    mmu_t mmu;

    mem_t *mem;
} cpu_t;

C86_INLINE bool
cpu_pe_enabled(const cpu_t *cpu) {
    return (cpu->reg_file.cr0 & X86_CR0_MASK_PE) != 0;
}

C86_INLINE bool
cpu_vm_enabled(const cpu_t *cpu) {
    return (cpu->reg_file.eflags & X86_EFLAGS_MASK_VM) != 0;
}

#endif
