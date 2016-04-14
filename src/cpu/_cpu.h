/*
 * Core 8086 Copyright (C) 2014 Matthew Vilim
 *
 * src/shared/macros.h
 */

#ifndef _CPU_H
#define _CPU_H

#include "cpu.h"

#include "mmu.h"
#include "reg_file.h"

typedef struct seg_desc {
    udword dw[2];
} seg_desc;

typedef struct tss_desc {
    udword dw[2];
} tss_desc;

typedef struct tss32 {
    udword link, esp0, ss0, esp1, ss1, esp2, ss2, cr3, eip, eflags, gen[8], seg[6], io_map_base;
} tss32;

typedef struct tss16 {
    uword link, sp0, ss0, sp1, ss1, sp2, ss2, cr3, ip, flags, gen[8], seg[6], io_map_base;
} tss16;

typedef struct tlb_entry {
    addr_virt virt;
    addr_phys phys;
    void *host;
    uint8 permission;
} tlb_entry;

typedef struct cpu {
    reg_file reg_file;
    mmu mmu;
    jmp_buf exc_buf;
} cpu;

#endif
