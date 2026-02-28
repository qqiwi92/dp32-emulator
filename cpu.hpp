#ifndef CPU_HPP
#define CPU_HPP

#include <cstdint>

class Bus;

class CPU {
public:
    CPU(Bus* b);
    void step();

private:
    Bus* bus; 

    uint32_t registers[256]; 
    uint32_t pc;      
    
    bool flag_v, flag_n, flag_z; 

    uint32_t fetch();
    
};

#endif