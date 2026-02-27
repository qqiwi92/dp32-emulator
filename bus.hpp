#ifndef BUS_HPP
#define BUS_HPP

#include "cpu.hpp"
#include "ram.hpp"

class Bus
{
public:
  RAM ram;
  CPU cpu;
    
  uint8_t cpu_read(uint)
private:
};

#endif
