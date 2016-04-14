/*
 * Game Core Copyright (C) 2014 Matthew Vilim
 *
 * src/shared/macros.h
 */

#ifndef EMU_H
#define EMU_H

#include "error.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct gc_emu *gc_emu_handle;

typedef struct gc_emu_config {

} gc_emu_config;

void gc_emu_alloc(gc_emu_handle *handle, gc_emu_config *config);
void gc_emu_release(gc_emu_handle *handle);

#ifdef __cplusplus
}
#endif

#endif
