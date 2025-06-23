// Copyright 2025 William Nosike
#include <string>
#include <iostream>
#include <SFML/Graphics.hpp>
#include "Sokoban.hpp"

int main(int argc, char* argv[]) {
    std::string levelFile = "level1.lvl";
    SB::Sokoban sokoban(levelFile);

    // Create window with the appropriate size
    sf::RenderWindow window(sf::VideoMode(sokoban.pixelWidth(), sokoban.pixelHeight()),
        "Sokoban - " + levelFile);

    // Main game loop
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }

            // Keyboard controls
            if (event.type == sf::Event::KeyPressed) {
                switch (event.key.code) {
                    case sf::Keyboard::Up:
                        sokoban.movePlayer(SB::Direction::Up);
                        break;
                    case sf::Keyboard::Down:
                        sokoban.movePlayer(SB::Direction::Down);
                        break;
                    case sf::Keyboard::Left:
                        sokoban.movePlayer(SB::Direction::Left);
                        break;
                    case sf::Keyboard::Right:
                        sokoban.movePlayer(SB::Direction::Right);
                        break;
                    case sf::Keyboard::R:
                        sokoban.reset();
                        break;
                    case sf::Keyboard::Escape:
                        window.close();
                        break;
                    default:
                        break;
                }
            }
        }

        // Check win condition
        if (sokoban.isWon()) {
            std::cout << "Level completed!" << std::endl;
        }

        // Clear, draw, and display
        window.clear(sf::Color::Black);
        window.draw(sokoban);
        window.display();
    }

    return 0;
}
