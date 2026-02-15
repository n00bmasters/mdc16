#include "decoder.h"
#include "enums.h"
#include "instruction.h"
#include "instructions.h"

GROUP getGroup(int number, int n) {
  return static_cast<GROUP>(number & ((1 << n) - 1));
}

Instruction16 Decoder::decodeInstruction(uint16_t raw_bytes) {
  GROUP last;

  for (int i = 3; i < 6; i++) {
    last = getGroup(raw_bytes, i);

    switch (i) {
    case 3:
      switch (last) {
      case GROUP::ZERO_OP:
        return InstructionOneOp(raw_bytes);
      case GROUP::IMM_6:
        return InstructionImm6(raw_bytes);
      case GROUP::IMM_9:
        return InstructionImm9(raw_bytes);
      case GROUP::BR_REL_N:
        return InstructionBranchRelN(raw_bytes);
      case GROUP::BR_REL_P:
        return InstructionBranchRelP(raw_bytes);
      default:
        break;
      }
      break;

    case 4:
      switch (last) {
      case GROUP::MEM_3:
        return InstructionMem3(raw_bytes);
      case GROUP::SHIFTS:
        return InstructionShift(raw_bytes);
      case GROUP::ALU3:
        return InstructionALU3(raw_bytes);
      default:
        break;
      }
      break;

    case 5:
      switch (last) {
      case GROUP::TWO_OP:
        return InstructionTwoOp(raw_bytes);
      case GROUP::MEM_2:
        return InstructionMem2(raw_bytes);
      case GROUP::BR_ABS:
        return InstructionBranchAbs(raw_bytes);
      case GROUP::ALU3_IND:
        return InstructionALU3Ind(raw_bytes);
      default : 
        break;
      }
      break;
    }
  }
}
