#include "bus.hpp"
#include <cstdint>

uint32_t BUS::read32(uint32_t addr) {
  return ram.read(addr);
}
void BUS::write32(uint32_t addr, uint32_t val) {
  ram.write(addr, val);
}