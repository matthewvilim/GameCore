/*
 * Core 8086 Copyright (C) 2014 Matthew Vilim
 *
 * src/shared/macros.h
 */

#include <gc_emu.h>

typedef struct gc_emu {
    cpu cpu;
    mem mem;
} gc_emu_t, *gc_emu_handle;

gc_error_t
gc_emu_alloc(gc_emu_handle *handle, gc_emu_config *config) {
    gc_error error = GC_NO_ERROR;
    if (!handle) {
        error = GC_ARG_ERROR
        goto error_ret;
    }

    gc_emu *emu = malloc(sizeof(*emu);
    if (!emu) {
        error = GC_MALLOC_ERROR;
        goto error_ret;
    }

    if (error = cpu_init(emu->cpu) {
        goto error_cpu;
    }
    if (error = mem_init(emu->cpu) {
        goto error_mem;
    }

    *handle = emu;
    INFO("Emulator initialized!");
    goto error_ret;

    error_mem:
        mem_release(emu->mem);
    error_cpu:
        cpu_release(emu->cpu);
    error_ret:
    return error;
}

gc_error_t
gc_emu_dealloc(gc_emu_handle handle) {
    gc_error error = GC_NO_ERROR;
    if (!handle) {
        error = GC_ARG_ERROR;
        goto error_ret;
    }

    gc_emu *emu = handle;
    if (error = cpu_dealloc(emu->cpu) {
        goto error_cpu;
    }
    if (error = mem_dealloc(emu->cpu) {
        goto error_mem;
    }
    free(emu);
    goto error_ret;

    error_mem:
        mem_dealloc(emu->mem);
    error_cpu:
        cpu_dealloc(emu->cpu);
    error_ret:
    return error;
}
