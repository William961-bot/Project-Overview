// Copyright 2025 William Nosike
#include <iostream>
#include <string>
#include "PhotoMagic.hpp"
#include <SFML/Graphics.hpp>

int main(int argc, char* argv[]) {
    // Checks for proper command-line arguments.
    if (argc != 4) {
    std::cerr << "Usage: " << argv[0] << " <input-file.png> <output-file.png> <seed>" << std::endl;
        return -1;
    }
    // Extracts command-line arguments.
    std::string inputFile  = argv[1];
    std::string outputFile = argv[2];
    std::string seed       = argv[3];
    // Loads the source image.
    sf::Image image;
    if (!image.loadFromFile(inputFile)) {
std::cerr << "Error: Could not load image" << inputFile << "!" << std::endl; return -1; }
    // Initialize the FibLFSR with the provided seed and transform the image.
PhotoMagic::FibLFSR lfsr(seed);
    PhotoMagic::transform(image, &lfsr);
    // Determines the window title based on the output filename.
std::string windowTitle;
if(outputFile.find("decrypt") != std::string::npos) {
        windowTitle = "Decrypted Image";
} else if (outputFile.find("encrypt") != std::string::npos) {
        windowTitle = "Encrypted Image";
    } else {
        windowTitle = "Encrypted Image";
    }

    // Creates an SFML window to display the transformed image.
    sf::Vector2u size = image.getSize();
    sf::RenderWindow window(sf::VideoMode(size.x, size.y), windowTitle);
    // Creates a texture and sprite for the image.
sf::Texture texture;
    if (!texture.loadFromImage(image)) {
        std::cerr << "Error: Could not create texture from image!" << std::endl;
        return -1;
    }
    sf::Sprite sprite;
sprite.setTexture(texture);
    // Main event loop.
while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }
        window.clear(sf::Color::White);
        window.draw(sprite);
        window.display();
    }
    // Saves the transformed image.
if (!image.saveToFile(outputFile)) {
        std::cerr << "Error: Could not save image to '" << outputFile << "'!" << std::endl;
        return -1;
    }
return 0;
}
