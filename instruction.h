#pragma once
#include <cstdint>
#include <memory>
#include <string>

class Instruction16 {
public:
  explicit Instruction16(uint16_t raw) : _raw(raw) {}

  uint16_t getRaw() const { return _raw; }

  virtual ~Instruction16() = default;

protected:
  uint16_t _raw;
};
