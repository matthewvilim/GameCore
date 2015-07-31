#include "mmu_c.h"

#define PAGE_SIZE_LOG2      12
#define TLB_SIZE_LOG2       10
#define TLB_SIZE            BIT(TLB_SIZE_LOG2)
#define MASK_TLB_OFFSET     MASK_RANGE(PAGE_SIZE_LOG2 - 1, 0)
#define MASK_TLB_INDEX      MASK_RANGE(TLB_SIZE_LOG2 + PAGE_SIZE_LOG2 - 1, PAGE_SIZE_LOG2)
#define MASK_TLB_TAG        MASK_RANGE(X86_MEM_PHYS_BUS_SIZE_80386 - 1, TLB_SIZE_LOG2 + PAGE_SIZE_LOG2)

gc_error_t
mmu_init(mmu_t *mmu, mem_t *mem) {
    mmu->mem = mem;
}

void
mmu_term(mmu_t *mmu) {
    mmu->mem = NULL;
}

void
mmu_cache_seg_desc(mmu_t *mmu, reg_file_t *reg_file, uint8_t seg, bool consistent) {
    udword_t base, limit;
    uint8_t dpl, type, s, dpl, p, avl, db;
    if (mmu_protected(mmu)) {
        word_t sel = reg_file_seg_read(reg_file, seg);

        lin_addr_t addr;
        if (BIT_FIELD_READ(sel, X86_SEG_SELECTOR_MASK_TI)) {
            addr = reg_file->ldtr.base;
        } else {
            addr = reg_file->gdtr.base;
        }

        seg_desc_t desc;
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

        seg_desc_cache_t *cache = mmu->seg + seg;
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
