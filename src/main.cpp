#include "bus.hpp"
#include "cpu.hpp"
#include "utilities.hpp"
#include <vector>

int main()
{
  BUS bus;
  CPU cpu(&bus);

  std::vector< uint32_t > program =
      load_hex_program("vhdl/input_algorithm.vhd");

  if (program.empty()) {
    return 1;
  }

  for (size_t i = 0; i < program.size(); ++i) {
    bus.write32(i, program[i]);
  }

  while (cpu.get_pc() < program.size()) {
    cpu.step();
  }
}
