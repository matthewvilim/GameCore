/*
 * Core 8086 Copyright (C) 2014 Matthew Vilim
 *
 * src/shared/macros.h
 */

#include <gc_emulator.h>

typedef struct gc_emu {
    cpu_t cpu;
    mem_t mem;
} gc_emu_t;

gc_error_t
gc_emu_init(gc_emu_t **emu) {
    gc_error_t error;
    if (!emu) {
        error = GC_ARG_ERROR
        goto error;
    }
    
    gc_emu_t *emulator;
    if (!emulator = malloc(sizeof(*emulator))) {
        error = GC_MALLOC_ERROR;
        goto error;
    }
    
    if (error = cpu_init(emulator->cpu) ||
        error = mem_init(emulator->mem)) {
        gc_emu_term(emulator);
        goto error;
    }
    
    INFO("Emulator initialized!");
    *emu = emulator;
    return GC_NO_ERROR;
    
    error:
    ERROR_DESC("Emulator initialization failed", error);
    gc_emu_term(emulator);
    return error;
}

gc_error_t
gc_emu_term(gc_emu_t *emu) {    
    if (!emu) {
        return GC_ARG_ERROR;
    }
    
    gc_error_t error;
    if (error = cpu_term(emu->cpu) ||
        error = mem_term(emu->mem)) {
        return error;
    }
    
    free(emu);
    
    return GC_NO_ERROR;
}