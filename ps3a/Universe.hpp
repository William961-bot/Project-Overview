// Copyright 2025 William Nosike
#ifndef UNIVERSE_HPP
#define UNIVERSE_HPP

#include <vector>
#include <string>
#include <SFML/Graphics.hpp>
#include "CelestialBody.hpp"

namespace NB {

class Universe : public sf::Drawable {
 public:
    Universe();
    // Simplified constructor for file loading
    explicit Universe(const std::string& filename) : Universe() {
        if (!loadFromFile(filename)) {
            std::cerr << "Universe load failed from file: " << filename << std::endl;
        }
    }

    // Read/write universe data
    friend std::istream& operator>>(std::istream& is, Universe& universe);
    friend std::ostream& operator<<(std::ostream& os, const Universe& universe);

    // Load data from a file
    bool loadFromFile(const std::string& filename);

    // Add new body inline
    void addBody(const CelestialBody& body) { bodies_.push_back(body); }

    // Getter for radius
    double getRadius() const { return radius_; }

    // Setter for radius (mainly for test purposes)
    void setRadius(double radius) { radius_ = radius; }

    // Getters
    std::vector<CelestialBody>& getBodies();

 protected:
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

 private:
    std::vector<CelestialBody> bodies_;
    double radius_;
};

}  // namespace NB

#endif
