// Copyright 2025 William Nosike
#include <string>
#include <iostream>
#include <fstream>
#include <SFML/Graphics.hpp>
#include "Sokoban.hpp"

int main(int argc, char* argv[]) {
    // Default level or use command line argument
    std::string levelFile = (argc > 1) ? argv[1] : "level1.lvl";

    // Add sokoban/ prefix if needed
    if (levelFile.find("sokoban/") != 0) {
        // Check if the file exists as-is
        std::ifstream testFile(levelFile);
        if (!testFile.good()) {
            // Try with prefix
            std::string withPrefix = "sokoban/" + levelFile;
            std::ifstream prefixedFile(withPrefix);
            if (prefixedFile.good()) {
                levelFile = withPrefix;
            }
        }
    }

    try {
        SB::Sokoban sokoban(levelFile);

        // Create window with the appropriate size
        sf::RenderWindow window(sf::VideoMode(sokoban.pixelWidth(), sokoban.pixelHeight()),
            "Sokoban - " + levelFile);

        // Load the win image from file
        sf::Texture winTexture;
        if (!winTexture.loadFromFile("/home/william/ps4b/you win.png")) {
            std::cerr << "Error: Could not load 'you win.png' file." << std::endl;
        }

        // Create sprite from the win texture and scale it down to 50% of original size
        sf::Sprite winSprite(winTexture);
        winSprite.setScale(0.3f, 0.3f);  // Make it even smaller - 30% of original size

        // Track win state
        bool levelWon = false;

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
                        case sf::Keyboard::W:
                            sokoban.movePlayer(SB::Direction::Up);
                            break;
                        case sf::Keyboard::Down:
                        case sf::Keyboard::S:
                            sokoban.movePlayer(SB::Direction::Down);
                            break;
                        case sf::Keyboard::Left:
                        case sf::Keyboard::A:
                            sokoban.movePlayer(SB::Direction::Left);
                            break;
                        case sf::Keyboard::Right:
                        case sf::Keyboard::D:
                            sokoban.movePlayer(SB::Direction::Right);
                            break;
                        case sf::Keyboard::R:
                            sokoban.reset();
                            levelWon = false;  // Reset win announcement when level resets
                            break;
                        case sf::Keyboard::Escape:
                            window.close();
                            break;
                        default:
                            break;
                    }
                }
            }

            // Check win condition - only print once when the level is first won
            if (sokoban.isWon() && !levelWon) {
                std::cout << "You win!" << std::endl;
                levelWon = true;
            }

            // Clear, draw, and display
            window.clear(sf::Color::Black);
            window.draw(sokoban);

            // Display win overlay if game is won
            if (sokoban.isWon()) {
                // Semi-transparent overlay
                sf::RectangleShape overlay;
                overlay.setSize(sf::Vector2f(sokoban.pixelWidth(), sokoban.pixelHeight()));
                overlay.setFillColor(sf::Color(0, 0, 0, 150));  // Semi-transparent black

                // Position the win sprite in the center of the window
                winSprite.setOrigin(winSprite.getLocalBounds().width / 2,
                                   winSprite.getLocalBounds().height / 2);
                winSprite.setPosition(sokoban.pixelWidth() / 2, sokoban.pixelHeight() / 2);

                // Draw overlay and win sprite
                window.draw(overlay);
                window.draw(winSprite);
            }

            window.display();
        }
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }

    return 0;
}
