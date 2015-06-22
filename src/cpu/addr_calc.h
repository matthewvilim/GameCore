/*
 * Game Core Copyright (C) 2014 Matthew Vilim
 *
 * src/cpu/cpu.c
 */

typedef void (*calc_addr_t)(const cpu_t *cpu, instr_t *instr, operand_t *operand);

void
calc_addr16(const cpu_t *cpu, instr_t *instr, operand_t *operand) {
    operand->w = *cpu_gen_w_host(cpu, instr->modrm.reg1) +
                 *cpu_gen_w_host(cpu, instr->modrm.reg1) +
                 instr->modrm.disp16;
}

void
calc_addr32() {
    operand->dw = *cpu_gen_dw_host(cpu, instr->modrm.base) +
                  instr->modrm.disp32;
}

void
calc_addr32_scale_index_base() {
    operand->dw = *cpu_gen_dw_host(cpu, instr->modrm.base) +
                 (*cpu_gen_dw_host(cpu, instr-modrm.index) << instr->modrm.scale) +
                 instr->modrm.disp32;
}

void
_modrm_E(const cpu_t *cpu, instr_t *instr, operand_t *operand) {
    instr->modrm_len = 1;

    uint8_t mod = BIT_FIELD_READ(instr->addr[1], X86_MODRM_MOD_MASK);
    uint8_t rm = BIT_FIELD_READ(instr->addr[1], X86_MODRM_RM_MASK);

    switch (mod) {
        case X86_MOD_NO_DISP:
        case X86_MOD_B_DISP:
        case X86_MOD_W_DISP:
            if (instr->size == AddrSizeW) {
                _modrm_E_real(cpu, instr, operand, mod, rm)
            } else {
                _modrm_E_protected(cpu, instr, operand, mod, rm);
            }
            break;
        case X86_MOD_REG:
            switch (instr->op_size) {
                case OperandSizeB:
                    operand->b = cpu_gen_b_host(cpu, rm);
                    break;
                case OperandSizeW:
                    operand->w = cpu_gen_w_host(cpu, rm);
                    break;
                case OperandSizeDW:
                    operand->dw = cpu_gen_dw_host(cpu, rm);
                    break;
                default: break;
            }
            break;
        default: break;
    }

    instr->len += instr->modrm_len;
}

GC_INLINE void
_modrm_E_addrw(const cpu_t *cpu, instr_t instr, operand_t *operand,
               uint8_t mod, uint8_t rm) {
    addr16_t addr;
    addr.base = operand->seg;

    switch (rm) {
        case X86_RM_BX_PLUS_SI:
            instr->modrm.reg1 = X86_REG_BX;
            instr->modrm.reg2
            break;
        case X86_RM_BX_PLUS_DI:
            addr.offset = *cpu_gen_w_host(cpu, X86_REG_BX) +
                          *cpu_gen_w_host(cpu, X86_REG_DI);
            break;
        case X86_RM_BP_PLUS_SI:
            addr.offset = *cpu_gen_w_host(cpu, X86_REG_BP) +
                          *cpu_gen_w_host(cpu, X86_REG_SI);
            break;
        case X86_RM_BP_PLUS_DI:
            addr.offset = *cpu_gen_w_host(cpu, X86_REG_BP) +
                          *cpu_gen_w_host(cpu, X86_REG_DI);
            break;
        case X86_RM_SI:
            addr.offset = *cpu_gen_w_host(cpu, X86_REG_SI);
            break;
        case X86_RM_DI:
            addr.offset = *cpu_gen_w_host(cpu, X86_REG_DI);
            break;
        case X86_RM_BP_OR_DIR_ADDR:
            if (mod == X86_MOD_NO_DISP) {
                addr.offset = *(word_t *)(instr->addr + 2);
            } else {
                addr.offset = *cpu_gen_w_host(cpu, X86_REG_BP);
            }
            break;
        case X86_RM_BX:
            addr.offset = *cpu_gen_w_host(cpu, X86_REG_BX);
            break;
        default: break;
    }

    switch (mod) {
        case X86_MOD_B_DISP:
            instr->modrm_len++;
            addr->offset += instr->addr[2];
        case X86_MOD_W_DISP:
            instr->modrm_len += 2;
            addr->offset += *(word_t *)(instr->addr + 2);
        default: break;
    }

    operand->w = mem_addr16_host(cpu->mem, addr);
}

GC_INLINE void
_modrm_E_protected(const cpu_t *cpu,instr_t instr, operand_t *operand,
            uint8_t mod, uint8_t rm) {

}
