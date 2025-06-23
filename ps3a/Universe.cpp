// Copyright 2025 William Nosike
#include "Universe.hpp"
#include <fstream>
#include <iostream>

namespace NB {

// Constructor with default universe radius
Universe::Universe() : radius_(0.0) {}


bool Universe::loadFromFile(const std::string& filename) {
    std::ifstream file(filename);
    if (!file) {
        return false;
    }
    return static_cast<bool>(file >> *this);
}

// Input stream operator
std::istream& operator>>(std::istream& is, Universe& universe) {
    int count;
    double radius;
    is >> count >> radius;
    universe.radius_ = radius;
    universe.bodies_.clear();
    universe.bodies_.reserve(count);

    for (int i = 0; i < count; ++i) {
        CelestialBody body;
        is >> body;
        universe.bodies_.push_back(body);
    }

    return is;
}

// Output stream operator
// Writes size, radius, and each body on separate lines
std::ostream& operator<<(std::ostream& os, const Universe& universe) {
    os << universe.bodies_.size() << " " << universe.radius_ << "\n";
    for (const auto& body : universe.bodies_) {
        os << body << "\n";
    }
    return os;
}

// Returns reference to the collection of celestial bodies
std::vector<CelestialBody>& Universe::getBodies() {
    return bodies_;
}

// Renders all celestial bodies
void Universe::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    for (const auto& body : bodies_) {
        target.draw(body, states);
    }
}

}  // namespace NB
