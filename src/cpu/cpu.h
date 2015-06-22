/*
 * Core 8086 Copyright (C) 2014 Matthew Vilim
 *
 * src/shared/macros.h
 */

#include <stdlib.h>

#ifndef CPU_H
#define CPU_H

#define

typedef struct cpu {
    struct reg_file {
        // general purpose registers
        dword_t gen[8];
        // segment registers
        word_t seg[4];
        // instruction pointer
        dword_t eip;
        // flags
        dword_t eflags;
    };

    mem_t *mem;
    bool
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
