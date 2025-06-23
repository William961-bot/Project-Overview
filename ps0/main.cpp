// Copyright 2025 William Nosike
#include <SFML/Graphics.hpp>

int main() {
    sf::RenderWindow window(sf::VideoMode(800, 600), "SFML window");
    window.setFramerateLimit(60);

    // Load sprite texture
    sf::Texture texture;
    if (!texture.loadFromFile("sprite.png")) return EXIT_FAILURE;
    sf::Sprite sprite(texture);
    sprite.setScale(0.5f, 0.5f);
    sf::Vector2f initialPosition = sprite.getPosition();

    // Load door texture
    sf::Texture doorTexture;
    if (!doorTexture.loadFromFile("door.png")) return EXIT_FAILURE;
    sf::Sprite door(doorTexture);
    door.setScale(0.5f, 0.5f);
    door.setPosition(sprite.getPosition().x + 700.f, sprite.getPosition().y);

    // Game state variables
    bool doorExists = true, enemySpawned = false, moving = false;
    float health = 100.f;
    sf::Clock spawnClock;

    // Load enemy texture
    sf::Texture enemyTexture;
    if (!enemyTexture.loadFromFile("enemy.png")) return EXIT_FAILURE;
    sf::Sprite enemy(enemyTexture);

    while (window.isOpen()) {
        // Event handling
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) window.close();
        }

        moving = false;  // Reset moving flag

        // Sprite movement
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) && sprite.getPosition().x > 0) {
            sprite.move(-5, 0); moving = true;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
            sprite.move(5, 0); moving = true;
        }
        if (!doorExists) {
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
                sprite.move(0, -5); moving = true;
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
                sprite.move(0, 5); moving = true;
            }
        }

        // Door collision and enemy spawning
        if (sprite.getGlobalBounds().intersects(door.getGlobalBounds()) && doorExists) {
            sprite.setPosition(initialPosition);
            doorExists = false;
            spawnClock.restart();
        }
        if (!enemySpawned && !doorExists && spawnClock.getElapsedTime().asSeconds() > 3.f) {
            enemy.setPosition(500.f, 400.f);
            enemySpawned = true;
        }

        // Health reduction logic
        if (enemySpawned && moving) health = std::max(0.f, health - 0.5f);
        if (enemySpawned && sprite.getGlobalBounds().intersects(enemy.getGlobalBounds())) {
            health = std::max(0.f, health - 5.f);
        }

        // Drawing for sprite,enemy and door
        window.clear();
        window.draw(sprite);
        if (enemySpawned) window.draw(enemy);
        if (doorExists) window.draw(door);

        // Health Drawing
        sf::RectangleShape healthBar(sf::Vector2f(health * 2.f, 20.f));
        healthBar.setFillColor(sf::Color::Red);
        healthBar.setPosition(10.f, window.getSize().y - 40.f);
        window.draw(healthBar);

        window.display();
    }

    return EXIT_SUCCESS;
}
