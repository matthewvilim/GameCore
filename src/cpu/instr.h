/*
 * Core 8086 Copyright (C) 2014 Matthew Vilim
 *
 * src/cpu/x86_instr.h
 */

#ifndef INSTR_H
#define INSTR_H

typedef uint8_t ubyte_t;
typedef uint16_t uword_t;
typedef uint32_t udword_t;
typedef sint8_t sbyte_t;
typedef sint16_t sword_t;
typedef sint32_t sdword_t;

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

    instr_calc_addr_t calc_addr;
    instr_exe_t exe;
} instr_t;

extern op_group_t add;

extern op_info_t add_eb_gb;

extern const op_info_t op_table[];

#endif
