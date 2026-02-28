#ifndef CPU_HPP
#define CPU_HPP

#include <cstdint>
#include <vector>

class BUS;

class CPU
{
public:
  CPU(BUS* b);
  void step();

private:
  BUS* bus;
  uint32_t regs[256]; // РОН
  uint32_t pc;

  bool v, n, z; // CC

  void update_cc(uint32_t result, bool overflow_happened);
};

#endif
