/*
 * Game Core Copyright (C) 2014 Matthew Vilim
 *
 * src/cpu/cpu.c
 */

#include "cpu.h"

C86_INLINE void
gen_writeb(reg_file_t *reg_file, reg_t reg, byte_t val) {
    word_t mask = reg & BIT(2) ? MASK_HIGH_B : MASK_LOW_B;
    MASK_SET_VAL(reg_file->gen[reg & ~BIT(2)], mask, val);
}

C86_INLINE void
gen_writew(reg_file_t *reg_file, reg_t reg, word_t val) {
    MASK_SET_VAL(reg_file->gen[reg->idx], reg->mask, val);
}

C86_INLINE byte_t
gen_readb(reg_file_t *reg_file, reg_t reg) {
    word_t mask = reg & BIT(2) ? MASK_HIGH_B : MASK_LOW_B;
    return MASK_GET_VAL(reg_file->gen[reg & ~BIT(2)], mask);
}

C86_INLINE word_t
gen_readw(reg_file_t *reg_file, reg_t reg) {
    return MASK_GET_VAL(reg_file->gen[reg], MASK_W);
}

C86_INLINE word_t
seg_read(reg_file_t *reg_file, reg_t reg) {
    return reg_file->seg[reg];
}

C86_INLINE void
seg_write(reg_file_t *reg_file, reg_t reg, word_t val) {
    reg_file->seg[reg] = val;
}

gc_error_t
cpu_init(cpu_t *cpu, mem_t *mem) {
    if (!cpu) return GC_ARG_ERROR;
    
    cpu->mem = mem;
    
    return GC_NO_ERROR;
}

gc_error_t
cpu_terminate(cpu_t *cpu) {
    if (!cpu) return GC_ARG_ERROR;
    
    cpu->mem = NULL;
    
    return GC_NO_ERROR;
}

gc_error_t
_fetch(cpu_t *cpu) {
    word_t cs = seg_read(cpu->reg_file, X86_REG_CS);
    
    cpu->decode.instr_addr = mem_lin_addr_calc(cs, cpu->reg_file.ip);
    return GC_NO_ERROR;
}

GC_INLINE gc_error_t
_decode(cpu_t *cpu) {
    decode_t *decode = &cpu->decode;
    
    byte_t *prefix_host = mem_host_addr_calc(mem, decode->instr);
    
    // decode instruction prefixes
    for (int i = 0; ; i++) {
        switch (prefix_host[i]) {
            case X86_PREFIX_REP:
            case X86_PREFIX_REPE_REPZ:
            case X86_PREFIX_REPNE_REPNZ:
            case X86_PREFIX_LOCK:
                decode->prefix_instr = prefix_host[i];
                break;
            case X86_PREFIX_OVERRIDE_CS:
            case X86_PREFIX_OVERRIDE_SS:
            case X86_PREFIX_OVERRIDE_DS:
            case X86_PREFIX_OVERRIDE_ES:
                decode->prefix_seg = prefix_host[i];
                break;
            default:
                decode->prefix_len = i;
                break;
        }
    }
    
    byte_t *instr_host = prefix_host + decode->prefix_len;
    size_t len = 0;
    
    op_info_t *op_info = op_table[instr_host[0]];
    
    // decode ModR/M byte
    switch (op_info->src) {
        AddressingCodeE:
            len++;
            switch (instr_host[1]) {
                case X86_MOD_NO_DISP:
                    break;
                case X86_MOD_B_DISP:
                    break;
                case X86_MOD_W_DISP:
                    break;
                case X86_MOD_REG:
                    break;
            }
            break;
        AddressingCodeG:
        AddressingCodeS:
            decode->src.reg = 
            break;
        default: break;
    }
    
    decode->instr_len = len;
}

gc_error_t
_execute(cpu_t *cpu) {
    
}

gc_error_t
_writeback(cpu_t *cpu) {
    
}