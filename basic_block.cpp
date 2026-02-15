#include "basic_block.h"

Instruction16 &BasicBlock::getTerminator() { return ins.back(); }
