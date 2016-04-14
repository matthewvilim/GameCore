/*
 * Core 8086 Copyright (C) 2014 Matthew Vilim
 *
 * src/cpu/x86_instr.h
 */

#ifndef _INSTR_H
#define _INSTR_H

typedef struct instr {
    byte prefix;

    unsigned int len : 4;

    struct op1, op2 {
        instr_op handler;
        union {
            reg reg : 3;
            struct addr {
                reg base : 3;
                reg index : 3;
                unsigned int scale : 2;
                dword disp;
            };
        };
    };

    struct flags {
        unsigned int seg_prefix : 1;
        unsigned int op_size : 1;
        unsigned int addr_size : 1;
    }

    instr_exe *exe;
} instr;

INLINE_FORCE dword
_calc_addr(const instr *instr, const reg_file *reg_file) {
        return reg_file_read_dw(reg_file, instr->addr.base) +
              (reg_file_read_dw(reg_file, instr->addr.index) << instr->addr.scale) +
               instr->addr.disp;
}

#endif
