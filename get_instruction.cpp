#include "enums.h"
#include "instructions.h"
#include "instruction.h"

int getLastNBits(int number, int n) {
    return number & ((1 << n) - 1)
};


Instruction16 get_instruction(int raw_bytes) {
    int last;
    for (int i = 3; i < 6; i++) {
        last = getLastNBits(raw_bytes, i);
        switch(i) {
            case 3:
                switch(last) {
                    case GROUP.ZERO_OP:
                        return InstructionOneOP(raw_bytes, static_cast<InstructionOneOp>(GROUP.ZERO_OP));
                    case GROUP.IMM_6:
                        return InstructionImm6(raw_bytes, static_cast<InstructionImm6>(GROUP.IMM_6));
                    case GROUP.IMM_9:
                        return InstructionImm9(raw_bytes, static_cast<InstructionImm9>(GROUP.IMM_9));
                    case GROUP.BR_REL_N:
                        return InstructionBranchAbsN(raw_bytes, static_cast<InstructionBranchRelN>(GROUP.BR_REL_N));
                    case GROUP.BR_REL_P:
                        return InstructionBranchAbsP(raw_bytes, static_cast<InstructionBranchAbsRelP>(GROUP.BR_REL_P));
                }
            case 4:
                switch(last) {
                    case GROUP.MEM_3:
                        return InstructionMem3(raw_bytes, static_cast<InstructionMem3>(GROUP.MEM_3));
                    case GROUP.SHIFTS:
                        return InstructionShifts(raw_bytes, static_cast<InstructionShifts>(GROUP.SHIFTS));
                    case GROUP.ALU3:
                        return InstructionAlu3(raw_bytes, static_cast<InstructionAlu3>(GROUP.ALU3));
                }
            case 5:
                switch(last): {
                    case GROUP.TWO_OP:
                        return InstructionTwoOp(raw_bytes, static_cast<InstructionTwoOp>(GROUP.TWO_OP));
                    case GROUP.MEM_2:
                        return InstructionMem2(raw_bytes, static_cast<InstructionMem2>(GROUP.MEM_2));
                    case GROUP.BR_ABS:
                        return InstructionBranchAbs(raw_bytes, static_cast<InstructionBranchAbs>(GROUP.BR_ABS));
                    
                }
        }
    }
}