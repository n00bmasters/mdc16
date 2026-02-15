#pragma once

#include "basic_block.h"
#include "instruction.h"
#include <cstddef>
#include <cstdint>
#include <memory>
#include <unordered_map>
#include <vector>

class Decoder {
public:
  using FunctionTable = std::unordered_map<uint16_t, BasicBlock *>;

  Decoder(std::vector<std::byte> memory) : memory{memory}, functionTable{} {}

  BasicBlock *decodeMethod(uint16_t);
  BasicBlock *decodeBB(uint16_t);
  Instruction16 decodeInstruction(uint16_t);

  FunctionTable decode();

private:
  std::vector<std::byte> memory;
  std::unordered_map<uint16_t, BasicBlock *> functionTable;
};
