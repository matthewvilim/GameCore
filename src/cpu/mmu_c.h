/*
 * Core 8086 Copyright (C) 2014 Matthew Vilim
 *
 * src/cpu/mmu_c.h
 */

#ifndef MMU_C_H
#define MMU_C_H

#include "mmu.h"

typedef struct mmu {
    struct desc_cache {
        udword_t limit;
        addr_lin_t base;
        uint8_t dpl;
    }[6];

     struct tlb {
         tlb_entry_t *entries;
     };
} mmu_t;

INLINE_FORCE void
mmu_cache_seg_desc(cpu_t *cpu, uint8_t seg) {
    word_t sel = cpu_seg_read(cpu, seg);

    seg_desc_t desc;
    lin_addr_t addr;
    if (BIT_FIELD_READ(sel, X86_SEG_SELECTOR_MASK_TI)) {
        addr = cpu->reg_file.ldtr.base;
    } else {
        addr = cpu->reg_file.gdtr.base;
    }

    desc.dw[0] = mem_lin_read_dw(cpu->mem, addr);
    desc.dw[1] = mem_lin_read_dw(cpu->mem, addr + 4);

    uint16_t limit_low = BIT_FIELD_READ(desc[0], X86_SEG_DESC_MASK_LIMIT_15_0);
    uint8_t limit_high = BIT_FIELD_READ(desc[0], X86_SEG_DESC_MASK_LIMIT_19_16);
    udword_t limit = 0;
    BIT_FIELD_WRITE(limit, MASK_RANGE(15, 0), limit_low);
    BIT_FIELD_WRITE(limit, MASK_RANGE(19, 16), limit_high);
    if (BIT_FIELD_READ(sel, X86_SEG_DESC_MASK_G)) {
        limit << 12;
        BIT_FIELD_WRITE(limit, MASK_RANGE(11, 0), ~0);
    }
    cpu->mmu.desc_cache[seg].limit = limit;
    cpu->mmu.desc_cache[seg].dpl = BIT_FIELD_READ(desc.dw[1], X86_SEG_DESC_MASK_DPL);


}

#endif
