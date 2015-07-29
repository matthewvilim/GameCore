/*
 * Core 8086 Copyright (C) 2014 Matthew Vilim
 *
 * src/cpu/reg_file_c.h
 */

#ifndef REG_FILE_C_H
#define REG_FILE_C_H

#include "reg_file.h"

typedef struct reg_desc_table {
    addr_lin_t base;
    uword_t limit;
} reg_desc_table_t;

typedef struct reg_task {
    uword_t sel;
    struct cache {
        addr_lin_t base;
        uword_t limit;
    };
} reg_task_t;

typedef struct reg_seg {
    uword_t sel;
    struct cache {
        addr_lin_t base;
        udword_t limit;
        uint8_t type, s, dpl, p, avl, db;
    };
} reg_seg_t;

typedef struct reg_file {
    udword_t gen[8], eip, eflags;

    reg_seg_t seg[6];

    udword_t eip;

    reg_desc_table_t gdtr, ldtr, idtr;

    reg_task_t tr;
    uword_t cr0, cr1, cr2, cr3;
} reg_file_t;

C86_INLINE uword_t
reg_file_ip_read(const reg_file_t *reg_file) {
    return BIT_FIELD_READ(reg_file->eip, MASK_LOW_W);
}

C86_INLINE void
reg_file_ip_write(reg_file_t *reg_file, uword_t val) {
    BIT_FIELD_WRITE(reg_file->eip, MASK_LOW_W, val);
}

C86_INLINE uword_t
reg_file_flags_read(const reg_file_t *reg_file) {
 return BIT_FIELD_READ(reg_file->eflags, MASK_LOW_W);
}

C86_INLINE void
reg_file_flags_write(reg_file_t *reg_file, uword_t val) {
    BIT_FIELD_WRITE(reg_file->eflags, MASK_LOW_W, val);
}

C86_INLINE ubyte_t
reg_file_gen_read_b(const reg_file_t *reg_file, const uint8_t reg) {
    udword_t mask = reg & BIT(2) ? MASK_LOW_B : MASK_HIGH_B;
    return BIT_FIELD_READ(reg_file->gen[reg & ~BIT(2)], mask);
}

C86_INLINE uword_t
reg_file_gen_read_w(const reg_file_t *reg_file, const uint8_t reg) {
    return BIT_FIELD_READ(reg_file->gen[reg], MASK_LOW_W);
}

C86_INLINE udword_t
reg_file_gen_read_dw(const reg_file_t *reg_file, const uint8_t reg) {
    return reg_file->gen[reg];
}

C86_INLINE void
reg_file_gen_write_b(reg_file_t *reg_file, const uint8_t reg, ubyte_t val) {
    udword_t mask = reg & BIT(2) ? MASK_LOW_B : MASK_HIGH_B;
    BIT_FIELD_WRITE(reg_file->gen[reg & ~BIT(2)], mask, val);
}

C86_INLINE void
reg_file_gen_write_w(reg_file_t *reg_file, const uint8_t reg, uword_t val) {
    BIT_FIELD_WRITE(reg_file->gen[reg], MASK_LOW_W, val);
}

C86_INLINE void
reg_file_gen_write_dw(reg_file_t *reg_file, const uint8_t reg, udword_t val) {
    reg_file->gen[reg] = val;
}

C86_INLINE uword_t
reg_file_seg_read(reg_file_t *reg_file, const uint8_t reg) {
    return reg_file->seg[reg].sel;
}

C86_INLINE void
reg_file_seg_write(reg_file_t *reg_file, const uint8_t reg, uword_t val) {
    reg_file->seg[reg].sel = val;
}

C86_INLINE bool
reg_file_pe_enabled(const reg_file_t *reg_file) {
    return reg_file->cr0 & X86_CR0_MASK_PE;
}

C86_INLINE bool
reg_file_vm_enabled(const reg_file_t *reg_file) {
    return reg_file->eflags & X86_EFLAGS_MASK_VM;
}

INLINE_FORCE void
reg_file_cache_seg_desc(reg_file_t *reg_file, uint8_t seg, mem_t *mem) {
    word_t sel = reg_file_seg_read(reg_file, seg);

    seg_desc_t desc;
    lin_addr_t addr;
    if (BIT_FIELD_READ(sel, X86_SEG_SELECTOR_MASK_TI)) {
        addr = reg_file->ldtr.base;
    } else {
        addr = reg_file->gdtr.base;
    }

    desc.dw[0] = mem_lin_read_dw(mem, addr);
    desc.dw[1] = mem_lin_read_dw(mem, addr + 4);

    udword_t base = 0;
    BIT_FIELD_WRITE(base, MASK_RANGE(15, 0), BIT_FIELD_READ(desc[0], X86_SEG_DESC_MASK_BASE_15_0));
    BIT_FIELD_WRITE(base, MASK_RANGE(23, 16), BIT_FIELD_READ(desc[0], X86_SEG_DESC_MASK_BASE_15_0));
    BIT_FIELD_WRITE(base, MASK_RANGE(31, 24), BIT_FIELD_READ(desc[0], X86_SEG_DESC_MASK_BASE_31_24));

    udword_t limit = 0;
    BIT_FIELD_WRITE(limit, MASK_RANGE(15, 0), BIT_FIELD_READ(desc[0], X86_SEG_DESC_MASK_LIMIT_15_0));
    BIT_FIELD_WRITE(limit, MASK_RANGE(19, 16), BIT_FIELD_READ(desc[1], X86_SEG_DESC_MASK_BASE_23_16));
    if (BIT_FIELD_READ(desc.dw[1], X86_SEG_DESC_MASK_G)) {
        limit << KBYTES_LOG2(2);
        BIT_FIELD_WRITE(limit, MASK_RANGE(KBYTES_LOG2(2) - 1, 0), ~0);
    }

    reg_seg_t *seg = reg_file->seg + seg;
    seg->cache.base = base;
    seg->cache.limit = limit;
    seg->cache.type = BIT_FIELD_READ(desc.dw[1], X86_SEG_DESC_MASK_TYPE);
    seg->cache.s = BIT_FIELD_READ(desc.dw[1], X86_SEG_DESC_MASK_S);
    seg->cache.dpl = BIT_FIELD_READ(desc.dw[1], X86_SEG_DESC_MASK_DPL);
    seg->cache.p = BIT_FIELD_READ(desc.dw[1], X86_SEG_DESC_MASK_P);
    seg->cache.avl = BIT_FIELD_READ(desc.dw[1], X86_SEG_DESC_MASK_AVL);
    seg->cache.db = BIT_FIELD_READ(desc.dw[1], X86_SEG_DESC_MASK_D_B);
}

#endif
