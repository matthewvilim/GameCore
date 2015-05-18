/*
 * Game Core Copyright (C) 2014 Matthew Vilim
 *
 * src/shared/macros.h
 */

#ifndef GC_EMULATOR_H
#define GC_EMULATOR_H

#include "cpu.h"

typedef struct gc_emu gc_emu_t;

void gc_emu_init(c86_emu_t **emu);
void gc_emu_terminate(c86_emu_t *emu);

#endif
