/*
 * Core 8086 Copyright (C) 2014 Matthew Vilim
 *
 * src/shared/macros.h
 */

#ifndef CPU_INLINE_H
#define CPU_INLINE_H

#include "cpu.h"

#define PAGE_SIZE_LOG2      12
#define TLB_SIZE_LOG2       10
#define TLB_SIZE           (1 << TLB_SIZE_LOG2)
#define TLB_OFFSET_MASK     MASK_RANGE(PAGE_SIZE_LOG2 - 1, 0)
#define TLB_INDEX_MASK      MASK_RANGE(TLB_SIZE_LOG2 + PAGE_SIZE_LOG2 - 1, PAGE_SIZE_LOG2)
#define TLB_TAG_MASK        MASK_RANGE(31, TLB_SIZE_LOG2 + PAGE_SIZE_LOG2)

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
    struct reg_file {
        udword_t gen[8], eip, eflags;

        uword_t seg[6];

        udword_t eip;

        struct gdtr {
            uword_t size;
            addr_lin_t base;
        };

        struct ldtr {
            uword_t limit;
            addr_virt_t base;
        };

        struct idtr {
            uword_t limit;
            addr_lin_t base;
        };

        uword_t cr0, cr1, cr2, cr3, tr;
    };

    struct mmu {
        struct desc_cache {
            dword_t limit;
            addr_lin_t base;
            uint8_t dpl : 2;
        }[6];

         struct tlb {
             tlb_entry_t *entries;
         };
    };
    mem_t *mem;

} cpu_t;

C86_INLINE bool
cpu_pe_enabled(const cpu_t *cpu) {
    return cpu->reg_file.cr0 & X86_CR0_MASK_PE;
}

C86_INLINE bool
cpu_vm_enabled(const cpu_t *cpu) {
    return cpu->reg_file.eflags & X86_EFLAGS_MASK_VM;
}

// EIP
C86_INLINE udword_t
cpu_eip_read(const cpu_t *cpu) {
    return cpu->reg_file.eip, MASK_DW;
}

C86_INLINE uword_t
cpu_ip_read(const cpu_t *cpu) {
    return BIT_FIELD_READ(cpu->reg_file.eip, MASK_LOW_W);
}

C86_INLINE void
cpu_eip_write(cpu_t *cpu, udword_t val) {
    cpu->reg_file.eip = val;
}

C86_INLINE void
cpu_ip_write(cpu_t *cpu, uword_t val) {
    BIT_FIELD_WRITE(cpu->reg_file.eip, MASK_LOW_W, val);
}

// EFLAGS
C86_INLINE udword_t
cpu_eflags_read(const cpu_t *cpu) {
    return cpu->reg_file.eflags;
}

C86_INLINE uword_t
cpu_flags_read(const cpu_t *cpu) {
    return BIT_FIELD_READ(cpu->reg_file.eflags, MASK_LOW_W);
}

C86_INLINE void
cpu_eflags_write(cpu_t *cpu, udword_t val) {
    cpu->reg_file.eflags = val;
}

C86_INLINE void
cpu_flags_write(cpu_t *cpu, uword_t val) {
    BIT_FIELD_WRITE(cpu->reg_file.eflags, MASK_LOW_W, val);
}

// general registers
C86_INLINE ubyte_t
cpu_gen_read_b(const cpu_t *cpu, const uint8_t reg) {
    udword_t mask = reg & BIT(2) ? MASK_LOW_B : MASK_HIGH_B;
    return BIT_FIELD_READ(cpu->reg_file.gen[reg & ~BIT(2)], mask);
}

C86_INLINE uword_t
cpu_gen_read_w(const cpu_t *cpu, const uint8_t reg) {
    return BIT_FIELD_READ(cpu->reg_file.gen[reg], MASK_LOW_W);
}

C86_INLINE udword_t
cpu_gen_read_dw(const cpu_t *cpu, const uint8_t reg) {
    return cpu->reg_file.gen[reg];
}

C86_INLINE void
cpu_gen_write_b(cpu_t *cpu, const uint8_t reg, ubyte_t val) {
    udword_t mask = reg & BIT(2) ? MASK_LOW_B : MASK_HIGH_B;
    BIT_FIELD_WRITE(cpu->reg_file.gen[reg & ~BIT(2)], mask, val);
}

C86_INLINE void
cpu_gen_write_w(cpu_t *cpu, const uint8_t reg, uword_t val) {
    BIT_FIELD_WRITE(cpu->reg_file.gen[reg], MASK_LOW_W, val);
}

C86_INLINE void
cpu_gen_write_dw(cpu_t *cpu, const uint8_t reg, udword_t val) {
    cpu->reg_file.gen[reg] = val;
}

// segment registers
C86_INLINE uword_t
cpu_seg_read(const cpu_t *cpu, const uint8_t reg) {
    return cpu->reg_file.seg[reg];
}

C86_INLINE void
cpu_seg_write(cpu_t *cpu, const uint8_t reg, uword_t val) {
    if (cpu_vm_enabled(cpu)) {
        cpu->reg_file.seg[reg].Selector = vale;
    } else {

    }
    cpu->reg_file.seg[reg] = val;
}

#endif
