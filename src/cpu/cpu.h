/*
 * Core 8086 Copyright (C) 2014 Matthew Vilim
 *
 * src/shared/macros.h
 */

#include <stdlib.h>

#ifndef CPU_H
#define CPU_H

typedef uint8_t ubyte;
typedef sint8_t sbyte;
typedef uint16_t uword;
typedef sint16_t sword;
typedef uint32_t udword;
typedef sint32_t sdword;

typedef union byte {
    ubyte u;
    sbyte s;
} byte;

typedef union word {
    uword u;
    sword s;
} word;

typedef union dword {
    udword u;
    sdword s;
} dword;

gc_error cpu_init(cpu *cpu, mem *mem);
gc_error cpu_term(cpu *cpu);

#endif
