#include "mmu_c.h"

#define PAGE_SIZE_LOG2      12
#define TLB_SIZE_LOG2       10
#define TLB_SIZE            BIT(TLB_SIZE_LOG2)
#define MASK_TLB_OFFSET     MASK_RANGE(PAGE_SIZE_LOG2 - 1, 0)
#define MASK_TLB_INDEX      MASK_RANGE(TLB_SIZE_LOG2 + PAGE_SIZE_LOG2 - 1, PAGE_SIZE_LOG2)
#define MASK_TLB_TAG        MASK_RANGE(X86_MEM_PHYS_BUS_SIZE_80386 - 1, TLB_SIZE_LOG2 + PAGE_SIZE_LOG2)

struct mmu {
    mem *mem;

    bool protected, paged;

    struct tlb {
        tlb_entry *entries;
    };
};

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

gc_error_t
mmu_init(mmu *mmu, mem *mem) {
    mmu->mem = mem;
}

void
mmu_term(mmu *mmu) {
    mmu->mem = NULL;
}

void
mmu_cache_seg_desc(mmu *mmu, reg_file *reg_file, uint8 seg, bool consistent) {
    udword base, limit;
    uint8 dpl, type, s, dpl, p, avl, db;
    if (mmu_protected(mmu)) {
        word sel = reg_file_seg_read(reg_file, seg);

        lin_addr addr;
        if (BIT_FIELD_READ(sel, X86_SEG_SELECTOR_MASK_TI)) {
            addr = reg_file->ldtr.base;
        } else {
            addr = reg_file->gdtr.base;
        }

        seg_desc desc;
        desc.dw[0] = mmu_lin_read_dw(mmu, addr);
        desc.dw[1] = mmu_lin_read_dw(mmu, addr + 4);

        base = 0;
        BIT_FIELD_WRITE(base, MASK_RANGE(15, 0), BIT_FIELD_READ(desc[0], X86_SEG_DESC_MASK_BASE_15_0));
        BIT_FIELD_WRITE(base, MASK_RANGE(23, 16), BIT_FIELD_READ(desc[0], X86_SEG_DESC_MASK_BASE_15_0));
        BIT_FIELD_WRITE(base, MASK_RANGE(31, 24), BIT_FIELD_READ(desc[0], X86_SEG_DESC_MASK_BASE_31_24));

        limit = 0;
        BIT_FIELD_WRITE(limit, MASK_RANGE(15, 0), BIT_FIELD_READ(desc[0], X86_SEG_DESC_MASK_LIMIT_15_0));
        BIT_FIELD_WRITE(limit, MASK_RANGE(19, 16), BIT_FIELD_READ(desc[1], X86_SEG_DESC_MASK_BASE_23_16));
        if (BIT_FIELD_READ(desc.dw[1], X86_SEG_DESC_MASK_G)) {
            limit << KBYTES_LOG2(2);
            BIT_FIELD_WRITE(limit, MASK_KBYTES(2), ~0);
        }

        seg_desc_cache *cache = mmu->seg + seg;
        cache->type = BIT_FIELD_READ(desc.dw[1], X86_SEG_DESC_MASK_TYPE);
        cache->s = BIT_FIELD_READ(desc.dw[1], X86_SEG_DESC_MASK_S);
        dpl = BIT_FIELD_READ(desc.dw[1], X86_SEG_DESC_MASK_DPL);
        cache->p = BIT_FIELD_READ(desc.dw[1], X86_SEG_DESC_MASK_P);
        cache->avl = BIT_FIELD_READ(desc.dw[1], X86_SEG_DESC_MASK_AVL);
        cache->db = BIT_FIELD_READ(desc.dw[1], X86_SEG_DESC_MASK_D_B);
    } else {
        base = seg->sel << 4;
        if (consistent) {
            limit = BIT_FIELD_WRITE(0, MASK_KBYTES(6), ~0);
        }
        dpl = 0;
    }
    cache->base = base;
    cache->limit = limit;
    cache->dpl = dpl;
}
