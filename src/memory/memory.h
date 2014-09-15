/**********************************************************************************
 *                                                                                *
 * The MIT License (MIT)                                                          *
 *                                                                                *
 * Core 8086                                                                      *
 * Copyright (c) 2014 Matthew Vilim                                               *
 *                                                                                *
 * Permission is hereby granted, free of charge, to any person obtaining a copy   *
 * of this software and associated documentation files (the "Software"), to deal  *
 * in the Software without restriction, including without limitation the rights   *
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell      *
 * copies of the Software, and to permit persons to whom the Software is          *
 * furnished to do so, subject to the following conditions:                       *
 *                                                                                *
 * The above copyright notice and this permission notice shall be included in all *
 * copies or substantial portions of the Software.                                *
 *                                                                                *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR     *
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,       *
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE    *
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER         *
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,  *
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE  *
 * SOFTWARE.                                                                      *
 *                                                                                *
 **********************************************************************************/

#ifndef MEMORY_H
#define MEMORY_H

#define MEM_ADDRESSABILITY_BYTES     1
#define MEM_SEGMENT_ADDRESS_SPACE    (1 << 16) // 64 KB
#define MEM_MASK_SEGMENT_ADDRESS     (MEM_SEGMENT_ADDRESS_SPACE - 1)
#define MEM_LINEAR_ADDRESS_SPACE     (1 << 20) // 1 MB
#define MEM_MASK_LINEAR_ADDRESS      (MEM_LINEAR_ADDRESS_SPACE - 1)

typedef uint8_t byte_t;
typedef uint16_t word_t;
typedef uint32_t long_t;

typedef uint16_t seg_addr_t; // internal address bus is 16 bits
typedef uint32_t linear_addr_t; // external address bus is 20 bits

typedef struct {
    uint8_t *base;
} mem_t;

static inline uint8_t mem_read_b(mem_t *mem, linear_addr_t addr) {
    return *(base + addr);
}

static inline uint16_t mem_read_w(mem_t *mem, linear_addr_t addr) {
    return *(uint16_t *)(base + addr);
}

static inline void mem_write_b(mem_t *mem, linear_addr_t addr, uint8_t val) {
    return *(base + addr) = val;
}

static inline void mem_write_w(mem_t *mem, linear_addr_t addr, uint16_t val) {
    *(uint16_t *)(base + addr) = val;
}

static inline linear_addr_t mem_calc_linear_addr(seg_addr_t base, seg_addr_t offset) C86_INLINE {
    return ((((linear_addr_t)base) << 4) + offset) & MEM_MASK_PHYS_ADDRESS;
}

#endif