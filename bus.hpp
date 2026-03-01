#ifndef BUS_HPP
#define BUS_HPP

#include "ram.hpp"
#include <cstdint>
class CPU;
class RAM;

class BUS
{
public:
  RAM ram;

  uint32_t read32(uint32_t address);
  void write32(uint32_t address, uint32_t data);
  void visualize(const CPU& cpu, uint32_t mem_range);
};

#endif
