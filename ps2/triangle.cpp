// Copyright 2025 <Jordan Charlot,William nosike>
// triangle.cpp
#include "triangle.hpp"
#include <cmath>

TriangleFractal::TriangleFractal(double length, int depth, float rotation)
    : length(length), depth(depth),
      rotation(rotation), triangles(sf::Triangles) {

    // Calculate height of an equilateral triangle (side length * √3/2)
    float height = static_cast<float>(length * 0.866);
    float halfLength = static_cast<float>(length / 2);
    float halfHeight = height / 2;

    // Position vertices to create a downward-pointing triangle centered at (400, 400):
    generateFractal(
        {400.0f, 400.0f - halfHeight},  // Top vertex
        {400.0f - halfLength, 400.0f + halfHeight},  // Bottom left vertex
        {400.0f + halfLength, 400.0f + halfHeight},  // Bottom right vertex
        depth+1);
}

void TriangleFractal::generateFractal(sf::Vector2f p1,
    sf::Vector2f p2, sf::Vector2f p3, int level) {
    if (level == 0) {
        sf::Color color = getColor(depth - level);
        triangles.append(sf::Vertex(p1, color));
        triangles.append(sf::Vertex(p2, color));
        triangles.append(sf::Vertex(p3, color));
        return;
    }

    // Calculate midpoints of each side of the triangle
    sf::Vector2f mid1 = {(p1.x + p2.x) / 2, (p1.y + p2.y) / 2};  // Midpoint of side p1-p2
    sf::Vector2f mid2 = {(p2.x + p3.x) / 2, (p2.y + p3.y) / 2};  // Midpoint of side p2-p3
    sf::Vector2f mid3 = {(p3.x + p1.x) / 2, (p3.y + p1.y) / 2};  // Midpoint of side p3-p1

    // Draw the central triangle
    sf::Color centerColor = getColor(depth - level + 1);
    triangles.append(sf::Vertex(mid1, centerColor));
    triangles.append(sf::Vertex(mid2, centerColor));
    triangles.append(sf::Vertex(mid3, centerColor));

    // Recursively generate the three corner triangles
    generateFractal(p1, mid1, mid3, level - 1);  // Top/left triangle
    generateFractal(mid1, p2, mid2, level - 1);  // Right triangle
    generateFractal(mid3, mid2, p3, level - 1);  // Bottom triangle
}

sf::Color TriangleFractal::getColor(int level) const {
    int r = (level * 50) % 255;
    int g = (level * 100) % 255;
    int b = (level * 150) % 255;
    return sf::Color(r, g, b);
}

void TriangleFractal::updateRotation(float delta) {
    rotation += delta;
}

void TriangleFractal::draw(sf::RenderTarget& target,
    sf::RenderStates states) const {
    sf::Transform transform;
    transform.rotate(rotation, sf::Vector2f(400, 400));  // Rotate around window center
    states.transform *= transform;
    target.draw(triangles, states);
}

