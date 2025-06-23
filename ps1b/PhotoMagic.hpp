// Copyright 2025 William Nosike
#ifndef PHOTOMAGIC_HPP
#define PHOTOMAGIC_HPP

#include <SFML/Graphics.hpp>
#include "FibLFSR.hpp"

namespace PhotoMagic {void transform(sf::Image& img, FibLFSR* lfsr);
}

#endif  // PHOTOMAGIC_HPP
