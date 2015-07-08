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

<<<<<<< HEAD
        modrm_info_t *modrm_info;
        uint8_t disp_size;
        if (instr->flags & ADDR16) {
            modrm_info = modrm_info_table16 + modrm;

            instr->addr_calc = modrm_info->calc_addr;
            if (modrm_info->calc_addr) {
                disp_size = modrm_info->disp_size;

                instr->modrm.m.base = modrm_info->base;
                instr->modrm.m.index = modrm_info->index;
            } else {
                instr->modrm.r = BIT_FIELD_READ(modrm, X86_MODRM_RM_MASK);
            }
        } else {
            modrm_info = modrm_info_table32 + modrm;
=======
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
>>>>>>> origin/master

            instr->addr_calc = modrm_info->calc_addr;
            if (modrm_info->calc_addr) {
                disp_size = modrm_info->disp_size;

                if (modrm_info->sib) {
                    instr->modrm.m.base = BIT_FIELD_READ(sib, X86_SIB_BASE_MASK);
                    instr->modrm.m.index = BIT_FIELD_READ(sib, X86_SIB_INDEX_MASK);
                    instr->modrm.m.scale = BIT_FIELD_READ(sib, X86_SIB_SCALE_MASK);

                    if (BIT_FIELD_READ(modrm, X86_MODRM_MOD_MASK) == 0x0 && instr->modrm.m.base == 0x5) {
                        instr->calc_addr = modrm_info_sib_override.calc_addr;
                        disp_size = modrm_info_sib_override.disp_size;
                    }
                } else {
                    instr->modrm.m.base = BIT_FIELD_READ(modrm, X86_MODRM_RM_MASK);
                }
            } else {
                instr->modrm.r = BIT_FIELD_READ(modrm, X86_MODRM_RM_MASK);
            }

        }
        instr->modrm.reg = BIT_FIELD_READ(modrm, X86_MODRM_REG_MASK);
}
