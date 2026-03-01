#include "cpu.hpp"
#include "bus.hpp"
#include <cstdint>

CPU::CPU(BUS* b) : bus(b), pc(0), v(false), n(false), z(false)
{
  for (int i = 0; i < 256; i++) {
    regs[i] = 0;
  }
}

uint32_t CPU::next_32bit_word()
{
  uint32_t word = bus->read32(pc);
  pc++;
  return word;
}
bool CPU::flags_check(uint8_t mask) {
    bool iv = (mask >> 3) & 1; 
    bool mv = (mask >> 2) & 1; 
    bool mn = (mask >> 1) & 1; 
    bool mz = (mask >> 0) & 1; 

    bool condition = (mv && v) || (mn && n) || (mz && z);
    return condition == iv; 
}

void CPU::step()
{
  uint32_t instr = bus->read32(pc);

  uint8_t op = (instr >> 24) & 0xFF; // 31-24
  uint8_t r3 = (instr >> 16) & 0xFF; // 23-16
  uint8_t r1 = (instr >> 8) & 0xFF;  // 15-8
  uint8_t r2 = instr & 0xFF;         // 7-0

  pc++;

  switch (op) {
  case 0x00:
    execute_add(r3, r1, r2);
    break;
  case 0x01:
    execute_substruct(r3, r1, r2);
    break;
  case 0x02:
    execute_multiply(r3, r1, r2);
    break;
  case 0x03:
    execute_divide(r3, r1, r2);
    break;

  case 0x04:
    execute_and(r3, r1, r2);
    break;
  case 0x05:
    execute_or(r3, r1, r2);
    break;
  case 0x06:
    execute_xor(r3, r1, r2);
    break;
  case 0x07:
    execute_mask(r3, r1, r2);
    break;

  case 0x10:
    execute_add_quick(r3, r1, r2);
    break;
  case 0x11:
    execute_substruct_quick(r3, r1, r2);
    break;
  case 0x12:
    execute_multiply_quick(r3, r1, r2);
    break;
  case 0x13:
    execute_divide_quick(r3, r1, r2);
    break;

  case 0x20:
    execute_load(r3, r1, r2);
    break;
  case 0x21:
    execute_store(r3, r1, r2);
    break;
  case 0x30:
    execute_load_quick(r3, r1, r2);
    break;
  case 0x31:
    execute_store_quick(r3, r1, r2);
    break;

  case 0x40:
    execute_branch(instr);
    break;
  case 0x41:
    execute_branch_indexed(instr);
    break;
  case 0x50:
    execute_branch_quick(instr);
    break;

  default:
    break;
  }
}
void CPU::update_cc(uint32_t result, bool overflow_happened)
{
  z = (result == 0);
  n = (result >> 31) & 1;
  v = overflow_happened;
}

uint32_t CPU::get_reg(int index) const { return regs[index]; }
void CPU::set_reg(uint8_t index, uint32_t value) { regs[index] = value; }

void CPU::execute_add(uint8_t r3, uint8_t r1, uint8_t r2)
{
  int32_t a = static_cast< int32_t >(regs[r1]);
  int32_t b = static_cast< int32_t >(regs[r2]);

  int32_t res = a + b;
  bool ovf = false;

  if (b > 0 && a > (INT32_MAX - b))
    ovf = true;
  else if (b < 0 && a < (INT32_MIN - b))
    ovf = true;

  regs[r3] = static_cast< uint32_t >(res);

  update_cc(regs[r3], ovf);
}

void CPU::execute_add_quick(uint8_t r3, uint8_t r1, uint8_t r2)
{
  int32_t a = static_cast< int32_t >(regs[r1]);
  int32_t b = static_cast< int32_t >(r2);

  int32_t res = a + b;
  bool ovf = false;

  if (b > 0 && a > (INT32_MAX - b))
    ovf = true;
  else if (b < 0 && a < (INT32_MIN - b))
    ovf = true;

  regs[r3] = static_cast< uint32_t >(res);

  update_cc(regs[r3], ovf);
}

void CPU::execute_substruct(uint8_t r3, uint8_t r1, uint8_t r2)
{
  int32_t a = static_cast< int32_t >(regs[r1]);
  int32_t b = static_cast< int32_t >(regs[r2]);

  int32_t res = a - b;
  bool ovf = false;

  if (b > 0 && a < (INT32_MIN + b))
    ovf = true;
  else if (b < 0 && a > (INT32_MAX + b))
    ovf = true;

  regs[r3] = static_cast< uint32_t >(res);

  update_cc(regs[r3], ovf);
}

