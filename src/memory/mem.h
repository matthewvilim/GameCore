/*
 * GameCore Copyright (C) 2014 Matthew Vilim
 *
 * src/shared/macros.h
 */

#ifndef MEM_H
#define MEM_H

typedef ubyte_t (*mem_read_b_t)(const cpu_t *cpu, const uint8_t seg, const addr_virt_t addr);
typedef uword_t (*mem_read_w_t)(const cpu_t *cpu, const uint8_t seg, const addr_virt_t addr);
typedef udword_t (*mem_read_dw_t)(const cpu_t *cpu, const uint8_t seg, const addr_virt_t addr);
typedef void (*mem_write_b_t)(const cpu_t *cpu, const uint8_t seg, const addr_virt_t addr, const ubyte_t val);
typedef void (*mem_write_w_t)(const cpu_t *cpu, const uint8_t seg, const addr_virt_t addr, const uword_t val);
typedef void (*mem_write_dw_t)(const cpu_t *cpu, const uint8_t seg, const addr_virt_t addr, const udword_t val);

typedef struct mem_handler_read {
    mem_read_b_t b;
    mem_read_w_t w;
    mem_read_dw_t dw;
} mem_handler_read_t;

typedef struct mem_handler_write {
    mem_write_b_t b;
    mem_write_w_t w;
    mem_write_dw_t dw;
} mem_handler_write_t;

extern const mem_handler_read_t mem_real_read;
extern const mem_handler_write_t mem_real_write;
extern const mem_handler_read_t mem_protected_read;
extern const mem_handler_write_t mem_protected_write;

typedef udword_t addr_virt_t;
typedef udword_t addr_lin_t;
typedef udword_t addr_phys_t;

typedef struct mem {
    ubyte_t *base;

    mem_handler_read_t read;
    mem_handler_write_t write;
} mem_t;

GC_INLINE void
mem_setup_real(mem_t *mem) {
    mem->read = mem_real_read;
    mem->write = mem_real_write;
}

GC_INLINE void
mem_setup_protected(mem_t *mem) {
    mem->read = mem_protected_read;
    mem->write = mem_protected_write;
}

#endif
