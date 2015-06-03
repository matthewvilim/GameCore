/*
 * Game Core Copyright (C) 2014 Matthew Vilim
 *
 * src/cpu/cpu.c
 */

#include "cpu.h"

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

void
_emulate(cpu_t *cpu, size_t cycles) {

}

void
_emulate_instr(cpu_t *cpu) {
    instr_t instr;

    instr.instr_addr = { .base = cpu_seg_read(cpu, X86_REG_CS), .offset = cpu_ip_read(cpu) };

    for (bool done = false, int i = 0; !done; i++) {
        lin_addr_t prefix_addr = instr.instr_addr;
        prefix_addr.offset += i;
        byte_t prefix = mem_readb(cpu->mem, prefix_addr);
        switch (prefix) {
            case X86_PREFIX_REP:
            case X86_PREFIX_REPE_REPZ:
            case X86_PREFIX_REPNE_REPNZ:
            case X86_PREFIX_LOCK:
                instr.instr_prefix = prefix;
                break;
            case X86_PREFIX_OVERRIDE_CS:
                instr.seg = X86_REG_CS;
            case X86_PREFIX_OVERRIDE_SS:
                instr.seg = X86_REG_SS;
            case X86_PREFIX_OVERRIDE_DS:
                instr.seg = X86_REG_DS;
            case X86_PREFIX_OVERRIDE_ES:
                instr.seg = X86_REG_ES;
                break;
            default:
                instr.instr_addr.offset += i;
                instr.len = i;
                done = true;
                break;
        }
    }

    byte_t opcode = mem_readb(cpu->mem, prefix_addr);
    op_info_t *op_info = op_table[opcode];


}

GC_INLINE void
_decode_addressing(cpu_t *cpu, decode_t *decode) {
    switch (addressing_code) {
        AddressingCodeE:
            decode->instr_len++;

            lin_addr_t *addr = &decode->addr;

            decode->mod = BIT_FIELD_READ(instr_host[1], X86_MODRM_MOD_MASK);
            decode->rm = BIT_FIELD_READ(instr_host[1], X86_MODRM_RM_MASK);
            decode->reg = BIT_FIELD_READ(instr_host[1], X86_MODRM_REG_MASK);

            switch (mod) {
                case X86_MOD_NO_DISP:
                case X86_MOD_B_DISP:
                case X86_MOD_W_DISP:
                    switch (rm) {
                        case X86_RM_BX_PLUS_SI:
                            addr->offset = cpu_gen_read_w(reg_file, X86_REG_BX) +
                                           cpu_gen_read_w(reg_file, X86_REG_SI);
                            break;
                        case X86_RM_BX_PLUS_DI:
                            addr->offset = cpu_gen_read_w(reg_file, X86_REG_BX) +
                                           cpu_gen_read_w(reg_file, X86_REG_DI);
                            break;
                        case X86_RM_BP_PLUS_SI:
                            addr->offset = cpu_gen_read_w(reg_file, X86_REG_BP) +
                                           cpu_gen_read_w(reg_file, X86_REG_SI);
                            break;
                        case X86_RM_BP_PLUS_DI:
                            addr->offset = cpu_gen_read_w(reg_file, X86_REG_BP) +
                                           cpu_gen_read_w(reg_file, X86_REG_DI);
                            break;
                        case X86_RM_SI:
                            addr->offset = cpu_gen_read_w(reg_file, X86_REG_SI);
                            break;
                        case X86_RM_DI:
                            addr->offset = cpu_gen_read_w(reg_file, X86_REG_DI);
                            break;
                        case X86_RM_BP_OR_DIR_ADDR:
                            addr->offset = mod != X86_MOD_NO_DISP ?
                                           cpu_gen_read_w(reg_file, X86_REG_BP) :
                                           *(word_t *)(instr_host + 2);
                            break;
                        case X86_RM_BX:
                            addr->offset = reg_gen_read_w(reg_file, X86_REG_BX);
                            break;
                        default: break;
                    }
                    break;
                default: break;
            }

            switch (mod) {
                case X86_MOD_B_DISP:
                    decode->instr_len++;
                    addr->offset += instr_host[2];
                case X86_MOD_W_DISP:
                    decode->instr_len += 2;
                    addr->offset += *(word_t *)(instr_host + 2);
                default: break;
            }

            break;
        default: break;
    }
}


GC_INLINE void
_decode_prefix(cpu_t *cpu, decode_t *decode) {
    decode->prefix_len = 0;

    for (bool done = false, int i = 0; !done; i++) {
        switch (decode->prefix[i]) {
            case X86_PREFIX_REP:
            case X86_PREFIX_REPE_REPZ:
            case X86_PREFIX_REPNE_REPNZ:
            case X86_PREFIX_LOCK:
                decode->prefix_instr = decode->prefix[i];
                break;
            case X86_PREFIX_OVERRIDE_CS:
            case X86_PREFIX_OVERRIDE_SS:
            case X86_PREFIX_OVERRIDE_DS:
            case X86_PREFIX_OVERRIDE_ES:
                decode->prefix_seg = decode->prefix[i];
                break;
            default:
                done = true;
                decode->prefix_len = i;
                break;
    }
}
