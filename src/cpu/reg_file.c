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

struct gen_info {
    char *name;
    reg_file_gen index;
    udword mask;
};

struct seg_info {
    char *name;
};

static const gen_info _gen_info_table[] {
    [REG_FILE_GEN_EAX] = { .name = "eax" },
    [REG_FILE_GEN_EBX] = { .name = "ebx" },
    [REG_FILE_GEN_ECX] = { .name = "ecx" },
    [REG_FILE_GEN_EDX] = { .name = "edx" },
    [REG_FILE_GEN_ESP] = { .name = "esp" },
    [REG_FILE_GEN_EBP] = { .name = "ebp" },
    [REG_FILE_GEN_ESI] = { .name = "esi" },
    [REG_FILE_GEN_EDI] = { .name = "edi", .index = REG_FILE_GEN_EDI },

    [REG_FILE_GEN_AX] = { .name = "ax", .index = GEN_EAX},
    [REG_FILE_GEN_BX] = { .name = "bx", .index = GEN_EBX, .mask = MASK_LOW_W },
    [REG_FILE_GEN_CX] = { .name = "cx", .index = GEN_ECX, .mask = MASK_LOW_W },
    [REG_FILE_GEN_DX] = { .name = "dx", .index = GEN_EDX, .mask = MASK_LOW_W },
    [REG_FILE_GEN_BP] = { .name = "bp", .index = GEN_EBP, .mask = MASK_LOW_W },
    [REG_FILE_GEN_SP] = { .name = "sp", .index = GEN_ESP, .mask = MASK_LOW_W },
    [REG_FILE_GEN_SI] = { .name = "si", .index = GEN_ESI, .mask = MASK_LOW_W },
    [REG_FILE_GEN_DI] = { .name = "di", .index = GEN_EDI, .mask = MASK_LOW_W },

    [REG_FILE_GEN_AL] = { .name = "al", .index = GEN_EAX, .mask = MASK_LOW_B },
    [REG_FILE_GEN_AH] = { .name = "ah", .index = GEN_EAX, .mask = MASK_HIGH_B },
    [REG_FILE_GEN_BL] = { .name = "bl", .index = GEN_EBX, .mask = MASK_LOW_B },
    [REG_FILE_GEN_BH] = { .name = "bh", .index = GEN_EBX, .mask = MASK_HIGH_B },
    [REG_FILE_GEN_CL] = { .name = "cl", .index = GEN_ECX, .mask = MASK_LOW_B },
    [REG_FILE_GEN_CH] = { .name = "ch", .index = GEN_ECX, .mask = MASK_HIGH_B },
    [REG_FILE_GEN_DL] = { .name = "dl", .index = GEN_EDX, .mask = MASK_LOW_B },
    [REG_FILE_GEN_DH] = { .name = "dh", .index = GEN_EDX, .mask = MASK_HIGH_B }
};

struct reg_file {
    udword gen[GEN_COUNT], eip, eflags;

    uword seg[SEG_COUNT];

    udword eip;

    reg_desc_table gdtr, ldtr, idtr;

    reg_task tr;
    uword cr0, cr1, cr2, cr3;
};

ubyte
reg_file_read_gen_b(const reg_file *rf, const reg_file_gen r) {
    const struct gen_info *i = _gen_info_table + r;
    return BIT_FIELD_READ(rf->gen[i->index], i->mask);
}

void
reg_file_write_gen_b(reg_file *rf, const reg r, const ubyte val) {
    const struct gen_info *i = _gen_info_table + r;
    BIT_FIELD_WRITE(rf->gen[i->index], i->mask, val);
}

uword
reg_file_read_gen_w(const reg_file *rf, const reg r) {
    return BIT_FIELD_READ(rf->gen[r], MASK_LOW_W);
}

void
reg_file_write_gen_w(reg_file *rf, const reg r, const uword val) {
    BIT_FIELD_WRITE(rf->gen[r], MASK_LOW_W, val);
}

udword
reg_file_read_gen_dw(const reg_file *rf, const reg r) {
    return rf->gen[r];
}

void
reg_file_write_gen_dw(reg_file *rf, const reg r, const udword val) {
    rf->gen[r = val;
}

uword_t
reg_file_ip_read(const reg_file *reg_file) {
    return BIT_FIELD_READ(reg_file->eip, MASK_LOW_W);
}

void
reg_file_ip_write(reg_file *reg_file, uword val) {
    BIT_FIELD_WRITE(reg_file->eip, MASK_LOW_W, val);
}

uword_t
reg_file_flags_read(const reg_file *reg_file) {
 return BIT_FIELD_READ(reg_file->eflags, MASK_LOW_W);
}

void
reg_file_flags_write(reg_file *reg_file, uword val) {
    BIT_FIELD_WRITE(reg_file->eflags, MASK_LOW_W, val);
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
