/*
 * Core 8086 Copyright (C) 2014 Matthew Vilim
 *
 * src/cpu/reg_file_c.h
 */

#ifndef _REG_FILE_H
#define _REG_FILE_H

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

typedef struct reg_file {
    udword_t gen[8], eip, eflags;

    uword_t seg[6];

    udword_t eip;

    reg_desc_table_t gdtr, ldtr, idtr;

    reg_task_t tr;
    uword_t cr0, cr1, cr2, cr3;

    mmu_t *mmu;
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
    return reg_file->seg[reg];
}

C86_INLINE void
reg_file_seg_write(reg_file_t *reg_file, const uint8_t reg, uword_t val) {
    reg_file->seg[reg] = val;
}

C86_INLINE bool
reg_file_pe_enabled(const reg_file_t *reg_file) {
    return reg_file->cr0 & X86_CR0_MASK_PE;
}

C86_INLINE bool
reg_file_vm_enabled(const reg_file_t *reg_file) {
    return reg_file->eflags & X86_EFLAGS_MASK_VM;
}

#endif
