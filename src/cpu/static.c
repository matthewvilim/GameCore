/*
 * Core 8086 Copyright (C) 2014 Matthew Vilim
 *
 * src/shared/macros.h
 */

#include "instr_gen_static.h"

#include "instructions.h"

static void _instr_gen_static(cpu_t *cpu);

extern const vtable_t vtable_real = {
    .decode = _decode
}

extern const vtable_t vtable_protected = {
    
}

gc_error_t
instr_gen_static_init(cpu_t *cpu) {
    if (!cpu) {
        return GC_ARG_ERROR;
    }
    cpu->instr_gen = _instr_gen_static;
    
    return GC_NO_ERROR
}

GC_INLINE gc_error_t
_decode(cpu_t *cpu, mem_t *mem) {
    long_t eip = cpu->reg_file.eip;
    byte_t opcode = mem_read_b(mem, eip);
    op_info_t *info = &op_table[opcode];
    
    // determine operant size
    _decode_operant_size(cpu);
    
    // decode addressing support
    for (addressing_t addr = info->addressing, i; addr; addr &= ~i) {
        i = LOW_BIT(info->addressing)
        switch (i) {
            case ADDRESSING_E:
                _decode_modrm(cpu);
            case ADDRESSING_G:
        }
    }
    return GC_NO_ERROR
}

GC_INLINE gc_error_t
_decode_operant_size(cpu_t *cpu) {
    
}

GC_INLINE gc_error_t
_decode_modrm(cpu_t *cpu, byte_t *modrm, operand_size_t size, dword_t *addr) {
    uint8_t mod = MASK_GET_VAL(*modrm, INSTR_MODRM_MOD_MASK);
    switch (mod) {
        case INSTR_MOD_REG:
            uint8_t rm = MASK_GET_VAL(*modrm, INSTR_MODRM_RM_MASK);
            
            dword_t mask;
            uint8_t reg;
            
            switch (size) {
                case OPERAND_SIZE_BYTE:
                    mask = rm & 0x4 ? MASK_HIGH_B : MASK_LOW_B;
                    reg = rm & ~0x4;
                    break;
                case OPERAND_SIZE_WORD:
                    mask = MASK_LOW_W;
                    reg = rm;
                    break;
                case OPERAND_SIZE_DWORD:
                    mask = MASK_DWORD;
                    reg = rm;
                    break;
                default: break;
            }
            break;
    }
    
    if (cpu_vm(cpu)) {
        switch (mod) {
            case INSTR_MOD_NO_DISP:
                switch (rm) {
                    case 0x0:
                        break;
                    case 0x1:
                        break;
                    case 0x2:
                        break;
                    case 0x3:
                        break;
                    case 0x4:
                        break;
                    case 0x5:
                        break;
                    case 0x6:
                        break;
                    case 0x7:
                        break;
                }
                break;
            default:
        }
    } else {
        
    }
}

GC_INLINE void
_modrm_decode_real(byte_t modrm, instr_t *instr, reg_file_t *reg_file) {

    
    
    
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
    return GC_NO_ERROR;
}

GC_INLINE linear_addr_t
_protected_addr_calc

// Most modern architectures use barrel shifters instead of serial shifters, yielding O(1) shift time.
// So, for convenience, it's fine to shift register fields instead of reading them in place.
// Since not all instructions' reg, mod, r/m, etc. fields are at the same index, each instruction's implementation function
// will pass the decoded values here directly.
static inline linear_addr_t _calc_effective_addr(op_info_t *op_info, reg_file_t *reg_file) {
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
