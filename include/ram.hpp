#ifndef RAM_HPP
#define RAM_HPP

#include <cstdint>
#include <iostream>
class RAM
{
public:
  RAM()
  {
    for (int i = 0; i < 65536; i++)
      memory[i] = 0;
  }
  uint32_t read(uint32_t address)
  {
    if (address >= 65536) {
      int32_t int_repr = static_cast< int32_t >(address);
      if (int_repr < 0) {
        std::cerr
            << "You've likely overflowed by passing negative displacement\n";
      }
      std::cerr << "SEGFAULT: Attempt to read address " << address << std::endl;
      return 0;
    }
    return memory[address];
  }
  void write(uint32_t address, uint32_t value)
  {
    if (address >= 65536) {
      int32_t int_repr = static_cast< int32_t >(address);
      if (int_repr < 0) {
        std::cerr
            << "You've likely overflowed by passing negative displacement\n";
      }
      std::cerr << "SEGFAULT: Attempt to write address " << address
                << std::endl;
      return;
    }
    memory[address] = value;
  }

private:
  uint32_t memory[65536];
};

#endif
