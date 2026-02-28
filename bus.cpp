#include "bus.hpp"
#include <cstdint>
#include <fstream>
#include <iomanip>
#include <sstream>
#include "cpu.hpp"
uint32_t BUS::read32(uint32_t addr) {
  return ram.read(addr);
}
void BUS::write32(uint32_t addr, uint32_t val) {
  ram.write(addr, val);
}

void BUS::visualize(const CPU& cpu, uint32_t mem_range) {
    std::ofstream file("vdp32_dump.html");
    
    file << "<html><head><style>"
         << "body { font-family: sans-serif; background: #1e1e1e; color: #d4d4d4; }"
         << "table { border-collapse: collapse; margin-bottom: 20px; }"
         << "th, td { border: 1px solid #444; padding: 8px; text-align: center; }"
         << "th { background: #333; }"
         << ".reg-cell { background: #2d2d2d; }"
         << ".mem-cell { background: #1a2a3a; }"
         << "h2 { color: #569cd6; }"
         << "</style></head><body>";

    // 1. Сетка регистров (16x16 = 256)
    file << "<h2>Registers (R0-R255)</h2><table><tr>";
    for (int i = 0; i < 256; ++i) {
        if (i > 0 && i % 16 == 0) file << "</tr><tr>";
        file << "<td class='reg-cell'><strong>R" << i << "</strong><br>" 
             << "0x" << std::hex << std::setw(8) << std::setfill('0') << cpu.get_reg(i) 
             << "</td>";
    }
    file << "</tr></table>";

    // 2. Сетка памяти (первые mem_range ячеек)
    file << "<h2>Memory (Top " << std::dec << mem_range << " words)</h2><table><tr>";
    for (uint32_t i = 0; i < mem_range; ++i) {
        if (i > 0 && i % 8 == 0) file << "</tr><tr>";
        file << "<td class='mem-cell'><strong>addr: " << i << "</strong><br>"
             << "0x" << std::hex << std::setw(8) << std::setfill('0') << ram.read(i)
             << "</td>";
    }
    file << "</tr></table>";

    file << "</body></html>";
    file.close();
}