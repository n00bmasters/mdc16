
enum class alu3_ind_op_type { BIT, CMP = 6 };

enum class alu3_op_type { AND, OR, XOR, BIC, ADD, ADDC, SUB, SUBC };

enum class alu2_op_type { NEG, NOT, SXT, SCL };

enum class shifts_op_type { SHL, SHR, SHRA, ROL, ROR, RCL, RCR };

enum class mem3_opt_type { LDW, LDB, LDSB, LCW, LCB, LCSB, STW, STB };

enum class imm9_op_type { INT = 0, RESET = 1, PUSH = 2, ADDSP = 6, JSR = 8 };

enum class zero_op {
  ZERO,
  RESERVED1,
  RESERVED2,
  RESERVED3,
  HALT,
  WAIT,
  EI,
  DI,
  JSR,
  PUPC,
  POPC,
  PUSP,
  POSP,
  PUPS,
  POPS,
};

enum class one_op { PUSH, POP, LDI, JSRR, LDSP, STSP, LDPC, STPS, ADDSP };

enum class two_op { MOVE };

enum class mem2_op { LDW, LBD, LDSB, LEW, LEB, LCSB, STW, STB };

enum class imm_6_op {
  LSW,
  LSB,
  LSSB,
  SSW,
  SSB,
  LDI,
  ADD,
  CMP,
};

enum class GROUP {
  ZERO_OP = 0b0,
  ONE_OP = 0b001,
  TWO_OP = 0b01000,
  MEM_2 = 0b01010,
  IMM_6 = 0b011,
  IMM_9 = 0b100,
  MEM_3 = 0b1010,
  BR_ABS = 0b00001,
  BR_REL_N = 0b110,
  BR_REL_P = 0b111,
  SHIFTS = 0b0001
};
