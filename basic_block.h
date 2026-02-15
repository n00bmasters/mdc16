#pragma once

#include "instruction.h"
#include "instructions.h"
#include <cstdint>
#include <vector>

struct BasicBlock {
  const uint16_t addr;

  std::vector<Instruction16> ins;

  BasicBlock *const next;

  BasicBlock(uint16_t addr, std::vector<Instruction16> ins, BasicBlock *next)
      : addr{addr}, ins{ins}, next{next} {}

  Instruction16 &getTerminator();
};
