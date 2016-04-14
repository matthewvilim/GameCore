/*
 * Core 8086 Copyright (C) 2014 Matthew Vilim
 *
 * src/cpu/x86_instr.h
 */

#ifndef _INSTR_H
#define _INSTR_H

typedef struct instr {
    uint8 len : 4;

    struct modrm {
        uint8 reg : 3;
        union {
            uint8 r : 3;
            struct m {
                uint8 scale : 2;
                uint8 index : 3;
                uint8 base : 3;
                union {
                    sword disp16;
                    sdword disp32;
                };
            };
        };
    };

    ubyte instr_prefix;

    struct flags {
        uint8 seg_prefix : 1;
        uint8 op_size : 1;
        uint8 addr_size : 1;
    }

    instr_exe *exe;
} instr;

INLINE_FORCE udword_t
_calc_addr(const cpu *cpu, const instr *instr) {
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
