#ifndef INSTR_H
#define INSTR_H

enum instr {
    INSTR_ADD_B,
    INSTR_ADD_W,
    INSTR_XOR
};

enum addr_mode {
    ADDR_MODE_BASE,
    ADDR_MODE_DISP,
    ADDR_MODE_BASE_SCALE,
    ADDR_MODE_BASE_INDEX,
    ADDR_MODE_BASE_DISP,
    ADDR_MODE_BASE_SCALE_INDEX,
    ADDR_MODE_BASE_SCALE_INDEX_DISP
};

enum operand {
    OPERAND_REG_GEN,
    OPERAND_REG_SEG,
    OPERAND_REG_CONTROL,
    OPERAND_REG_DEBUG,
    OPERAND_REG_TEST,
    OPERAND_MEM,
    OPERAND_FLAGS,
    OPERAND_IMMEDIATE
};

struct addr {
    enum addr_mode mode;
    reg_file_seg seg : 3;
    union base, index {
        enum reg_file_gen_dw dw;
        enum reg_file_gen_w w;
    } : 3;
    uint8_t scale : 2;
    union disp {
        byte b;
        word w;
        dword dw;
    };
};

struct instr {
    enum instr;
    struct op1, op2 {
        enum operand operand;
        union {
            struct _addr addr;
            enum reg_file_gen reg;
        };
    };
};

#endif
