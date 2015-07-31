/*
 * Core 8086 Copyright (C) 2014 Matthew Vilim
 *
 * src/cpu/mmu_c.h
 */

#ifndef MMU_C_H
#define MMU_C_H

#include "mmu.h"

#include "mem_c.h"

typedef struct seg_desc_cache {
    bool dirty;
    addr_lin_t base;
    udword_t limit;
    uint8_t type, s, dpl, p, avl, db;
} seg_desc_cache_t;

typedef struct mmu {
    mem_t *mem;

    bool protected, paged;
    seg_desc_cache_t seg[6];

    struct tlb {
        tlb_entry_t *entries;
    };
} mmu_t;

INLINE_FORCE bool
mmu_protected(mmu_t *mmu) {
    return mmu0->protected;
}

INLINE_FORCE void
mmu_cache_protected(mmu_t *mmu, reg_file_t *reg_file) {
    mmu->protected = reg_file_pe_enabled(reg_file) && !reg_file_vm_enabled(reg_file);
}

INLINE_FORCE void
mmu_cache_paged(mmu_t *mmu, reg_file_t *reg_file) {
    mmu->paged = (reg_file->cr0 & X86_EFLAGS_MASK_PG) != 0;
}

INLINE_FORCE addr_lin_t
mmu_addr_log_to_lin(mmu_t *mmu, addr_log_t log) {
    seg_desc_cache_t *cache = mmu->seg + log.seg;
    if (log.offset < cache->limit) {
        return cache->base + log.offset;
    } else {
        // TODO: do exception
    }
}

INLINE_FORCE addr_phys_t
mmu_addr_lin_to_phys(mmu_t *mmu, addr_lin_t lin) {
    if (mmu->paged) {
        // TODO: implement paging
    } else {
        return lin;
    }
}

INLINE_FORCE ubyte_t
mmu_addr_log_read_b(mmu_t *mmu, addr_log_t log) {
    addr_lin_t lin = mmu_addr_log_to_lin(mmu, log);
    return mmu_addr_lin_read_b(mmu, lin);
}

INLINE_FORCE ubyte_t
mmu_addr_lin_read_b(mmu_t *mmu, addr_lin_t lin) {
    addr_phys_t phys = mmu_addr_lin_to_phys(mmu, lin);
    return mem_addr_phys_read_b(mmu->mem, phys)
}

#endif
