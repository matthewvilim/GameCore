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
#define MASK_TLB_OFFSET     MASK_RANGE(PAGE_SIZE_LOG2 - 1, 0)
#define MASK_TLB_INDEX      MASK_RANGE(TLB_SIZE_LOG2 + PAGE_SIZE_LOG2 - 1, PAGE_SIZE_LOG2)
#define MASK_TLB_TAG        MASK_RANGE(31, TLB_SIZE_LOG2 + PAGE_SIZE_LOG2)

typedef struct tlb_entry {
    addr_virt_t phys;
    addr_phys_t virt;
    byte_t *host;
    uint8_t permission;
} tlb_entry_t;

typedef struct gdt_desc {
    dword_t dword[2];
} gdt_desc_t;

typedef struct cpu {
    struct reg_file {
        // general purpose registers
        dword_t gen[8];
        // segment registers
        struct seg {
            word_t selector;
            gdt_desc_t descriptor;
        }[6];
        word_t seg[6];
        // instruction pointer
        dword_t eip;
        // flags
        dword_t eflags;
        // Global Descriptor Table register
        struct gdtr {
            word_t size;
            addr_lin_t offset;
        };
        // Local Descriptor Table register
        struct ldtr {
            word_t size;
            addr_virt_t offset;
        };
    };

    mem_t *mem;
    typedef struct tlb {
        tlb_entry_t *entries;
    };
} cpu_t;

// EIP
C86_INLINE dword_t
cpu_eip_read(const cpu_t *cpu) {
    return cpu->reg_file.eip, MASK_DW;
}

C86_INLINE word_t
cpu_ip_read(const cpu_t *cpu) {
    return BIT_FIELD_READ(cpu->reg_file.eip, MASK_LOW_W);
}

C86_INLINE void
cpu_eip_write(cpu_t *cpu, dword_t val) {
    cpu->reg_file.eip = val;
}

C86_INLINE void
cpu_ip_write(cpu_t *cpu, word_t val) {
    BIT_FIELD_WRITE(cpu->reg_file.eip, MASK_LOW_W, val);
}

// EFLAGS
C86_INLINE dword_t
cpu_eflags_read(const cpu_t *cpu) {
    return cpu->reg_file.eflags;
}

C86_INLINE word_t
cpu_flags_read(const cpu_t *cpu) {
    return BIT_FIELD_READ(cpu->reg_file.eflags, MASK_LOW_W);
}

C86_INLINE void
cpu_eflags_write(cpu_t *cpu, dword_t val) {
    cpu->reg_file.eflags = val;
}

C86_INLINE void
cpu_flags_write(cpu_t *cpu, word_t val) {
    BIT_FIELD_WRITE(cpu->reg_file.eflags, MASK_LOW_W, val);
}

// general registers
C86_INLINE byte_t
cpu_gen_read_b(const cpu_t *cpu, const uint8_t reg) {
    dword_t mask = reg & BIT(2) ? MASK_LOW_B : MASK_HIGH_B;
    return BIT_FIELD_READ(cpu->reg_file.gen[reg & ~BIT(2)], mask);
}

C86_INLINE word_t
cpu_gen_read_w(const cpu_t *cpu, const uint8_t reg) {
    return BIT_FIELD_READ(cpu->reg_file.gen[reg], MASK_LOW_W);
}

C86_INLINE dword_t
cpu_gen_read_dw(const cpu_t *cpu, const uint8_t reg) {
    return cpu->reg_file.gen[reg];
}

C86_INLINE void
cpu_gen_write_b(cpu_t *cpu, const uint8_t reg, byte_t val) {
    dword_t mask = reg & BIT(2) ? MASK_LOW_B : MASK_HIGH_B;
    BIT_FIELD_WRITE(cpu->reg_file.gen[reg & ~BIT(2)], mask, val);
}

C86_INLINE void
cpu_gen_write_w(cpu_t *cpu, const uint8_t reg, word_t val) {
    BIT_FIELD_WRITE(cpu->reg_file.gen[reg], MASK_LOW_W, val);
}

C86_INLINE void
cpu_gen_write_dw(cpu_t *cpu, const uint8_t reg, dword_t val) {
    cpu->reg_file.gen[reg] = val;
}

// segment registers
C86_INLINE word_t
cpu_seg_read(const cpu_t *cpu, const uint8_t reg) {
    return cpu->reg_file.seg[reg];
}

C86_INLINE void
cpu_seg_write(cpu_t *cpu, const uint8_t reg, word_t val) {
    cpu->reg_file.seg[reg] = val;
}

#endif
