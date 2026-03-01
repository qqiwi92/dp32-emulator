#include "bus.hpp"
#include "cpu.hpp"
#include <iostream>

int main() {
    BUS bus;
    CPU cpu(&bus);

    cpu.set_reg(1, 10);
    cpu.set_reg(2, 20);
    
    bus.write32(0, 0x00030102);

    std::cout << "Running Step 1 (Normal Add)..." << std::endl;
    cpu.step(); 
    std::cout << "R3 result: " << std::dec << cpu.get_reg(3) << " (Expected 30)" << std::endl;
    std::cout << "Flags - Z: " << cpu.get_z() << " N: " << cpu.get_n() << " V: " << cpu.get_v() << std::endl;

    cpu.set_reg(5, 0x7FFFFFFF); 
    cpu.set_reg(6, 1);
    
    bus.write32(1, 0x00040506);

    std::cout << "\nRunning Step 2 (Overflow Add)..." << std::endl;
    cpu.step(); 
    std::cout << "R4 result: 0x" << std::hex << cpu.get_reg(4) << " (Expected 0x80000000)" << std::endl;
    std::cout << "Flags - Z: " << cpu.get_z() << " N: " << cpu.get_n() << " V: " << cpu.get_v() << std::endl;

    cpu.set_reg(8, 0xFFFFFFFB); // -5
    cpu.set_reg(9, 5);
    
    bus.write32(2, 0x00070809);

    std::cout << "\nRunning Step 3 (Zero test)..." << std::endl;
    cpu.step();
    std::cout << "R7 result: " << std::dec << cpu.get_reg(7) << " (Expected 0)" << std::endl;
    std::cout << "Flags - Z: " << cpu.get_z() << " N: " << cpu.get_n() << " V: " << cpu.get_v() << std::endl;

    bus.visualize(cpu, 10); 

    return 0;
}