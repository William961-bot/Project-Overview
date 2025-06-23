// Copyright 2025 William Nosike
#ifndef CELESTIALBODY_HPP
#define CELESTIALBODY_HPP

#include <iostream>
#include <string>
#include <memory>
#include <SFML/Graphics.hpp>

namespace NB {

class CelestialBody : public sf::Drawable {
 public:
    CelestialBody();


    friend std::istream& operator>>(std::istream& is, CelestialBody& body);

    friend std::ostream& operator<<(std::ostream& os, const CelestialBody& body);


    void setScaledPosition(double scaleFactor, float windowSize);

    // Getters for physics calculations
    double getX() const { return x_; }
    double getY() const { return y_; }
    double getVX() const { return vx_; }
    double getVY() const { return vy_; }
    double getMass() const { return mass_; }

    // Vector getters
    sf::Vector2f getPosition() const {
        return sf::Vector2f(static_cast<float>(x_), static_cast<float>(y_));
    }
    sf::Vector2f getVelocity() const {
        return sf::Vector2f(static_cast<float>(vx_), static_cast<float>(vy_));
    }

    // Methods for test compatibility
    struct Vector2d {
        double x;
        double y;
    };

    Vector2d position() const { return {x_, y_}; }
    Vector2d velocity() const { return {vx_, vy_}; }
    double mass() const { return mass_; }

    // Update position based on current velocity
    void updatePosition(double dt);
    // Update position directly (for testing)
    void updatePosition(double dx, double dy) { x_ += dx; y_ += dy; }
    // Update velocity based on acceleration
    void updateVelocity(double ax, double ay, double dt);

 private:
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

double x_, y_;  // position
double vx_, vy_;  // velocity
double  mass_;
std::string imageFile_;


std::shared_ptr<sf::Texture> texture_;
sf::Sprite sprite_;
};

}  // namespace NB

#endif
