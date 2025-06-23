// Copyright 2025 <Jordan Charlot,William Nosike>

#include <cstdlib>
#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include "triangle.hpp"

int main(int argc, char* argv[]) {
    if (argc < 3 || argc > 4) {
        std::cerr << "Usage: " << argv[0]
                  << " <side length> <recursion depth> [rotation]" << std::endl;
        return 1;
    }

    double length = std::atof(argv[1]);
    int depth = std::atoi(argv[2]);
    float rotation = (argc == 4) ? std::atof(argv[3]) : 0.0f;

    sf::RenderWindow window(sf::VideoMode(800, 800), "Triangle Fractal");
    TriangleFractal fractal(length, depth, rotation);

    sf::Clock clock;
    bool animate = true;

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
            if (event.type == sf::Event::KeyPressed &&
                event.key.code == sf::Keyboard::Space) {
                animate = !animate;  // Toggle animation with spacebar
            }
        }

        if (animate) {
            float deltaTime = clock.restart().asSeconds();
            fractal.updateRotation(30.0f * deltaTime);
        }

        window.clear();
        window.draw(fractal);
        window.display();
    }

    return 0;
}
