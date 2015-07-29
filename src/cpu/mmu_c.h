/*
 * Core 8086 Copyright (C) 2014 Matthew Vilim
 *
 * src/cpu/mmu_c.h
 */

#ifndef MMU_C_H
#define MMU_C_H

#include "mmu.h"

typedef struct mmu {
    bool protected, paged;
    struct tlb {
        tlb_entry_t *entries;
    };
} mmu_t;

INLINE_FORCE void
mmu_cache_protected(mmu_t *mmu, reg_file_t *reg_file) {
    mmu->protected = reg_file_pe_enabled(reg_file) && !reg_file_vm_enabled(reg_file);
}

INLINE_FORCE void
mmu_cache_paged(mmu_t *mmu, reg_file_t *reg_file) {
    mmu->paged = (reg_file->cr0 & X86_EFLAGS_MASK_PG) != 0;
}

INLINE_FORCE addr_lin_t
mmu_addr_log_to_lin(mmu_t *mmu, addr_log_t log, reg_file_t *reg_file) {
    if (mmu->protected) {
        reg_seg_t *seg = reg_file->seg + addr.seg;
        if (log.offset < seg->limit) {
            return seg.base + log.offset;
        } else {
            // TODO: do exception
        }
    } else {
        uword_t seg = reg_file_seg_read(reg_file, log.seg);
        return ((seg << 4) + log.offset) & MASK_RANGE(X86_MEM_PHYS_BUS_SIZE_8086, 0);
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
mmu_addr_log_read_b(mmu_t *mmu, addr_log_t log, reg_file_t *reg_file, mem_t *mem) {
    addr_lin_t lin = mmu_addr_log_to_lin(mmu, log, reg_file);
    return mmu_addr_lin_read_b(mmu, lin, mem);
}

INLINE_FORCE ubyte_t
mmu_addr_lin_read_b(mmu_t *mmu, addr_lin_t lin, mem_t *mem) {
    addr_phys_t phys = mmu_addr_lin_to_phys(mmu, lin);
    return mem_addr_phys_read_b(mem, phys)
}

#endif
