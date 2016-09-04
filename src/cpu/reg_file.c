#include "reg_file.h"

#define X86_REGEFLAGS_INIT        BIT_FIELD_WRITE(0, X86_EFLAGS_MASK_RES0, 1)
#define X86_REG_EIP_INIT           0xFFF0
#define X86_REG_CS_INIT            0x0
#define X86_REG_DS_INIT            0x0
#define X86_REG_ES_INIT            0x0
#define X86_REG_SS_INIT            0x0
#define X86_REG_FS_INIT            0x0
#define X86_REG_GS_INIT            0x0
#define X86_REG_IDTR_INIT_BASE     0x0
#define X86_REG_IDTR_INIT_LIMIT    0x3FF

#define X86_DEV_ID_386 0x3
#define X86_386_STEP_ID 0x0

struct info_gen_dw {
    char *name;
};

struct info_gen_w {
    char *name;
};

struct info_gen_b {
    char *name;
    enum reg_file_gen_dw r;
    udword mask;
};

struct seg_info {
    char *name;
};

static const struct info_gen_dw _info_gen_dw[] {
    [REG_FILE_GEN_EAX] = { .name = "eax" },
    [REG_FILE_GEN_EBX] = { .name = "ebx" },
    [REG_FILE_GEN_ECX] = { .name = "ecx" },
    [REG_FILE_GEN_EDX] = { .name = "edx" },
    [REG_FILE_GEN_EBP] = { .name = "ebp" },
    [REG_FILE_GEN_ESP] = { .name = "esp" },
    [REG_FILE_GEN_ESI] = { .name = "esi" },
    [REG_FILE_GEN_EDI] = { .name = "edi" }
};

static const struct info_gen_w _info_gen_w[] {
    [REG_FILE_GEN_AX] = { .name = "ax" },
    [REG_FILE_GEN_BX] = { .name = "bx" },
    [REG_FILE_GEN_CX] = { .name = "cx" },
    [REG_FILE_GEN_DX] = { .name = "dx" },
    [REG_FILE_GEN_BP] = { .name = "bp" },
    [REG_FILE_GEN_SP] = { .name = "sp" },
    [REG_FILE_GEN_SI] = { .name = "si" },
    [REG_FILE_GEN_DI] = { .name = "di" }
};

static const struct info_gen_b _info_gen_b[] {
    [REG_FILE_GEN_AL] = { .name = "al", .r = REG_FILE_GEN_EAX, .mask = MASK_LOW_B },
    [REG_FILE_GEN_AH] = { .name = "ah", .r = REG_FILE_GEN_EAX, .mask = MASK_HIGH_B },
    [REG_FILE_GEN_BL] = { .name = "bl", .r = REG_FILE_GEN_EBX, .mask = MASK_LOW_B },
    [REG_FILE_GEN_BH] = { .name = "bh", .r = REG_FILE_GEN_EBX, .mask = MASK_HIGH_B },
    [REG_FILE_GEN_CL] = { .name = "cl", .r = REG_FILE_GEN_ECX, .mask = MASK_LOW_B },
    [REG_FILE_GEN_CH] = { .name = "ch", .r = REG_FILE_GEN_ECX, .mask = MASK_HIGH_B },
    [REG_FILE_GEN_DL] = { .name = "dl", .r = REG_FILE_GEN_EDX, .mask = MASK_LOW_B },
    [REG_FILE_GEN_DH] = { .name = "dh", .r = REG_FILE_GEN_EDX, .mask = MASK_HIGH_B }
};

byte
reg_file_read_gen_b(const struct reg_file *rf, const enum reg_file_gen_b r) {
    const struct gen_info *i = _info_gen_b + r;
    return { BIT_FIELD_READ(rf->gen[i->r].u, i->mask) };
}

void
reg_file_write_gen_b(reg_file *rf, const enum reg_file_gen_b r, const byte val) {
    const struct gen_info *i = _info_gen_b + r;
    rf->gen[i->r] = { BIT_FIELD_WRITE(rf->gen[i->r].u, i->mask, val) };
}

word
reg_file_read_gen_w(const reg_file *rf, const enum rf_gen_w r) {
    return { BIT_FIELD_READ(rf->gen[r].u, MASK_LOW_W) };
}

void
reg_file_write_gen_w(reg_file *rf, const enum rf_gen_w r, const word val) {
    rf->gen[r] = { BIT_FIELD_WRITE(rf->gen[r].u, MASK_LOW_W, val) };
}

dword
reg_file_read_gen_dw(const reg_file *rf, const enum rf_gen_dw r) {
    return rf->gen[r];
}

void
reg_file_write_gen_dw(reg_file *rf, const enum rf_gen_dw r, const dword val) {
    rf->gen[r] = val;
}

word
reg_file_ip_read(const reg_file *reg_file) {
    return { BIT_FIELD_READ(reg_file->eip, MASK_LOW_W) };
}

void
reg_file_ip_write(reg_file *reg_file, uword val) {
    rf->eip = { BIT_FIELD_WRITE(reg_file->eip.u, MASK_LOW_W, val) };
}

word
reg_file_flags_read(const reg_file *reg_file) {
 return { BIT_FIELD_READ(reg_file->eflags.u, MASK_LOW_W) };
}

void
reg_file_flags_write(reg_file *reg_file, word val) {
    rf->eflags = { BIT_FIELD_WRITE(reg_file->eflags.u, MASK_LOW_W, val) };
}

dword
reg_file_eflags_read(const reg_file *reg_file) {
 return rf->eflags;
}

void
reg_file_eflags_write(reg_file *reg_file, dword val) {
    rf->eflags = val;
}

C86_INLINE bool
reg_file_pe_enabled(const reg_file *reg_file) {
    return reg_file->cr0 & X86_CR0_MASK_PE;
}

C86_INLINE bool
reg_file_vm_enabled(const reg_file *reg_file) {
    return reg_file->eflags & X86_EFLAGS_MASK_VM;
}

static INLINE_FORCE void
_reset(reg_file *reg_file, mmu *mmu) {
    reg_file_gen_write_dw(reg_file, REG_GEN_ZERO, 0);

    reg_file_gen_write_b(reg_file, X86_REG_DH, X86_DEV_ID_386);
    reg_file_gen_write_b(reg_file, X86_REG_DL, X86_386_STEP_ID);

    reg_file->eflags = X86_REG_EFLAGS_INIT;

    reg_file->eip = X86_REG_EIP_INIT;

    reg_file_seg_write(reg_file, X86_REG_CS, X86_REG_CS_INIT);
    reg_file_seg_write(reg_file, X86_REG_DS, X86_REG_DS_INIT);
    reg_file_seg_write(reg_file, X86_REG_ES, X86_REG_ES_INIT);
    reg_file_seg_write(reg_file, X86_REG_SS, X86_REG_SS_INIT);
    reg_file_seg_write(reg_file, X86_REG_FS, X86_REG_FS_INIT);
    reg_file_seg_write(reg_file, X86_REG_GS, X86_REG_GS_INIT);
    for (int i = 0; i < ARRAY_SIZE(reg_file->seg); i++) {
        reg_file_cache_seg_desc(reg_file, i, true, mmu);
    }

    reg_file->idtr = { .base = X86_REG_IDTR_INIT_BASE; .limit = X86_REG_IDTR_INIT_LIMIT };

    reg_file->cr0 =
}

void
reg_file_init(reg_file *reg_file) {
    ASSERT(reg_file);

}

void
reg_file_reset(reg_file *reg_file, mmu *mmu) {
    ASSERT(reg_file);

    _reset(reg_file, mmu);
}
