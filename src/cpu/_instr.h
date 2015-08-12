/*
 * Core 8086 Copyright (C) 2014 Matthew Vilim
 *
 * src/cpu/x86_instr.h
 */

#ifndef _INSTR_H
#define _INSTR_H

typedef struct instr {
    uint8_t len : 4;

    struct modrm {
        uint8_t reg : 3;
        union {
            uint8_t r : 3;
            struct m {
                uint8_t scale : 2;
                uint8_t index : 3;
                uint8_t base : 3;
                union {
                    sword_t disp16;
                    sdword_t disp32;
                };
            };
        };
    };

    ubyte_t instr_prefix;

    struct flags {
        uint8_t seg_prefix : 1;
        uint8_t op_size : 1;
        uint8_t addr_size : 1;
    }

    instr_calc_addr_t *calc_addr;
    instr_exe_t *exe;
} instr_t;

INLINE_FORCE udword_t
_calc_addr(const cpu_t *cpu, const instr_t *instr) {
    if (instr->addr16) {
        return cpu_gen_read_w(cpu, instr->modrm.m.base) +
               cpu_gen_read_w(cpu, instr->modrm.m.index) +
               instr->modrm.m.disp16;
    } else {
        return cpu_gen_read_dw(cpu, instr->modrm.m.base) +
              (cpu_gen_read_dw(cpu, instr->modrm.m.index) << instr->modrm.m.scale) +
               instr->modrm.m.disp32;
    }

}

#endif
