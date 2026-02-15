#pragma once
#include "instruction.h"
#include <cstdint>
#include <memory>
#include <unordered_map>
#include <vector>

class Decoder
{
  std::vector<uint8_t> memmory;
  std::unordered_map<uint16_t, BB&> functionTable;

public:
  std::unique_ptr<BB> decodeMethod(uint16_t);
  std::unique_ptr<BB> decodeBB(uint16_t);
  Instruction16 decodeInstruction(uint16_t);
};
