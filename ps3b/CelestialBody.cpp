// Copyright 2025 William Nosike

#include "CelestialBody.hpp"

namespace NB {

CelestialBody::CelestialBody()
: x_(0.0), y_(0.0), vx_(0.0), vy_(0.0), mass_(0.0),
texture_(std::make_shared<sf::Texture>()) {
}

std::istream& operator>>(std::istream& is, CelestialBody& body) {
    // Format: x y vx vy mass imageFile
    is >> body.x_ >> body.y_
    >> body.vx_ >> body.vy_
    >> body.mass_ >> body.imageFile_;

    if (!body.texture_->loadFromFile(body.imageFile_)) {
        std::cerr << "Failed to load texture: " << body.imageFile_ << std::endl;
    } else {
        body.sprite_.setTexture(*body.texture_);
        sf::FloatRect bounds = body.sprite_.getLocalBounds();
        body.sprite_.setOrigin(bounds.width / 2.f, bounds.height / 2.f);
    }
    return is;
}

std::ostream& operator<<(std::ostream& os, const CelestialBody& body) {
    os << body.x_ << " "
    << body.y_ << " "
    << body.vx_ << " "
    << body.vy_ << " "
    << body.mass_ << " "
    << body.imageFile_;
    return os;
}

void CelestialBody::setScaledPosition(double scaleFactor, float windowSize) {
    float scaledX = static_cast<float>(x_ * scaleFactor + windowSize / 2.f);
    float scaledY = static_cast<float>(windowSize / 2.f - y_ * scaleFactor);
    sprite_.setPosition(scaledX, scaledY);
}

void CelestialBody::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    target.draw(sprite_, states);
}

void CelestialBody::updatePosition(double dt) {
    // Update position based on current velocity
    x_ += vx_ * dt;
    y_ += vy_ * dt;
}

void CelestialBody::updateVelocity(double ax, double ay, double dt) {
    // Update velocity based on acceleration
    vx_ += ax * dt;
    vy_ += ay * dt;
}

}  // namespace NB
