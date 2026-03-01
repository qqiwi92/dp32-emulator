#ifndef RAM_HPP
#define RAM_HPP

#include <cstdint>
#include <vector>
class RAM
{
public:
  RAM()
  {
    for (int i = 0; i < 65536; i++)
      memory[i] = 0;
  }
  uint32_t read(uint32_t address) { return memory[address]; }
  void write(uint32_t address, uint32_t value) { memory[address] = value; }

private:
  uint32_t memory[65536];
};

#endif
