/**********************************************************************************
 *                                                                                *
 * The MIT License (MIT)                                                          *
 *                                                                                *
 * Core 8086                                                                      *
 * Copyright (c) 2014 Matthew Vilim                                               *
 *                                                                                *
 * Permission is hereby granted, free of charge, to any person obtaining a copy   *
 * of this software and associated documentation files (the "Software"), to deal  *
 * in the Software without restriction, including without limitation the rights   *
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell      *
 * copies of the Software, and to permit persons to whom the Software is          *
 * furnished to do so, subject to the following conditions:                       *
 *                                                                                *
 * The above copyright notice and this permission notice shall be included in all *
 * copies or substantial portions of the Software.                                *
 *                                                                                *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR     *
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,       *
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE    *
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER         *
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,  *
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE  *
 * SOFTWARE.                                                                      *
 *                                                                                *
 **********************************************************************************/

#include <stdlib.h>

#ifndef CPU_H
#define CPU_H

// NOTE: C bitfields do NOT guarantee ordering and should be avoided when mapping to HW registers

/******************
 * REGISTER MASKS *
 ******************/

#define FLAG_MASK_CARRY               (0x1 << 0)
#define FLAG_MASK_RESERVED1           (0x1 << 1)
#define FLAG_MASK_PARITY              (0x1 << 2)
#define FLAG_MASK_RESERVED3           (0x1 << 3)
#define FLAG_MASK_ADJUST              (0x1 << 4)
#define FLAG_MASK_RESERVED5           (0x1 << 5)
#define FLAG_MASK_ZERO                (0x1 << 6)
#define FLAG_MASK_SIGN                (0x1 << 7)
#define FLAG_MASK_TRAP                (0x1 << 8)
#define FLAG_MASK_INTERRUPT_ENABLE    (0x1 << 9)
#define FLAG_MASK_DIRECTION           (0x1 << 10)
#define FLAG_MASK_OVERFLOW            (0x1 << 11)
#define FLAG_MASK_RESERVED12_15       (0xF << 12)

typedef void (*instr_gen_t)(cpu_t *cpu);

typedef union reg {
    struct {
        union {
            struct {
                uint8_t l8, h8;
            };
            uint16_t reg16;
        };
        uint16_t pad;
    };
    uint32_t reg32;
} reg_t;

typedef struct reg_file {
    // general purpose
    reg_t gen[8];
    // instruction pointer
    uint16_t ip;
    // segment
    uint16_t cs;
    uint16_t ds;
    uint16_t es;
    uint16_t ss;
    // flags
    uint16_t flags;
} reg_file_t;

typedef struct cpu {
    reg_file_t reg_file;
    
    instr_gen_t instr_gen;
} cpu_t;

#endif