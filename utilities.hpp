#ifndef UTILITIES_HPP
#define UTILITIES_HPP

#include <iostream>
#include <vector>

template < typename T > void print(const T& value)
{
  std::cout << "Single value: " << value << std::endl;
}

template < typename T > void print(const std::vector< T >& vec)
{
  std::cout << "Vector: ";
  for (const auto& elem : vec) {
    std::cout << elem << " ";
  }
  std::cout << std::endl;
}

inline void print(const char* vec) { std::cout << vec << std::endl; }

#endif
