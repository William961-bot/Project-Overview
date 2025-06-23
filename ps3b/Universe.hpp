
// Copyright 2025 William Nosike
#ifndef UNIVERSE_HPP
#define UNIVERSE_HPP

#include <vector>
#include <string>
#include <memory>
#include <iostream>
#include <SFML/Graphics.hpp>
#include "CelestialBody.hpp"

namespace NB {

class Universe : public sf::Drawable {
 public:
    Universe();  // Default Constructor
    explicit Universe(const std::string& filename);

    virtual void step(double dt);  // Physics simulation step - made virtual for testing
    void addBody(const CelestialBody& body);
    double getRadius() const;

    // Get reference to the bodies collection
    std::vector<std::shared_ptr<CelestialBody>>& getBodies();

    // Array access operators - made virtual for testing
    virtual CelestialBody& operator[](size_t index);
    virtual const CelestialBody& operator[](size_t index) const;

    // File I/O
    friend std::istream& operator>>(std::istream& is, Universe& uni);
    friend std::ostream& operator<<(std::ostream& os, const Universe& uni);

 protected:
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

 private:
    void calculateForces(std::vector<double>& fx, std::vector<double>& fy) const;

    double radius_;
    std::vector<std::shared_ptr<CelestialBody>> bodies_;  // List of celestial bodies

    static constexpr double G = 6.67e-11;  // Gravitational constant
};

}  // namespace NB

#endif  // UNIVERSE_HPP
