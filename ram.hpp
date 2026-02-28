#ifndef RAM_HPP
#define RAM_HPP

#include <cstdint>
#include <vector>
class RAM
{
public:
  RAM() : memory(1024 * 1024, 0) {}
  uint8_t read(uint32_t address) { return memory[address]; }
  void write(uint32_t address, uint32_t value) { memory[address] = value; }

private:
  std::vector< uint32_t > memory;
};


#endif 