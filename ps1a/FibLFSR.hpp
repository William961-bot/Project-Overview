// Copyright 2025 William Nosike

#include <iostream>
#include <string>
#include <bitset>

namespace PhotoMagic {

class FibLFSR {
 public:
    explicit FibLFSR(const std::string& seed);
    int step();  // Simulate one step and return the new bit
    int generate(int k);  // Simulate k steps and return a k-bit integer

    friend std::ostream& operator<<(std::ostream& os, const FibLFSR& lfsr);

 private:
    std::bitset<16> reg;  // Internal LFSR register
};

}  // namespace PhotoMagic


