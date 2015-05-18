/*
 * Game Core Copyright (C) 2014 Matthew Vilim
 *
 * src/cpu/cpu.c
 */

#include "cpu.h"
vtable_t vtable_real {
    .decode = _
};

vtable_t vtable_protected {
    
};
gc_error_t
cpu_init(cpu_t *cpu) {
    if (!cpu) {
        return GC_ARG_ERROR;
    }
    // x86 maintains backwards compatibility by starting in real mode
    cpu->protected_mode = false;
    
    return GC_NO_ERROR
}

gc_error_t
_real_init(cpu_t *cpu) {
    cpu->
}

gc_error_t
_protected_init(cpu_t *cpu) {
    cpu->
}