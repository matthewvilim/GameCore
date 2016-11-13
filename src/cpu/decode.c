#include "decode.h"

#include "instr.h"

enum operand_size _operand_size_table[] = {
    []                                                                                           = OPERAND_SIZE16,
    [SIZE_ATTRIBUTE_SEG_DEFAULT]                                                                 = OPERAND_SIZE32,
    [                             SIZE_ATTRIBUTE_OPERAND_PREFIX]                                 = OPERAND_SIZE32,
    [SIZE_ATTRIBUTE_SEG_DEFAULT | SIZE_ATTRIBUTE_OPERAND_PREFIX]                                 = OPERAND_SIZE16,
    [                                                             SIZE_ATTRIBUTE_ADDRESS_PREFIX] = OPERAND_SIZE16,
    [SIZE_ATTRIBUTE_SEG_DEFAULT |                                 SIZE_ATTRIBUTE_ADDRESS_PREFIX] = OPERAND_SIZE32,
    [                             SIZE_ATTRIBUTE_OPERAND_PREFIX | SIZE_ATTRIBUTE_ADDRESS_PREFIX] = OPERAND_SIZE32,
    [SIZE_ATTRIBUTE_SEG_DEFAULT | SIZE_ATTRIBUTE_OPERAND_PREFIX | SIZE_ATTRIBUTE_ADDRESS_PREFIX] = OPERAND_SIZE16
}

enum address_size _operand_size_table[] = {
    []                                                                                           = ADDRESS_SIZE16,
    [SIZE_ATTRIBUTE_SEG_DEFAULT]                                                                 = ADDRESS_SIZE32,
    [                             SIZE_ATTRIBUTE_OPERAND_PREFIX]                                 = ADDRESS_SIZE16,
    [SIZE_ATTRIBUTE_SEG_DEFAULT | SIZE_ATTRIBUTE_OPERAND_PREFIX]                                 = ADDRESS_SIZE32,
    [                                                             SIZE_ATTRIBUTE_ADDRESS_PREFIX] = ADDRESS_SIZE32,
    [SIZE_ATTRIBUTE_SEG_DEFAULT |                                 SIZE_ATTRIBUTE_ADDRESS_PREFIX] = ADDRESS_SIZE16,
    [                             SIZE_ATTRIBUTE_OPERAND_PREFIX | SIZE_ATTRIBUTE_ADDRESS_PREFIX] = ADDRESS_SIZE32,
    [SIZE_ATTRIBUTE_SEG_DEFAULT | SIZE_ATTRIBUTE_OPERAND_PREFIX | SIZE_ATTRIBUTE_ADDRESS_PREFIX] = ADDRESS_SIZE16
}

struct _opcode {
    enum instr b, w, dw;
    reg_file_seg op1, op2;
};

enum _group {
    GROUP1,
    GROUP2,
    GROUP3,
    GROUP4,
    GROUP5,
    GROUP6,
    GROUP7,
    GROUP8
};

enum _disp {
    DISP_NONE,
    DISP_BYTE,
    DISP_WORD,
    DISP_DWORD
};

enum _sib_mode {
    SIB_MODE0,
    SIB_MODE1,
    SIB_MODE2,
    SIB_MODE3
};

struct _modrm_info {
    bool sib;
    union {
        enum _sib_mode sib_mode;
        struct {
            enum _addr_mode addr_mode;
            enum rm {
                RM_REG,
                RM_MEM
            };
            union {
                reg_file_gen r;
                struct m {
                    reg_file_gen base, index;
                    _disp disp;
                };
            };
            _group group;
            reg_file_gen reg;
        };
    };
};

typedef struct _sib_info {
    enum _addr_mode mode;
    reg_file_gen base, index;
    uint8_t scale : 2;
    _disp disp;
} _sib_info;
