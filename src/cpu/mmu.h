/*
 * Core 8086 Copyright (C) 2014 Matthew Vilim
 *
 * src/cpu/mmu.h
 */

#ifndef MMU_H
#define MMU_H

typedef struct mmu {
    struct desc_cache {
        dword_t limit;
        addr_lin_t base;
        uint8_t dpl : 2;
    }[6];

     struct tlb {
         tlb_entry_t *entries;
     };
} mmu_t;

INLINE_FORCE void
mmu_cache_seg_desc(cpu_t *cpu, uint8_t seg) {

}

mmu_log_addr_read_b()

#endif
