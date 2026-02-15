#pragma once
#include "enums.h"
#include "instruction.h"
#include <cstdint>


//
// ================= ZERO_OP =================
//

class InstructionZeroOp : public Instruction16
{
public:

    InstructionZeroOp(uint16_t raw_, zero_op op_type_)
        : Instruction16(raw_), op_type(op_type_)
    {}

    uint8_t getRawOpType() const
    {
        return _raw & 0xF;
    }

    zero_op opType() const
    {
        return op_type;
    }

private:

    zero_op op_type;
};


//
// ================= ONE_OP =================
//

class InstructionOneOp : public Instruction16
{
public:

    InstructionOneOp(uint16_t raw_, one_op op_type_)
        : Instruction16(raw_), op_type(op_type_)
    {}

    uint8_t getRawOpType() const
    {
        return (_raw >> 9) & 0x7;
    }

    uint8_t reg() const
    {
        return (_raw >> 6) & 0x7;
    }

    one_op opType() const
    {
        return op_type;
    }

private:

    one_op op_type;
};


//
// ================= TWO_OP =================
//

class InstructionTwoOp : public Instruction16
{
public:

    InstructionTwoOp(uint16_t raw_, two_op op_type_)
        : Instruction16(raw_), op_type(op_type_)
    {}

    uint8_t srcReg() const
    {
        return (_raw >> 6) & 0x7;
    }

    uint8_t dstReg() const
    {
        return (_raw >> 3) & 0x7;
    }

    two_op opType() const
    {
        return op_type;
    }

private:

    two_op op_type;
};


//
// ================= MEM2 =================
//

class InstructionMem2 : public Instruction16
{
public:

    InstructionMem2(uint16_t raw_, mem2_op op_type_)
        : Instruction16(raw_), op_type(op_type_)
    {}

    uint8_t reg() const
    {
        return (_raw >> 6) & 0x7;
    }

    uint8_t addrReg() const
    {
        return (_raw >> 3) & 0x7;
    }

    mem2_op opType() const
    {
        return op_type;
    }

private:

    mem2_op op_type;
};


//
// ================= IMM6 =================
//

class InstructionImm6 : public Instruction16
{
public:

    InstructionImm6(uint16_t raw_, imm_6_op op_type_)
        : Instruction16(raw_), op_type(op_type_)
    {}

    int16_t immediate() const
    {
        int16_t val = _raw & 0x3F;

        if (val & 0x20)
            val |= 0xFFC0;

        return val;
    }

    imm_6_op opType() const
    {
        return op_type;
    }

private:

    imm_6_op op_type;
};


//
// ================= IMM9 =================
//

class InstructionImm9 : public Instruction16
{
public:

    InstructionImm9(uint16_t raw_, imm9_op_type op_type_)
        : Instruction16(raw_), op_type(op_type_)
    {}

    int16_t immediate() const
    {
        int16_t val = _raw & 0x1FF;

        if (val & 0x100)
            val |= 0xFE00;

        return val;
    }

    imm9_op_type opType() const
    {
        return op_type;
    }

private:

    imm9_op_type op_type;
};


//
// ================= MEM3 =================
//

class InstructionMem3 : public Instruction16
{
public:

    InstructionMem3(uint16_t raw_, mem3_opt_type op_type_)
        : Instruction16(raw_), op_type(op_type_)
    {}

    uint8_t reg() const
    {
        return (_raw >> 6) & 0x7;
    }

    uint8_t baseReg() const
    {
        return (_raw >> 3) & 0x7;
    }

    mem3_opt_type opType() const
    {
        return op_type;
    }

private:

    mem3_opt_type op_type;
};


//
// ================= SHIFTS =================
//

class InstructionShift : public Instruction16
{
public:

    InstructionShift(uint16_t raw_, shifts_op_type op_type_)
        : Instruction16(raw_), op_type(op_type_)
    {}

    uint8_t reg() const
    {
        return (_raw >> 3) & 0x7;
    }

    uint8_t amount() const
    {
        return _raw & 0x7;
    }

    shifts_op_type opType() const
    {
        return op_type;
    }

private:

    shifts_op_type op_type;
};


//
// ================= ALU2 =================
//

class InstructionALU2 : public Instruction16
{
public:

    InstructionALU2(uint16_t raw_, alu2_op_type op_type_)
        : Instruction16(raw_), op_type(op_type_)
    {}

    uint8_t reg() const
    {
        return (_raw >> 3) & 0x7;
    }

    alu2_op_type opType() const
    {
        return op_type;
    }

private:

    alu2_op_type op_type;
};


//
// ================= ALU3 =================
//

class InstructionALU3 : public Instruction16
{
public:

    InstructionALU3(uint16_t raw_, alu3_op_type op_type_)
        : Instruction16(raw_), op_type(op_type_)
    {}

    uint8_t src1() const
    {
        return (_raw >> 6) & 0x7;
    }

    uint8_t src2() const
    {
        return (_raw >> 3) & 0x7;
    }

    uint8_t dst() const
    {
        return _raw & 0x7;
    }

    alu3_op_type opType() const
    {
        return op_type;
    }

private:

    alu3_op_type op_type;
};


//
// ================= ALU3_IND =================
//

class InstructionALU3Ind : public Instruction16
{
public:

    InstructionALU3Ind(uint16_t raw_, alu3_ind_op_type op_type_)
        : Instruction16(raw_), op_type(op_type_)
    {}

    uint8_t reg() const
    {
        return (_raw >> 3) & 0x7;
    }

    alu3_ind_op_type opType() const
    {
        return op_type;
    }

private:

    alu3_ind_op_type op_type;
};


//
// ================= BRANCH ABS =================
//

class InstructionBranchAbs : public Instruction16
{
public:

    explicit InstructionBranchAbs(uint16_t raw_)
        : Instruction16(raw_)
    {}

    uint16_t address() const
    {
        return _raw & 0x7FF;
    }
};


//
// ================= BRANCH REL =================
//

class InstructionBranchRel : public Instruction16
{
public:

    explicit InstructionBranchRel(uint16_t raw_)
        : Instruction16(raw_)
    {}

    int16_t offset() const
    {
        int16_t val = _raw & 0x1FF;

        if (val & 0x100)
            val |= 0xFE00;

        return val;
    }
};
