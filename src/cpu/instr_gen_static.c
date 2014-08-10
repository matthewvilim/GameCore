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

#include "instr_gen_static.h"

#include "instructions.h"

static void _gen_static(cpu_t *cpu);

void init_instr_gen_static(cpu_t *cpu) {
    cpu->instr_gen = _gen_static;
}

// Most modern architectures use barrel shifters instead of serial shifters, yielding O(1) shift time.
// So, for convenience, it's fine to shift register fields instead of reading them in place.
// Since not all instructions' reg, mod, r/m, etc. fields are at the same index, each instruction's implementation function
// will pass the decoded values here directly.
static inline linear_addr_t _calc_effective_addr(op_info_t *op_info, reg_file_t *reg_file) C86_INLINE {
    linear_addr_t effective_addr;
    switch (rm) {
        case INSTR_RM_BX+SI:
            effective_addr = reg_file->bx + reg_file->si; break;
        case INSTR_RM_BX+DI:
            effective_addr = reg_file->bx + reg_file->di; break;
        case INSTR_RM_BP+SI:
            effective_addr = reg_file->bp + reg_file->si; break;
        case INSTR_RM_BP+DI:
            effective_addr = reg_file->bp + reg_file->di; break;
        case INSTR_RM_SI:
            effective_addr = reg_file->si; break;
        case INSTR_RM_DI:
            effective_addr = reg_file->di; break;
        case INSTR_RM_BP_OR_DIR_ADDR:
            effective_addr = reg_file->bp; break;
        case INSTR_RM_BX:
            effective_addr = reg_file->bx; break;
        default: break; // TODO: handle error
    }
    switch (mod) {
        case INSTR_MOD_NO_DISP:
            // override address calculated above
            if (rm == INSTR_RM_BP_OR_DIR_ADDR) {
                effective_addr = ((uint16_t *)instr)[1];
            }
            break;
        case INSTR_MOD_B_DISP:
            effective_addr += instr[2]; break;
        case INSTR_MOD_W_DISP:
            effective_addr += ((uint16_t *)instr)[1]; break;
        case INSTR_MOD_REG:
        default: break; // TODO: handle error
    }
    return effective_addr;
}



static inline uint8_t * _calc_addr_mod_rm_b(reg_file_t *reg_file, uint8_t *instr, uint8_t mod, uint8_t rm) C86_INLINE {
    switch (mod) {
        case INSTR_MOD_NO_DISP:
        case INSTR_MOD_B_DISP:
        case INSTR_MOD_W_DISP:
            linear_addr_t linear_addr = _calc_effective_addr(reg_file, instr, mod, rm); break;
            
        case INSTR_MOD_REG:
        default: break; // TODO: handle error
    }
}

static inline uint8_t * _fetch_instr(reg_file_t *reg_file, mem_t *mem) {
    return mem->base + mem_calc_linear_addr(reg_file->cs, reg_file->ip);
}

void _gen_static(cpu_t *cpu, mem_t *mem) {
    linear_addr_t = _fetch_instr(cpu, mem);
    instr_t *instr = { .op_info =  }
    uint8_t *instr = mem->base + cpu->reg_file.ip;
    op_info_t *op_info = op_table + *instr;
    // some instructions are variable length; we'll increment IP again for those below
    cpu->reg_file.ip += op_info.size;
    switch (op_info.opcode) {
        case OPCODE_ADD_REG_MEM: _add_b_reg_to_mem(cpu, mem); break;
        default:
            break;
    }
}
