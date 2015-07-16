/*
 * Game Core Copyright (C) 2014 Matthew Vilim
 *
 * src/shared/macros.h
 */

#ifndef GC_EMULATOR_H
#define GC_EMULATOR_H

#include <gc_error.h>

typedef struct gc_emu *gc_emu_handle_t;

typedef struct gc_emu_config {

} gc_emu_config_t;

void gc_emu_alloc(gc_emu_handle_t *handle, gc_emu_config_t *config);
void gc_emu_release(gc_emu_handle_t *handle);

#endif
