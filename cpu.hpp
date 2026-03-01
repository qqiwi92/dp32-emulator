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
  void set_reg(uint8_t index, uint32_t value);
  bool get_z() const { return z; }
  bool get_n() const { return n; }
  bool get_v() const { return v; }

private:
  BUS* bus;
  uint32_t regs[256]; // РОН
  uint32_t pc;

  bool v, n, z; // CC

  void update_cc(uint32_t result, bool overflow_happened);
  uint32_t next_32bit_word();
  bool flags_check(uint8_t flags);
  // alu funcs
  void execute_add(uint8_t r3, uint8_t r1, uint8_t r2);
  void execute_substruct(uint8_t r3, uint8_t r1, uint8_t r2);
  void execute_multiply(uint8_t r3, uint8_t r1, uint8_t r2);
  void execute_divide(uint8_t r3, uint8_t r1, uint8_t r2);

  void execute_add_quick(uint8_t r3, uint8_t r1, uint8_t r2);
  void execute_substruct_quick(uint8_t r3, uint8_t r1, uint8_t r2);
  void execute_multiply_quick(uint8_t r3, uint8_t r1, uint8_t r2);
  void execute_divide_quick(uint8_t r3, uint8_t r1, uint8_t r2);

  // logical stuff
  void execute_and(uint8_t r3, uint8_t r1, uint8_t r2);
  void execute_or(uint8_t r3, uint8_t r1, uint8_t r2);
  void execute_xor(uint8_t r3, uint8_t r1, uint8_t r2);
  void execute_mask(uint8_t r3, uint8_t r1, uint8_t r2);
  
  // ram communication
  void execute_load(uint8_t r3, uint8_t r1, uint8_t r2);
  void execute_store(uint8_t r3, uint8_t r1, uint8_t r2);
  
  void execute_load_quick(uint8_t r3, uint8_t r1, uint8_t r2);
  void execute_store_quick(uint8_t r3, uint8_t r1, uint8_t r2);
  
  //branch-jumping
  void execute_branch(uint32_t word);
  void execute_branch_quick(uint32_t word);
  void execute_branch_indexed(uint32_t word);

};

#endif
