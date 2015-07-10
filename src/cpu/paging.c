#include "cpu.h"

#define PAGE_SIZE_LOG2      12
#define TLB_SIZE_LOG2       10
#define TLB_SIZE           (1 << TLB_SIZE_LOG2)
#define MASK_TLB_OFFSET     MASK_RANGE(PAGE_SIZE_LOG2 - 1, 0)
#define MASK_TLB_INDEX      MASK_RANGE(TLB_SIZE_LOG2 + PAGE_SIZE_LOG2 - 1, PAGE_SIZE_LOG2)
#define MASK_TLB_TAG        MASK_RANGE(31, TLB_SIZE_LOG2 + PAGE_SIZE_LOG2)

GC_INLINE void
_tlb_offset(addr_virt_t addr) {
    return BIT_FIELD_READ(addr, MASK_TLB_OFFSET);
}

gc_error_t
cpu_init_paging(cpu_t *cpu) {
    memzero(cpu->tlb.entries, sizeof(cpu->tlb.entries));
    return GC_NO_ERROR;
}
