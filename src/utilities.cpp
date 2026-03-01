#include "utilities.hpp"
#include <fstream>
#include <iostream>
#include <vector>
#include <cstdint>
#include <string>

std::vector< uint32_t > load_hex_program(const std::string& filename)
{
  std::vector< uint32_t > program;
  std::ifstream file(filename);
  std::string line;

  if (!file.is_open()) {
    std::cerr << "bad file: " << filename << std::endl;
    return program;
  }

  while (std::getline(file, line)) {
    size_t start = line.find("X\"");
    if (start != std::string::npos) {
      std::string hex_val;
      for (size_t i = start + 2; i < line.length() && hex_val.length() < 8;
           ++i) {
        if (line[i] != '_' && line[i] != '\"') {
          hex_val += line[i];
        }
      }
      if (hex_val.length() == 8) {
        uint32_t word = std::stoul(hex_val, nullptr, 16);
        program.push_back(word);
      }
    }
  }
  return program;
}
