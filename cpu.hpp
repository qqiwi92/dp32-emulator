#ifndef CPU_HPP
#define CPU_HPP

#include <cstdint>
#include <vector>

class CPU
{
public:
  CPU() : registers(255, 0) {}
  void step();
private:
  std::vector< uint32_t > registers;
};

#endif
