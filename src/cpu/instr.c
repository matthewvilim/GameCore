/*
 * Game Core Copyright (C) 2014 Matthew Vilim
 *
 * src/cpu/instruction.c
 */

const op_group_t mov = {
    .name = "mov"
};

const op_info_t mov_al_ob = {
    .read = _read_al_ob;
    .exe = _exe_dummy;
    .write =
};

const op_info_t op_table[] = {
    , // 0x00

}

GC_INLINE void *
_modrm_E(const cpu_t *cpu, instr_t *instr, bool byte) {
    instr->modrm_len = 1;

    uint8_t mod = BIT_FIELD_READ(instr->addr[1], X86_MODRM_MOD_MASK);
    uint8_t rm = BIT_FIELD_READ(instr->addr[1], X86_MODRM_RM_MASK);

    lin_addr_t addr;
    addr.base = instr->seg;

    switch (mod) {
        case X86_MOD_NO_DISP:
        case X86_MOD_B_DISP:
        case X86_MOD_W_DISP:
            switch (rm) {
                case X86_RM_BX_PLUS_SI:
                    addr.offset = *cpu_gen_w_host(cpu, X86_REG_BX) +
                                  *cpu_gen_w_host(cpu, X86_REG_SI);
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
                        addr.offset = mod == X86_MOD_NO_DISP ?
                                      *(word_t *)(instr->addr + 2) :
                                      cpu_gen_w_host(cpu, X86_REG_BP);
                    break;
                case X86_RM_BX:
                    addr.offset = cpu_gen_w_host(cpu, X86_REG_BX);
                    break;
                default: break;
            }
            break;
            case X86_MOD_REG:
                return byte ? cpu_gen_b_host(cpu, rm) : cpu_gen_w_host(cpu, rm);
                break;
        default: break;
    }

    switch (mod) {
        case X86_MOD_B_DISP:
            instr->modrm_len++;
            addr->offset += instr_host[2];
        case X86_MOD_W_DISP:
            instr->modrm_len += 2;
            addr->offset += *(word_t *)(instr_host + 2);
        default: break;
    }

    instr->len += instr->modrm_len;

    return mem_addr_host(cpu->mem, addr);
}

GC_INLINE void *
_modrm_G(const cpu_t *cpu, instr_t *instr, bool byte) {
    uint8_t gen = BIT_FIELD_READ(instr->addr[1], X86_MODRM_REG_MASK);
    return byte ? cpu_gen_b_host(cpu, gen) : cpu_gen_w_host(cpu, gen);
}

GC_INLINE void *
_modrm_S(const cpu_t *cpu, instr_t *instr) {
    uint8_t seg = BIT_FIELD_READ(instr->addr[1], X86_MODRM_REG_MASK);
    return cpu_seg_host(cpu, seg);
}

void
_ops_Ew_Sw(const cpu_t *cpu, instr_t *instr) {
    instr->op1.b = _modrm_E(cpu, instr, false);
    instr->op2.b = _modrm_S(cpu, instr);
}

void
_ops_Sw_Ew(const cpu_t *cpu, instr_t *instr) {
    instr->op1.b = _modrm_S(cpu, instr);
    instr->op2.b = _modrm_E(cpu, instr, false);
}

void
_ops_Eb_Gb(const cpu_t *cpu, instr_t *instr) {
    instr->op1.b = _modrm_E(cpu, instr, true);
    instr->op2.b = _modrm_G(cpu, instr, true);
}

void
_ops_Gb_Eb(const cpu_t *cpu, instr_t *instr) {
    instr->op1.b = _modrm_G(cpu, instr, true);
    instr->op2.b = _modrm_E(cpu, instr, true);
}

void
_ops_Ew_Gw(const cpu_t *cpu, instr_t *instr) {
    instr->op1.w = _modrm_E(cpu, instr, false);
    instr->op2.w = _modrm_G(cpu, instr, false);
}

void
_ops_Gw_Ew(const cpu_t *cpu, instr_t *instr) {
    instr->op1.w = _modrm_G(cpu, instr, false);
    instr->op2.w = _modrm_E(cpu, instr, false);
}

void
_ops_AL_Ob(const cpu_t *cpu, instr_t *instr) {
    instr->op1.b = cpu_gen_b_host(cpu, X86_REG_AL);
    instr->op2.b = instr.addr + 1
}

void
_ops_Ob_AL(const cpu_t *cpu, instr_t *instr) {
    instr->op1.b = instr.addr + 1;
    instr->op2.b = cpu_gen_b_host(cpu, X86_REG_AL);
}

void
_ops_AX_Ow(const cpu_t *cpu, instr_t *instr) {
    instr->op1.w = cpu_gen_w_host(cpu, X86_REG_AX);
    instr->op2.w = instr.addr + 1
}

void
_ops_Ow_AX(const cpu_t *cpu, instr_t *instr) {
    instr->op1.w = instr.addr + 1
    instr->op2.w = cpu_gen_w_host(cpu, X86_REG_AX);
}

void
_ops_AL_Ib(const cpu_t *cpu, instr_t *instr) {
    instr->op1.b = cpu_gen_b_host(cpu, X86_REG_AL);
    instr->op2.b = instr->addr[1];
}

void
_ops_CL_Ib(const cpu_t *cpu, instr_t *instr) {
    instr->op1.b = cpu_gen_b_host(cpu, X86_REG_CL);
    instr->op2.b = instr->addr[1];
}

void
_ops_DL_Ib(const cpu_t *cpu, instr_t *instr) {
    instr->op1.b = cpu_gen_b_host(cpu, X86_REG_DL);
    instr->op2.b = instr->addr[1];
}

void
_ops_BL_Ib(const cpu_t *cpu, instr_t *instr) {
    instr->op1.b = cpu_gen_b_host(cpu, X86_REG_BH);
    instr->op2.b = instr->addr[1];
}

void
_ops_AH_Ib(const cpu_t *cpu, instr_t *instr) {
    instr->op1.b = cpu_gen_b_host(cpu, X86_REG_AH);
    instr->op2.b = instr->addr[1];
}

void
_ops_CH_Ib(const cpu_t *cpu, instr_t *instr) {
    instr->op1.b = cpu_gen_b_host(cpu, X86_REG_CH);
    instr->op2.b = instr->addr[1];
}

void
_ops_DH_Ib(const cpu_t *cpu, instr_t *instr) {
    instr->op1.b = cpu_gen_b_host(cpu, X86_REG_DH);
    instr->op2.b = instr->addr[1];
}

void
_ops_BH_Ib(const cpu_t *cpu, instr_t *instr) {
    instr->op1.b = cpu_gen_b_host(cpu, X86_REG_BH);
    instr->op2.b = instr->addr[1];
}

void
_exe_movb(const cpu_t *cpu, const instr_t *instr) {
    *op1.b = *op2.b;
}

void
_exe_movw(const cpu_t *cpu, const instr_t *instr) {
    *op1.w = *op2.w;
}
