#pragma once

#include "basic_block.h"
#include "instruction.h"
#include <cstddef>
#include <cstdint>
#include <memory>
#include <unordered_map>
#include <vector>

class Decoder {
  std::vector<std::byte> memory;
  std::unordered_map<uint16_t, BasicBlock *> functionTable;

public:
  BasicBlock *decodeMethod(uint16_t);
  BasicBlock *decodeBB(uint16_t);
  Instruction16 decodeInstruction(uint16_t);
};
