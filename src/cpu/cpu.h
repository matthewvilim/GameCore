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
        union gen[8] {
            word_t w;
            byte_t b[2];
        }
        // segment registers
        word_t seg[4];
        // instruction pointer
        word_t ip;
        // flags
        word_t flags;
    };

    mem_t *mem;
} cpu_t;

C86_INLINE word_t *
cpu_ip_host(const cpu_t *cpu) {
    return &cpu->reg_file.ip;
}

C86_INLINE word_t *
cpu_flags_host(const cpu_t *cpu) {
    return &cpu->reg_file.flags;
}

C86_INLINE byte_t *
cpu_gen_b_host(const cpu_t *cpu, const uint8_t reg) {
    size_t index = reg & BIT(2) ? BYTE_LOW_INDEX : BYTE_HIGH_INDEX;
    return &cpu->reg_file.gen[reg & ~BIT(2)].b[index];
}

C86_INLINE word_t *
cpu_gen_w_host(const cpu_t *cpu, const uint8_t reg) {
    return &cpu->reg_file.gen[reg];
}

C86_INLINE word_t *
cpu_seg_host(const cpu_t *cpu, const uint8_t reg) {
    return &cpu->reg_file.seg[reg];
}

#endif
