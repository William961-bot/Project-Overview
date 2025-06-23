// Copyright 2025 William Nosike

#include "Universe.hpp"
#include <fstream>
#include <cmath>

namespace NB {

Universe::Universe() : radius_(0.0) {
}

Universe::Universe(const std::string& filename) : radius_(0.0) {
    std::ifstream file(filename);
    if (!file) {
        std::cerr << "Error opening file: " << filename << std::endl;
        return;
    }

    // Read the number of bodies and radius
    int numBodies;
    file >> numBodies >> radius_;

    // Read each celestial body
    for (int i = 0; i < numBodies; i++) {
        auto body = std::make_shared<CelestialBody>();
        file >> *body;
        bodies_.push_back(body);
    }
}

void Universe::addBody(const CelestialBody& body) {
    bodies_.push_back(std::make_shared<CelestialBody>(body));
}

double Universe::getRadius() const {
    return radius_;
}

std::vector<std::shared_ptr<CelestialBody>>& Universe::getBodies() {
    return bodies_;
}


void Universe::calculateForces(std::vector<double>& fx, std::vector<double>& fy) const {
    // Reset all forces to zero (principle of superposition)
    std::fill(fx.begin(), fx.end(), 0.0);
    std::fill(fy.begin(), fy.end(), 0.0);

    // Calculate pairwise forces between all bodies
    for (size_t i = 0; i < bodies_.size(); i++) {
        for (size_t j = i + 1; j < bodies_.size(); j++) {
            auto body1 = bodies_[i];
            auto body2 = bodies_[j];

            // Calculate distance vector components
            double dx = body2->getX() - body1->getX();
            double dy = body2->getY() - body1->getY();

            // Calculate distance (magnitude)
            double dist = std::hypot(dx, dy);

            // Avoid division by zero for very close bodies
            if (dist < 1e-10) continue;

            // Newton's law of universal gravitation:
            // F = G * (m1 * m2) / r^2
            double force = (G * body1->getMass() * body2->getMass()) / (dist * dist);

            // Calculate force vector components by projecting along distance vector
            double fx_ij = force * dx / dist;  // Force along x-axis
            double fy_ij = force * dy / dist;  // Force along y-axis

            // Apply principle of superposition by adding this force to both bodies
            // (equal and opposite forces according to Newton's third law)
            fx[i] += fx_ij;
            fy[i] += fy_ij;
            fx[j] -= fx_ij;
            fy[j] -= fy_ij;
        }
    }
}

void Universe::step(double dt) {
    if (bodies_.empty()) return;

    //  Compute forces for each particle using Newton's law of gravitation
    std::vector<double> fx(bodies_.size(), 0.0);
    std::vector<double> fy(bodies_.size(), 0.0);
    calculateForces(fx, fy);

    // For each particle, calculate acceleration and update velocity
    for (size_t i = 0; i < bodies_.size(); i++) {
        // Calculate acceleration using Newton's second law: a = F/m
        double ax = fx[i] / bodies_[i]->getMass();
        double ay = fy[i] / bodies_[i]->getMass();

        // Update velocity: v_new = v_old + dt * a
        bodies_[i]->updateVelocity(ax, ay, dt);
    }

    // Update positions using the new velocities
    for (auto& body : bodies_) {
        // Update position
        body->updatePosition(dt);
    }
}




void Universe::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    // Scale for rendering
    double scaleFactor = (radius_ != 0.0) ? (400.0 / radius_) : 1.0;
    float windowSize = static_cast<float>(std::min(target.getSize().x, target.getSize().y));

    // Draw each body
    for (const auto& body : bodies_) {
        CelestialBody renderBody = *body;
        renderBody.setScaledPosition(scaleFactor, windowSize);
        target.draw(renderBody, states);
    }
}

std::istream& operator>>(std::istream& is, Universe& uni) {
    int numBodies;
    is >> numBodies >> uni.radius_;

    uni.bodies_.clear();
    for (int i = 0; i < numBodies; i++) {
        auto body = std::make_shared<CelestialBody>();
        is >> *body;
        uni.bodies_.push_back(body);
    }

    return is;
}

std::ostream& operator<<(std::ostream& os, const Universe& uni) {
    os << uni.bodies_.size() << " " << uni.radius_ << std::endl;
    for (const auto& body : uni.bodies_) {
        os << *body << std::endl;
    }
    return os;
}

CelestialBody& Universe::operator[](size_t index) {
    return *bodies_[index];
}

const CelestialBody& Universe::operator[](size_t index) const {
    return *bodies_[index];
}

}  // namespace NB
