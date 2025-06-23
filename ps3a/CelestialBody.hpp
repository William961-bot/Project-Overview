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
    // Constructors
    CelestialBody();
    CelestialBody(double x, double y, double vx, double vy,
                 double mass, const std::string& imageFile);

    // Copy/move operations
    CelestialBody(const CelestialBody& other);
    CelestialBody& operator=(const CelestialBody& other);
    CelestialBody(CelestialBody&& other) noexcept;
    CelestialBody& operator=(CelestialBody&& other) noexcept;

    // Getters
    double getX() const { return x_; }
    double getY() const { return y_; }
    double getVX() const { return vx_; }
    double getVY() const { return vy_; }
    double getMass() const { return mass_; }
    const std::string& getImageFile() const { return imageFile_; }

    // Setters
    void setX(double x) { x_ = x; }
    void setY(double y) { y_ = y; }
    void setVX(double vx) { vx_ = vx; }
    void setVY(double vy) { vy_ = vy; }
    void setMass(double mass) { mass_ = mass; }
    void setImageFile(const std::string& imageFile);

    // Stream operations
    bool loadFromStream(std::istream& is);
    void writeToStream(std::ostream& os) const;

    // Position and rendering
    void setScaledPosition(double scaleFactor, float windowSize);

 private:
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
    bool loadTextureFromFile(const std::string& filename);

    double x_, y_;  // position
    double vx_, vy_;  // velocity
    double mass_;
    std::string imageFile_;

    // For SFML rendering
    std::unique_ptr<sf::Texture> texture_;
    sf::Sprite sprite_;
};

// Free functions for stream operators
std::istream& operator>>(std::istream& is, CelestialBody& body);
std::ostream& operator<<(std::ostream& os, const CelestialBody& body);

}  // namespace NB

#endif
