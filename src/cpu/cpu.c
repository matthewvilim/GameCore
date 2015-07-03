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

    lin_addr_t addr;
    addr.base = *cpu_seg_host(cpu, X86_REG_CS);
    addr.offset = *cpu_ip_host(cpu);
    instr.addr; = mem_addr_host(cpu->mem, addr);

    for (bool done = false, int i = 0; !done; i++) {
        byte_t prefix = instr.addr[i];
        switch (prefix) {
            case X86_PREFIX_REP:
            case X86_PREFIX_REPE_REPZ:
            case X86_PREFIX_REPNE_REPNZ:
            case X86_PREFIX_LOCK:
                instr.instr_prefix = prefix;
                break;
            case X86_PREFIX_OVERRIDE_CS:
                instr.seg_prefix = true;
                instr.seg = seg;
            case X86_PREFIX_OVERRIDE_SS:
                instr.seg_prefix = true;
                instr.seg = seg;
            case X86_PREFIX_OVERRIDE_DS:
                instr.seg_prefix = true;
                instr.seg = seg;
            case X86_PREFIX_OVERRIDE_ES:
                instr.seg_prefix = true;
                instr.seg = seg;
                break;
            default:
                instr.len = i;
                done = true;
                break;
        }
    }

    instr->modrm.mod = BIT_FIELD_READ(modrm, X86_MODRM_MOD_MASK);
    if (instr->modrm.mod != 3) {
        if (instr->flags & ADDR16) {

            instr->calc_addr = calc_addr16_table_modrm[modrm];
        } else {
            instr->modrm.base = BIT_FIELD_READ(modrm, X86_MODRM_REG_MASK);

            instr->calc_addr = calc_addr32_table_modrm[modrm];
            if (!instr->calc_addr) {
                instr->modrm.scale = BIT_FIELD_READ(sib, X86_SIB_SCALE_MASK);
                instr->modrm.index = BIT_FIELD_READ(sib, X86_SIB_INDEX_MASK);
                instr->modrm.base = BIT_FIELD_READ(sib, X86_SIB_BASE_MASK);

                instr->calc_addr = calc_addr32_table_sib[sib][instr->modrm.mod != 0];
            }
        }
    } else {
        instr->calc_addr = NULL;
    }


    byte_t opcode = mem_addr_host(cpu->mem, instr.addr[0]);
    op_info_t *op_info = op_table[opcode];

    if (!instr.seg_prefix) {
        instr.seg = op_info->group.seg;
    }

    op_info->get_ops(cpu, instr);
    op_info->exe(cpu, instr);

    *cpu_ip_host(cpu) += instr.len;
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
