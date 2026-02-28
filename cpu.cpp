#include "cpu.hpp"
#include "bus.hpp"

CPU::CPU(BUS* b) : bus(b), pc(0), v(false), n(false), z(false) {}

void CPU::step()
{
  uint32_t instr = bus->read32(pc);

  uint8_t op = (instr >> 24) & 0xFF; // 31-24
  uint8_t r3 = (instr >> 16) & 0xFF; // 23-16
  uint8_t r1 = (instr >> 8) & 0xFF;  // 15-8
  uint8_t r2 = instr & 0xFF;         // 7-0

  pc++;

  switch (op) {
    // todo: opps
  }
}
void CPU::update_cc(uint32_t result, bool overflow_happened) {
    z = (result == 0);
    n = (result >> 31) & 1;
    v = overflow_happened;
}
