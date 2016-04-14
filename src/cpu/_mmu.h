/*
 * Core 8086 Copyright (C) 2014 Matthew Vilim
 *
 * src/cpu/mmu_c.h
 */

#ifndef _MMU_H
#define _MMU_H

#include "mmu.h"

#include "_mem.h"

typedef struct seg_desc_cache {
    bool dirty;
    addr_lin base;
    udword limit;
    uint8 type, s, dpl, p, avl, db;
} seg_desc_cache;

typedef struct mmu {
    mem *mem;

    bool protected, paged;
    seg_desc_cache seg[6];

    struct tlb {
        tlb_entry *entries;
    };
} mmu;

INLINE_FORCE bool
mmu_protected(mmu *mmu) {
    return mmu0->protected;
}

INLINE_FORCE void
mmu_cache_protected(mmu *mmu, reg_file *reg_file) {
    mmu->protected = reg_file_pe_enabled(reg_file) && !reg_file_vm_enabled(reg_file);
}

INLINE_FORCE void
mmu_cache_paged(mmu *mmu, reg_file *reg_file) {
    mmu->paged = (reg_file->cr0 & X86_EFLAGS_MASK_PG) != 0;
}

INLINE_FORCE addr_lin_t
mmu_addr_log_to_lin(mmu *mmu, addr_log log) {
    seg_desc_cache *cache = mmu->seg + log.seg;
    if (log.offset < cache->limit) {
        return cache->base + log.offset;
    } else {
        // TODO: do exception
    }
}

INLINE_FORCE addr_phys_t
mmu_addr_lin_to_phys(mmu *mmu, addr_lin lin) {
    if (mmu->paged) {
        // TODO: implement paging
    } else {
        return lin;
    }
}

INLINE_FORCE ubyte_t
mmu_addr_log_read_b(mmu *mmu, addr_log log) {
    addr_lin lin = mmu_addr_log_to_lin(mmu, log);
    return mmu_addr_lin_read_b(mmu, lin);
}

INLINE_FORCE ubyte_t
mmu_addr_lin_read_b(mmu *mmu, addr_lin lin) {
    addr_phys phys = mmu_addr_lin_to_phys(mmu, lin);
    return mem_addr_phys_read_b(mmu->mem, phys)
}

#endif
