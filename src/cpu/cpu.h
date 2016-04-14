/*
 * Core 8086 Copyright (C) 2014 Matthew Vilim
 *
 * src/shared/macros.h
 */

#include <stdlib.h>

#ifndef CPU_H
#define CPU_H

gc_error cpu_init(cpu *cpu, mem *mem);
gc_error cpu_term(cpu *cpu);

#endif
