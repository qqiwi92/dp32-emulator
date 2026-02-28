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
  uint32_t get_reg(int index) const;
  void set_reg(uint8_t index, uint32_t value) ;
  bool get_z() const { return z; }
  bool get_n() const { return n; }
  bool get_v() const { return v; }
private:
  BUS* bus;
  uint32_t regs[256]; // РОН
  uint32_t pc;

  bool v, n, z; // CC

  void update_cc(uint32_t result, bool overflow_happened);

  // alu funcs
  void execute_add(uint8_t r3, uint8_t r1, uint8_t r2);
};

#endif
