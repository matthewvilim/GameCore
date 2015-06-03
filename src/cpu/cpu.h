/*
 * Core 8086 Copyright (C) 2014 Matthew Vilim
 *
 * src/shared/macros.h
 */

#include <stdlib.h>

#ifndef CPU_H
#define CPU_H

typedef struct cpu {
    struct reg_file {
        // general purpose registers
        word_t gen[8];
        // segment registers
        word_t seg[4];
        // instruction pointer
        word_t ip;
        // flags
        word_t flags;
    };

    mem_t *mem;
} cpu_t;

C86_INLINE word_t
cpu_ip_read(const cpu_t *cpu) {
    return cpu->reg_file.ip;
}

C86_INLINE void
cpu_ip_write(cpu_t *cpu, const word_t val) {
    cpu->reg_file.ip, MASK_W = val;
}

C86_INLINE bool
cpu_flags_read(const cpu_t *cpu, const word_t mask) {
    return !!BIT_FIELD_READ(cpu->reg_file.flags, mask);
}

C86_INLINE void
cpu_flags_write(cpu_t *cpu, const word_t mask, const bool val) {
    BIT_FIELD_WRITE(cpu->reg_file.flags, reg->mask, val);
}

C86_INLINE void
cpu_gen_write_b(cpu_t *cpu, const uint8_t reg, const byte_t val) {
    word_t mask = reg & BIT(2) ? MASK_HIGH_B : MASK_LOW_B;
    BIT_FIELD_WRITE(cpu->reg_file.gen[reg & ~BIT(2)], mask, val);
}

C86_INLINE void
cpu_gen_write_w(cpu_t *cpu, const uint8_t reg, const word_t val) {
    cpu->reg_file.gen[reg] = val;
}

C86_INLINE byte_t
cpu_gen_read_b(cpu_t *cpu, const uint8_t reg) {
    word_t mask = reg & BIT(2) ? MASK_HIGH_B : MASK_LOW_B;
    return BIT_FIELD_READ(cpu->reg_file.gen[reg & ~BIT(2)], mask);
}

C86_INLINE word_t
cpu_gen_read_w(cpu_t *cpu, const uint8_t reg) {
    return cpu->reg_file.gen[reg];
}

C86_INLINE word_t
cpu_seg_read(cpu_t *cpu, const uint8_t reg) {
    return cpu->reg_file.seg[reg];
}

C86_INLINE void
cpu_seg_write(cpu_t *cpu, const uint8_t reg, const word_t val) {
    cpu->reg_file.seg[reg] = val;
}

#endif
