#ifndef PRINT_HEX_H
#define PRINT_HEX_H

#include <cstdio>
#include <iomanip>
#include <iostream>
#include <string>
template <std::size_t N>
inline void printHex(const unsigned char (&key)[N], const std::string &label) {
  std::cout << label << ": ";
  for (std::size_t i = 0; i < N; ++i) {
    std::printf("%02x", key[i]);
  }
  std::cout << std::endl;
}
void printHex(const unsigned char *data, size_t length) {
  if (!data) {
    std::cerr << "Ciphertext is null!" << std::endl;
    return;
  }
  for (size_t i = 0; i < length; i++) {
    std::cout << std::hex << std::setw(2) << std::setfill('0')
              << static_cast<int>(data[i]);
  }
  std::cout << std::dec << std::endl; // Reset formatting
}
#endif // PRINT_HEX_H
