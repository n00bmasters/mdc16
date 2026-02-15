enum alu3_ind_op_type{
    BIT,
    CMP = 6
};

enum alu3_op_type{
    AND, OR, XOR, BIC, ADD, ADDC,  SUB, SUBC
};

enum alu2_op_type{
    NEG, NOT, SXT, SCL
};

enum shifts_op_type{
    SHL, SHR, SHRA, ROL, ROR, RCL, RCR
};

enum mem3_opt_type{
    LDW, LDB, LDSB, LCW, LCB, LCSB, STW, STB
};

enum imm9_op_type{
    INT = 0, RESET = 1, PUSH = 2, ADDSP = 6, JSR = 8 
};