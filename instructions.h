#pragma once
#include "enums.h"
#include "instruction.h"
#include "register.h"
#include <cassert>
#include <cstdint>

static Register getRegister(uint16_t raw, int pos) {
  assert((raw >> pos) & 0b111 < 8);
  return static_cast<Register>((raw >> pos) & 0b111);
}

template <class T, int size> static T getOp(uint16_t raw, int pos) {
  return static_cast<T>((raw >> pos) & ((1 << size) - 1));
}

template <int size> static uint16_t getImmediate(uint16_t raw, int pos) {
  return (raw >> pos) & ((1 << size) - 1);
}

//
// ================= ZERO_OP =================
//

struct InstructionZeroOp : public Instruction16 {

  InstructionZeroOp(uint16_t raw_, zero_op op_type_)
      : Instruction16(raw_), op_type(op_type_) {}

  const zero_op op_type;
};

//
// ================= ONE_OP =================
//

struct InstructionOneOp : public Instruction16 {

  InstructionOneOp(uint16_t raw_)
      : Instruction16(raw_), _op_type(getOp<one_op, 4>(raw_, 3)),
        _register(getRegister(raw_, 0)) {
    assert(((raw_ >> 13) & 0b111) == 0b001);
    assert(((raw_ >> 3) & 0b1111) == static_cast<uint16_t>(_op_type));
    assert((raw_ & 0b111) == static_cast<uint16_t>(_register));
  }

  const one_op _op_type;
  const Register _register;
};

//
// ================= TWO_OP =================
//

struct InstructionTwoOp : public Instruction16 {
  InstructionTwoOp(uint16_t raw_, two_op op_type_, Register reg1, Register reg2)
      : Instruction16(raw_), op_type(getOp<two_op, 5>(raw_, 6)),
        _reg1(getRegister(raw_, 0)), _reg2(getRegister(raw_, 3)) {
    assert(((raw_ >> 11) & 0b11111) == 0b01000);
    assert(((raw_ >> 6) & 0b1111) == static_cast<uint16_t>(op_type));
    assert(((raw_ >> 3) & 0b111) == static_cast<uint16_t>(reg1));
    assert((raw_ & 0b111) == static_cast<uint16_t>(reg2));
  }

  const two_op op_type;
  const Register _reg1, _reg2;
};

//
// ================= MEM2 =================
//

struct InstructionMem2 : public Instruction16 {

  InstructionMem2(uint16_t raw_, mem2_op op_type_, Register rs, Register rd)
      : Instruction16(raw_), op_type(getOp<mem2_op, 5>(raw_, 6)),
        _rs(getRegister(raw_, 3)), _rd(getRegister(raw_, 0)) {
    assert(((raw_ >> 13) & 0b111) == 0b011);
    assert(((raw_ >> 9) & 0b1111) == static_cast<uint16_t>(op_type));
    assert(((raw_ >> 3) & 0b111111) == static_cast<uint16_t>(rs));
    assert((raw_ & 0b111) == static_cast<uint16_t>(rd));
  }

  const mem2_op op_type;
  const Register _rs, _rd;
};

// q
//  ================= IMM6 =================
//

struct InstructionImm6 : public Instruction16 {

  InstructionImm6(uint16_t raw_, imm_6_op op_type_, uint16_t imm6, Register rd)
      : Instruction16(raw_), op_type(getOp<imm_6_op, 4>(raw_, 9)),
        _imm6(getImmediate<6>(raw_, 3)), _rd(getRegister(raw_, 0)) {
    assert(((raw_ >> 13) & 0b111) == 0b011); // group coding
    assert(((raw_ >> 9) & 0b1111) == static_cast<uint16_t>(op_type)); // op type
    assert(((raw_ >> 3) & 0b111111) == static_cast<uint16_t>(op_type_));
    assert((raw_ & 0b111) == static_cast<uint16_t>(rd));
  }

  const imm_6_op op_type;
  const uint16_t _imm6;
  const Register _rd;
};

//
// ================= IMM9 =================
//

struct InstructionImm9 : public Instruction16 {
  InstructionImm9(uint16_t raw_, imm9_op_type op_type_, uint16_t immediate)
      : Instruction16(raw_), op_type(getOp<imm9_op_type, 4>(raw_, 9)),
        _immediate(getOp<uint16_t, 9>(raw_, 0)) {
    assert(((raw_ >> 13) & 0b111) == 0b100); // group coding
    assert(((raw_ >> 9) & 0b1111) == static_cast<uint16_t>(op_type)); // op type
    assert((raw_ & 0b111111111) == immediate);
  }

  const imm9_op_type op_type;
  const uint16_t _immediate;
};

//
// ================= MEM3 =================
//

struct InstructionMem3 : public Instruction16 {
  InstructionMem3(uint16_t raw_, mem3_opt_type op_type_, Register rs0,
                  Register rs1, Register rd)
      : Instruction16(raw_), op_type(getOp<mem3_opt_type, 3>(raw_, 9)),
        _rs0(getRegister(raw_, 3)), _rs1(getRegister(raw_, 6)),
        _rd(getRegister(raw_, 0)) {
    assert(((raw_ >> 12) & 0b1111) == 0b1010); // group coding
    assert(((raw_ >> 9)) & 0b111 == static_cast<uint16_t>(op_type)); // op type
    assert((raw_ >> 6) & 0b111 == static_cast<uint16_t>(rs0));
    assert((raw_ >> 3) & 0b111 == static_cast<uint16_t>(rs1));
    assert((raw_ & 0b111) == static_cast<uint16_t>(rd));
  }

