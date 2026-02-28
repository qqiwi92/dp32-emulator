#include "bus.hpp"
#include <cstdint>
#include <fstream>
#include <iomanip>
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
         << "body { font-family: 'Segoe UI', Tahoma, Geneva, Verdana, sans-serif; background: #1e1e1e; color: #d4d4d4; padding: 20px; }"
         << "table { border-collapse: collapse; margin-bottom: 30px; font-size: 12px; }"
         << "th, td { border: 1px solid #444; padding: 6px; text-align: center; min-width: 80px; }"
         << "th { background: #333; }"
         << ".reg-cell { background: #2d2d2d; }"
         << ".mem-cell { background: #1a2a3a; }"
         << ".empty { color: #444; opacity: 0.4; } " // Dimmed style
         << "h2 { color: #569cd6; border-bottom: 1px solid #444; padding-bottom: 10px; }"
         << "strong { color: #9cdcfe; font-size: 10px; }"
         << "</style></head><body>";

    // 1. Registers Grid
    file << "<h2>Registers (R0-R255)</h2><table><tr>";
    for (int i = 0; i < 256; ++i) {
        uint32_t val = cpu.get_reg(i);
        bool is_empty = (val == 0);
        
        if (i > 0 && i % 16 == 0) file << "</tr><tr>";
        
        // Use 'title' attribute for decimal hover, 'empty' class for dimming
        file << "<td class='reg-cell" << (is_empty ? " empty" : "") << "' title='Decimal: " << std::dec << val << "'>";
        file << "<strong>R" << i << "</strong><br>";
        file << "0x" << std::hex << std::setw(8) << std::setfill('0') << val;
        file << "</td>";
    }
    file << "</tr></table>";

    // 2. Memory Grid
    file << "<h2>Memory (Top " << std::dec << mem_range << " words)</h2><table><tr>";
    for (uint32_t i = 0; i < mem_range; ++i) {
        uint32_t val = ram.read(i);
        bool is_empty = (val == 0);

        if (i > 0 && i % 8 == 0) file << "</tr><tr>";

        file << "<td class='mem-cell" << (is_empty ? " empty" : "") << "' title='Decimal: " << std::dec << val << "'>";
        file << "<strong>" << std::hex << std::setw(4) << std::setfill('0') << i << "</strong><br>";
        
        // Logic: Only print the hex value if it's not zero
        if (!is_empty) {
            file << "0x" << std::hex << std::setw(8) << std::setfill('0') << val;
        } else {
            file << "---"; // Placeholder for empty cells
        }
        
        file << "</td>";
    }
    file << "</tr></table></body></html>";
    file.close();
}