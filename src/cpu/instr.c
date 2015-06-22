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
_modrm_G_S(const cpu_t *cpu, instr_t *instr, bool gen) {
    uint8_t reg = BIT_FIELD_READ(instr->addr[1], X86_MODRM_REG_MASK);
    if (gen) {
        switch (instr->op_size) {
            case OperandSizeB:
                return cpu_gen_b_host(cpu, gen);
            case OperandSizeW:
                return cpu_gen_w_host(cpu, gen);
            case OperandSizeDW:
                return cpu_gen_dw_host(cpu, gen);
            default:
        }
    } else {
        return cpu_seg_host(cpu, seg);
    }
}

void
_ops_Ew_Sw(const cpu_t *cpu, instr_t *instr) {
    instr->op1.b = _modrm_E(cpu, instr, instr->op1.seg, false);
    instr->op2.b = _modrm_S(cpu, instr);
}

void
_ops_Sw_Ew(const cpu_t *cpu, instr_t *instr) {
    instr->op1.b = _modrm_S(cpu, instr);
    instr->op2.b = _modrm_E(cpu, instr, instr->op2.seg, false);
}

void
_ops_Eb_Gb(const cpu_t *cpu, instr_t *instr) {
    instr->op1.b = _modrm_E(cpu, instr, instr->op1.seg, true);
    instr->op2.b = _modrm_G(cpu, instr, true);
}

void
_ops_Gb_Eb(const cpu_t *cpu, instr_t *instr) {
    instr->op1.b = _modrm_G(cpu, instr, true);
    instr->op2.b = _modrm_E(cpu, instr, instr->op2.seg, true);
}

void
_ops_Ew_Gw(const cpu_t *cpu, instr_t *instr) {
    instr->op1.w = _modrm_E(cpu, instr, instr->op1.seg, false);
    instr->op2.w = _modrm_G(cpu, instr, false);
}

void
_ops_Gw_Ew(const cpu_t *cpu, instr_t *instr) {
    instr->op1.w = _modrm_G(cpu, instr, false);
    instr->op2.w = _modrm_E(cpu, instr, instr->op2.seg, false);
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