  const mem3_opt_type op_type;
  const Register _rs0, _rs1, _rd;
};

//
// ================= SHIFTS =================
//

struct InstructionShift : public Instruction16 {

  InstructionShift(uint16_t raw_, shifts_op_type op_type_, Register rs,
                   Register rd, uint8_t shift_val)
      : Instruction16(raw_), op_type(getOp<shifts_op_type, 3>(raw_, 9)),
        _rs(getRegister(raw_, 3)), _rd(getRegister(raw_, 0)),
        _shift_val(getOp<uint8_t, 3>(raw_, 6)) {
    assert(((raw_ >> 12) & 0b1111) == 0b0001); // group coding
    assert(((raw_ >> 9) & 0b111) == static_cast<uint16_t>(op_type)); // op type
    assert((raw_ >> 6) & 0b111 == static_cast<uint16_t>(shift_val));
    assert((raw_ >> 3) & 0b111 == static_cast<uint16_t>(rs));
    assert((raw_ & 0b111) == static_cast<uint16_t>(rd));
  }

  const shifts_op_type op_type;
  const Register _rs, _rd;
  const uint8_t _shift_val;
};

// ================= ALU2 =================
//

struct InstructionALU2 : public Instruction16 {

  InstructionALU2(uint16_t raw_, alu2_op_type op_type_, Register rs,
                  Register rd)
      : Instruction16(raw_), op_type(op_type_), _rs(rs), _rd(rd) {
    assert(((raw_ >> 11) & 0b11111) == 0b01011); // group coding
    assert(((raw_ >> 6) & 0b111) == static_cast<uint16_t>(op_type)); // op type
    assert((raw_ >> 3) & 0b111 == static_cast<uint16_t>(rs));
    assert((raw_ & 0b111) == static_cast<uint16_t>(rd));
  }

  const alu2_op_type op_type;
  const Register _rs, _rd;
};

//
// ================= ALU3 =================
//

struct InstructionALU3 : public Instruction16 {

  InstructionALU3(uint16_t raw_, alu3_op_type op_type_, Register rs0,
                  Register rs1, Register rd)
      : Instruction16(raw_), op_type(op_type_), _rs0(rs0), _rs1(rs1), _rd(rd) {
    assert(((raw_ >> 12) & 0b1111) == 0b1011); // group coding
    assert(((raw_ >> 9) & 0b111) == static_cast<uint16_t>(op_type)); // op type
    assert((raw_ >> 6) & 0b111 == static_cast<uint16_t>(rs0));
    assert((raw_ >> 3) & 0b111 == static_cast<uint16_t>(rs1));
    assert((raw_ & 0b111) == static_cast<uint16_t>(rd));
  }

  const alu3_op_type op_type;
  const Register _rs0, _rs1, _rd;
};

//
// ================= ALU3_IND =================
//

struct InstructionALU3Ind : public Instruction16 {
  explicit InstructionALU3Ind(uint16_t raw_, alu3_ind_op_type op_type_,
                              Register rs, Register rd)
      : Instruction16(raw_), op_type(op_type_), _rs(rs), _rd(rd) {
    assert(((raw_ >> 11) & 0b11111) == 0b01001); // group coding
    assert(((raw_ >> 6) & 0b111) == static_cast<uint16_t>(op_type)); // op type
    assert((raw_ >> 3) & 0b111 == static_cast<uint16_t>(rs));
    assert((raw_ & 0b111) == static_cast<uint16_t>(rd));
  }

  const alu3_ind_op_type op_type;
  const Register _rs, _rd;
};

//
// ================= BRANCH ABS =================
//

struct InstructionBranchAbs : public Instruction16 {
  explicit InstructionBranchAbs(uint16_t raw_, uint8_t condition)
      : Instruction16(raw_), _condition(condition) {
    assert(((raw_ >> 11) & 0b11111) == 0b00001); // group coding
    assert(raw_ & 0b1111 == condition & 0b1111);
  }

  const uint8_t _condition;
};

//
// ================= BRANCH REL =================
//

struct InstructionBranchRelN : public Instruction16 {
  explicit InstructionBranchRelN(uint16_t raw_, uint8_t condition,
                                 uint16_t immediate)
      : Instruction16(raw_), _condition(condition), _immediate(immediate) {
    assert(((raw_ >> 13) & 0b111) == 0b110);
    assert(((raw_ >> 9) & 0b1111) == condition & 0b1111);
    assert((raw_ & 0b111111111) == immediate & 0b111111111);
  }

  const uint8_t _condition;
  const uint16_t _immediate;
};

struct InstructionBranchRelP : public Instruction16 {
  explicit InstructionBranchRelP(uint16_t raw_, uint8_t condition,
                                 uint16_t immediate)
      : Instruction16(raw_), _condition(condition), _immediate(immediate) {
    assert(((raw_ >> 13) & 0b111) == 0b111);
    assert(((raw_ >> 9) & 0b1111) == condition & 0b1111);
    assert((raw_ & 0b111111111) == immediate & 0b111111111);
  }

  const uint16_t _immediate;
  const uint8_t _condition;
};
