// Copyright 2025 <Jordan Charlot,William Nosike>

#ifndef _HOME_JGCHARLOT615_COMPIV_PS2_TRIANGLE_HPP_
#define _HOME_JGCHARLOT615_COMPIV_PS2_TRIANGLE_HPP_

#include <vector>
#include <SFML/Graphics.hpp>

class TriangleFractal : public sf::Drawable {
 public:
    TriangleFractal(double length, int depth, float rotation = 0.0f);
    void updateRotation(float delta);

 private:
    double length;
    int depth;
    float rotation;
    sf::VertexArray triangles;

    void generateFractal(sf::Vector2f p1, sf::Vector2f p2,
                         sf::Vector2f p3, int level);
    sf::Color getColor(int level) const;

    void draw(sf::RenderTarget& target, sf::RenderStates states)
        const override;
};

#endif  // _HOME_JGCHARLOT615_COMPIV_PS2_TRIANGLE_HPP_
