#include "cpu.hpp"
#include "bus.hpp"
#include <cstdint>

CPU::CPU(BUS* b) : bus(b), pc(0), v(false), n(false), z(false)
{
  for (int i = 0; i < 256; i++) {
    regs[i] = 0;
  }
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
    // TODO: THE REST OF THE OPERATIONS
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
