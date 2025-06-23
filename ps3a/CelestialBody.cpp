// Copyright 2025 William Nosike

#include "CelestialBody.hpp"

namespace NB {

// Default constructor
CelestialBody::CelestialBody()
: x_(0.0), y_(0.0), vx_(0.0), vy_(0.0), mass_(0.0),
texture_(std::make_unique<sf::Texture>()) {
}

// Parameterized constructor
CelestialBody::CelestialBody(double x, double y, double vx, double vy,
                           double mass, const std::string& imageFile)
: x_(x), y_(y), vx_(vx), vy_(vy), mass_(mass), imageFile_(imageFile),
texture_(std::make_unique<sf::Texture>()) {
    loadTextureFromFile(imageFile_);
}

// Copy constructor
CelestialBody::CelestialBody(const CelestialBody& other)
: x_(other.x_), y_(other.y_), vx_(other.vx_), vy_(other.vy_),
mass_(other.mass_), imageFile_(other.imageFile_),
texture_(std::make_unique<sf::Texture>()) {
    if (!other.imageFile_.empty()) {
        loadTextureFromFile(imageFile_);
    }
}

// Copy assignment operator
CelestialBody& CelestialBody::operator=(const CelestialBody& other) {
    if (this != &other) {
        x_ = other.x_;
        y_ = other.y_;
        vx_ = other.vx_;
        vy_ = other.vy_;
        mass_ = other.mass_;
        imageFile_ = other.imageFile_;

        texture_ = std::make_unique<sf::Texture>();
        if (!other.imageFile_.empty()) {
            loadTextureFromFile(imageFile_);
        }
    }
    return *this;
}

// Move constructor
CelestialBody::CelestialBody(CelestialBody&& other) noexcept
: x_(other.x_), y_(other.y_), vx_(other.vx_), vy_(other.vy_),
mass_(other.mass_), imageFile_(std::move(other.imageFile_)),
texture_(std::move(other.texture_)), sprite_(std::move(other.sprite_)) {
}

// Move assignment operator
CelestialBody& CelestialBody::operator=(CelestialBody&& other) noexcept {
    if (this != &other) {
        x_ = other.x_;
        y_ = other.y_;
        vx_ = other.vx_;
        vy_ = other.vy_;
        mass_ = other.mass_;
        imageFile_ = std::move(other.imageFile_);
        texture_ = std::move(other.texture_);
        sprite_ = std::move(other.sprite_);
    }
    return *this;
}

// Set image file and load texture
void CelestialBody::setImageFile(const std::string& imageFile) {
    imageFile_ = imageFile;
    loadTextureFromFile(imageFile_);
}

// Helper method to load texture
bool CelestialBody::loadTextureFromFile(const std::string& filename) {
    if (!texture_->loadFromFile(filename)) {
        std::cerr << "Failed to load texture: " << filename << std::endl;
        return false;
    }

    sprite_.setTexture(*texture_);
    auto bounds = sprite_.getLocalBounds();
    sprite_.setOrigin(bounds.width / 2.f, bounds.height / 2.f);
    return true;
}

// Load from input stream
bool CelestialBody::loadFromStream(std::istream& is) {
    double x, y, vx, vy, mass;
    std::string imageFile;

    is >> x >> y >> vx >> vy >> mass >> imageFile;

    if (is.fail()) {
        return false;
    }

    setX(x);
    setY(y);
    setVX(vx);
    setVY(vy);
    setMass(mass);
    setImageFile(imageFile);

    return true;
}

// Write to output stream
void CelestialBody::writeToStream(std::ostream& os) const {
    os << getX() << " "
       << getY() << " "
       << getVX() << " "
       << getVY() << " "
       << getMass() << " "
       << getImageFile();
}

// Read celestial body data from input stream
std::istream& operator>>(std::istream& is, CelestialBody& body) {
    body.loadFromStream(is);
    return is;
}

// Write celestial body data to output stream
std::ostream& operator<<(std::ostream& os, const CelestialBody& body) {
    body.writeToStream(os);
    return os;
}

// Convert universe coordinates to screen coordinates
void CelestialBody::setScaledPosition(double scaleFactor, float windowSize) {
    float center = windowSize / 2.f;
    float scaledX = static_cast<float>(getX() * scaleFactor + center);
    float scaledY = static_cast<float>(center - getY() * scaleFactor);
    sprite_.setPosition(scaledX, scaledY);
}

// Draw the celestial body to the render target
void CelestialBody::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    target.draw(sprite_, states);
}

}  // namespace NB
