/*
 * GameCore Copyright (C) 2014 Matthew Vilim
 *
 * src/shared/macros.h
 */

#ifndef MEM_H
#define MEM_H

#define MEM_ADDRESSABILITY_BYTES     1
#define MEM_SEGMENT_ADDRESS_SPACE    (1 << 16) // 64 KB
#define MEM_MASK_SEGMENT_ADDRESS     (MEM_SEGMENT_ADDRESS_SPACE - 1)
#define MEM_LINEAR_ADDRESS_SPACE     (1 << 20) // 1 MB
#define MEM_MASK_LINEAR_ADDRESS      (MEM_LINEAR_ADDRESS_SPACE - 1)

typedef byte_t (*mem_read_b_t)(const cpu_t *cpu);
typedef word_t (*mem_read_w_t)(const cpu_t *cpu);
typedef dword_t (*mem_read_dw_t)(const cpu_t *cpu);
typedef void (*mem_write_b_t)(const cpu_t *cpu, const byte_t val);
typedef void (*mem_write_w_t)(const cpu_t *cpu, const word_t val);
typedef void (*mem_write_dw_t)(const cpu_t *cpu, const dword_t val);

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

typedef dword_t addr_offset_t;

typedef dword_t addr_virt_t;
typedef dword_t addr_phys_t;

typedef struct mem {
    byte_t *base;

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
