#ifndef RAM_HPP
#define RAM_HPP

#include <cstdint>
#include <vector>
class RAM
{
public:
  RAM() : memory(4ULL * 1024 * 1024 * 1024, 0) {}
  uint8_t read(uint32_t address) { return memory[address]; }
  void write(uint32_t address, uint8_t value) { memory[address] = value; }

private:
  std::vector< uint8_t > memory;
};


#endif 