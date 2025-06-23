// Copyright 2025 William Nosike

#include <iostream>
#include <fstream>
#include <cmath>
#include <ctime>
#include <cstdlib>
#include "Universe.hpp"
#include <SFML/Graphics.hpp>

int main() {
    // Read universe data from planets.txt
    NB::Universe universe("planets.txt");

    // Create an SFML window
    sf::RenderWindow window(sf::VideoMode(800, 800), "The Solar System!");
    window.setFramerateLimit(60);

    // Compute a scale factor to fit the universe radius into 800x800
    double scaleFactor = (universe.getRadius() != 0.0) ? (400.0 / universe.getRadius()) : 1.0;

// Create a basic starfield background
sf::Texture backgroundTexture;
sf::Image bgImage;
bgImage.create(800, 800, sf::Color::Black);  // Pure black background

// Add simple white stars
std::srand(static_cast<unsigned int>(std::time(nullptr)));
for (int i = 0; i < 500; ++i) {
    int x = std::rand() % 800;
    int y = std::rand() % 800;
    bgImage.setPixel(x, y, sf::Color::White);
}

backgroundTexture.loadFromImage(bgImage);


    backgroundTexture.update(bgImage);
    sf::Sprite backgroundSprite(backgroundTexture);

    // Scale each CelestialBody's position
    for (auto& body : universe.getBodies()) {
        body.setScaledPosition(scaleFactor, 800.0f);
    }

    // Main event/render loop
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }

        window.clear(sf::Color::Black);

        window.draw(backgroundSprite);

        window.draw(universe);
        window.display();
    }

    return 0;
}
