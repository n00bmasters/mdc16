#include "enums.h"  
#include "instructions.h"
#include "instruction.h"
#include "decoder.h"

GROUP getGroup(int number, int n) {
    return static_cast<GROUP>(number & ((1 << n) - 1));
}


Instruction16 Decoder::decodeInstruction(uint16_t raw_bytes) {
    GROUP last;
    
    for (int i = 3; i < 6; i++) {
        last = getGroup(raw_bytes, i);
        
        switch(i) {
            case 3:
                switch(last) {
                    case GROUP::ZERO_OP:
                        return InstructionOneOp(raw_bytes, GROUP::ZERO_OP);
                    case GROUP::IMM_6:
                        return InstructionImm6(raw_bytes, GROUP::IMM_6);
                    case GROUP::IMM_9:
                        return InstructionImm9(raw_bytes, GROUP::IMM_9);
                    case GROUP::BR_REL_N:
                        return InstructionBranchAbsRelN(raw_bytes, GROUP::BR_REL_N);
                    case GROUP::BR_REL_P:
                        return InstructionBranchAbsRelP(raw_bytes, GROUP::BR_REL_P);
                    default:
                        break;
                }
                break;
                
            case 4:
                switch(last) {
                    case GROUP::MEM_3:
                        return InstructionMem3(raw_bytes, GROUP::MEM_3);
                    case GROUP::SHIFTS:
                        return InstructionShift(raw_bytes, GROUP::SHIFTS);
                    case GROUP::ALU3:
                        return InstructionALU3(raw_bytes, GROUP::ALU3);
                    default:
                        break;
                }
                break;
                
            case 5:
                switch(last) {
                    case GROUP::TWO_OP:
                        return InstructionTwoOp(raw_bytes, GROUP::TWO_OP);
                    case GROUP::MEM_2:
                        return InstructionMem2(raw_bytes, GROUP::MEM_2);
                    case GROUP::BR_ABS:
                        return InstructionBranchAbs(raw_bytes, GROUP::BR_ABS);
                    case GROUP::ALU3_IND:
                        return InstructionALU3Ind(raw_bytes, GROUP::ALU3_IND)
                    default:
                        break;
                }
                break;
        }
    }
}
