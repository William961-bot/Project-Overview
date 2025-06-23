// Copyright 2025 William Nosike

#include "FibLFSR.hpp"
#include <iostream>
#include <bitset>
#include <string>

namespace PhotoMagic {

// Initializes the LFSR with the seed
FibLFSR::FibLFSR(const std::string& seed) {
    if (seed.length() != 16) {
        throw std::invalid_argument("Seed must be exactly 16 bits long");
    }
    for (char bit : seed) {
        if (bit != '0' && bit != '1') {
            throw std::invalid_argument("Seed should only contain 0 and 1");
        }
    }

    reg = std::bitset<16>(seed);
}

// Simulate one step of the LFSR
int FibLFSR::step() {
    bool feedback = reg[15] ^ reg[13] ^ reg[12] ^ reg[10];  // XOR taps
    reg <<= 1;  // Shift left
    reg[0] = feedback;  // Insert feedback at position 0
    return feedback;
}

// Generate k-bit integer using LFSR
int FibLFSR::generate(int k) {
    if (k <= 0) {
        throw std::invalid_argument("k must be a positive integer.");
    }

    int result = 0;
    for (int i = 0; i < k; i++) {
        result = (result << 1) | step();
    }
    return result;
}

// Overloaded << operator to print current register state
std::ostream& operator<<(std::ostream& os, const PhotoMagic::FibLFSR& lfsr) {
    os << lfsr.reg.to_string();  // Convert bitset to string for display
    return os;
}

}  // namespace PhotoMagic