void CPU::execute_substruct_quick(uint8_t r3, uint8_t r1, uint8_t r2)
{
  int32_t a = static_cast< int32_t >(regs[r1]);
  int32_t b = static_cast< int32_t >(r2);

  int32_t res = a - b;
  bool ovf = false;

  if (b > 0 && a < (INT32_MIN + b))
    ovf = true;
  else if (b < 0 && a > (INT32_MAX + b))
    ovf = true;

  regs[r3] = static_cast< uint32_t >(res);

  update_cc(regs[r3], ovf);
}

void CPU::execute_divide(uint8_t r3, uint8_t r1, uint8_t r2)
{
  int32_t a = static_cast< int32_t >(regs[r1]);
  int32_t b = static_cast< int32_t >(regs[r2]);
  int32_t res;
  bool ovf;
  if (b == 0) {
    res = a >= 0 ? INT32_MAX : INT32_MIN;
    ovf = true;
  } else if (a == INT32_MIN && b == -1) {
    res = INT32_MIN;
    ovf = true;
  } else {

    res = a / b;
    ovf = false;
  }

  regs[r3] = static_cast< uint32_t >(res);

  update_cc(regs[r3], ovf);
}

void CPU::execute_divide_quick(uint8_t r3, uint8_t r1, uint8_t r2)
{
  int32_t a = static_cast< int32_t >(regs[r1]);
  int32_t b = static_cast< int32_t >(r2);
  int32_t res;
  bool ovf;
  if (b == 0) {
    res = a >= 0 ? INT32_MAX : INT32_MIN;
    ovf = true;
  } else if (a == INT32_MIN && b == -1) {
    res = INT32_MIN;
    ovf = true;
  } else {

    res = a / b;
    ovf = false;
  }

  regs[r3] = static_cast< uint32_t >(res);

  update_cc(regs[r3], ovf);
}

void CPU::execute_multiply(uint8_t r3, uint8_t r1, uint8_t r2)
{
  int32_t a = static_cast< int32_t >(regs[r1]);
  int32_t b = static_cast< int32_t >(regs[r2]);
  int32_t res;
  bool ovf = false;

  if (a == 0 || b == 0) {
    res = 0;
  } else {
    int64_t wide_res = static_cast< int64_t >(a) * static_cast< int64_t >(b);

    if (wide_res > INT32_MAX) {
      res = INT32_MAX;
      ovf = true;
    } else if (wide_res < INT32_MIN) {
      res = INT32_MIN;
      ovf = true;
    } else {
      res = static_cast< int32_t >(wide_res);
    }
  }

  regs[r3] = static_cast< uint32_t >(res);
  update_cc(regs[r3], ovf);
}

void CPU::execute_multiply_quick(uint8_t r3, uint8_t r1, uint8_t r2)
{
  int32_t a = static_cast< int32_t >(regs[r1]);
  int32_t b = static_cast< int32_t >(r2);
  int32_t res;
  bool ovf = false;

  if (a == 0 || b == 0) {
    res = 0;
  } else {
    int64_t wide_res = static_cast< int64_t >(a) * static_cast< int64_t >(b);

    if (wide_res > INT32_MAX) {
      res = INT32_MAX;
      ovf = true;
    } else if (wide_res < INT32_MIN) {
      res = INT32_MIN;
      ovf = true;
    } else {
      res = static_cast< int32_t >(wide_res);
    }
  }

  regs[r3] = static_cast< uint32_t >(res);
  update_cc(regs[r3], ovf);
}

void CPU::execute_and(uint8_t r3, uint8_t r1, uint8_t r2)
{
  uint32_t a = regs[r1];
  uint32_t b = regs[r2];
  int32_t res = a & b;
  bool ovf = false;

  regs[r3] = static_cast< uint32_t >(res);

  update_cc(regs[r3], ovf);
}

void CPU::execute_or(uint8_t r3, uint8_t r1, uint8_t r2)
{
  uint32_t a = regs[r1];
  uint32_t b = regs[r2];
  int32_t res = a | b;
  bool ovf = false;

  regs[r3] = static_cast< uint32_t >(res);

  update_cc(regs[r3], ovf);
}
void CPU::execute_xor(uint8_t r3, uint8_t r1, uint8_t r2)
{
  uint32_t a = regs[r1];
  uint32_t b = regs[r2];
  int32_t res = a ^ b;
  bool ovf = false;

  regs[r3] = static_cast< uint32_t >(res);

  update_cc(regs[r3], ovf);
}
void CPU::execute_mask(uint8_t r3, uint8_t r1, uint8_t r2)
{
  uint32_t a = regs[r1];
  uint32_t b = regs[r2];
  int32_t res = a & (~b);
  bool ovf = false;

  regs[r3] = static_cast< uint32_t >(res);

  update_cc(regs[r3], ovf);
}

void CPU::execute_branch(uint32_t word)
{
  uint8_t cond_mask = (word >> 16) & 0x0F;
  int32_t displacement = static_cast< int32_t >(next_32bit_word());
  
  if (flags_check(cond_mask)) {
    pc = pc + displacement;
  }
}
