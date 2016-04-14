/*
 * Core 8086 Copyright (C) 2014 Matthew Vilim
 *
 * src/cpu/reg_file_c.h
 */

#ifndef _REG_FILE_H
#define _REG_FILE_H

#include "reg_file.h"

typedef enum reg {
    REG_EAX,
    REG_EBX,
    REG_ECX,
    REG_EDX,
    REG_ESP,
    REG_EBP,
    REG_ESI,
    REG_EDI,

    REG_AX,
    REG_BX,
    REG_CX,
    REG_DX,
    REG_SP,
    REG_BP,
    REG_SI,
    REG_DI,

    REG_AL,
    REG_AH,
    REG_BL,
    REG_BH,
    REG_CL,
    REG_CH,
    REG_DL,
    REG_DH,

    REG_EIP,
    REG_IP,

    REG_EFLAGS,
    REG_FLAGS,

    REG_CR0,
    REG_CR1,
    REG_CR2,
    REG_CR3,

    REG_NULL
} reg;

typedef struct reg_desc_table {
    addr_lin base;
    uword limit;
} reg_desc_table;

typedef struct reg_task {
    uword sel;
    struct cache {
        addr_lin base;
        uword limit;
    };
} reg_task;

typedef struct reg_file {
    udword eax, ebx, ecx, edx, esp, edi, esp, ebp, eip, eflags;

    uword fs, gs, cs, ss, ds, es;

    reg_desc_table gdtr, ldtr, idtr;

    reg_task tr;
    uword cr0, cr1, cr2, cr3;

    mmu *mmu;
} reg_file;

C86_INLINE ubyte_t
reg_file_read_b(const reg_file *reg_file, const reg reg) {
    switch (reg) {
        case REG_AL: return BIT_FIELD_READ(reg_file->eax, MASK_LOW_B);
        case REG_AH: return BIT_FIELD_READ(reg_file->eax, MASK_HIGH_B);
        case REG_BL: return BIT_FIELD_READ(reg_file->ebx, MASK_LOW_B);
        case REG_BH: return BIT_FIELD_READ(reg_file->ebx, MASK_HIGH_B);
        case REG_CL: return BIT_FIELD_READ(reg_file->ecx, MASK_LOW_B);
        case REG_CH: return BIT_FIELD_READ(reg_file->ecx, MASK_HIGH_B);
        case REG_DL: return BIT_FIELD_READ(reg_file->edx, MASK_LOW_B);
        case REG_DH: return BIT_FIELD_READ(reg_file->edx, MASK_HIGH_B);
        case REG_NULL: return 0;
        default: assert(false);
    }
}

C86_INLINE void
reg_file_write_b(reg_file *reg_file, const reg reg, const val) {
    switch (reg) {
        case REG_AL: BIT_FIELD_WRITE(reg_file->eax, MASK_LOW_B, val);
        case REG_AH: BIT_FIELD_WRITE(reg_file->eax, MASK_HIGH_B, val);
        case REG_BL: BIT_FIELD_WRITE(reg_file->ebx, MASK_LOW_B, val);
        case REG_BH: BIT_FIELD_WRITE(reg_file->ebx, MASK_HIGH_B, val);
        case REG_CL: BIT_FIELD_WRITE(reg_file->ecx, MASK_LOW_B, val);
        case REG_CH: BIT_FIELD_WRITE(reg_file->ecx, MASK_HIGH_B, val);
        case REG_DL: BIT_FIELD_WRITE(reg_file->edx, MASK_LOW_B, val);
        case REG_DH: BIT_FIELD_WRITE(reg_file->edx, MASK_HIGH_B, val);
        default: assert(false);
    }
}

C86_INLINE bool
reg_file_pe_enabled(const reg_file *reg_file) {
    return reg_file->cr0 & X86_CR0_MASK_PE;
}

C86_INLINE bool
reg_file_vm_enabled(const reg_file *reg_file) {
    return reg_file->eflags & X86_EFLAGS_MASK_VM;
}

#endif
