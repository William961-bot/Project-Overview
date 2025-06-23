// Copyright 2025 William Nosike


#include <fstream>
#include <iostream>
#include <memory>

#include <SFML/Graphics.hpp>

#include "Universe.hpp"

int main(int argc, char* argv[]) {
    double T = 1000000.0;  // default simulation time (in seconds)
    double dt = 25000.0;  // default time step (in seconds)

    if (argc >= 2) {
        T = std::stod(argv[1]);
    }
    if (argc >= 3) {
        dt = std::stod(argv[2]);
    }

    // Read universe data from planets.txt
    auto universe = std::make_unique<NB::Universe>("planets.txt");

    // Create an SFML window
    sf::RenderWindow window(sf::VideoMode(800, 800), "The Solar System!");
    window.setFramerateLimit(60);

    // Compute a scale factor to fit the universe radius into 800x800
    double scaleFactor = (universe->getRadius() != 0.0) ? (400.0 / universe->getRadius()): 1.0;

    // Scale each CelestialBody's position
    for (auto& body : universe->getBodies()) {
        body->setScaledPosition(scaleFactor, 800.0f);
    }


    double timeElapsed = 0.0;
    bool simulationComplete = false;

    sf::Clock clock;

    // Main event/render loop
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }

        // Run simulation step if not complete
        if (!simulationComplete && timeElapsed < T) {
            universe->step(dt);
            timeElapsed += dt;

            // Check if simulation is complete
            if (timeElapsed >= T) {
                simulationComplete = true;
                // Print the final state of the universe
                std::cout << *universe << std::endl;
            }
        }
        // Render the universe
        window.clear(sf::Color::Black);
        window.draw(*universe);
        window.display();
    }

    return 0;
}
