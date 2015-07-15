/*
 * Game Core Copyright (C) 2014 Matthew Vilim
 *
 * src/cpu/cpu.c
 */

#include "cpu.h"

gc_error_t
cpu_init(cpu_t *cpu, mem_t *mem) {
    ASSERT(cpu && mem);

    cpu->mem = mem;

    cpu->tlb.entries = malloc(sizeof(tlb_entry_t) * TLB_SIZE);


    return GC_NO_ERROR;
}

gc_error_t
cpu_terminate(cpu_t *cpu) {
    ASSERT(cpu);

    cpu->mem = NULL;

    free(cpu->tlb.entries);

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
        ubyte_t prefix = instr.addr[i];
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
