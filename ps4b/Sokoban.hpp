// Copyright 2025 William Nosike
#pragma once

#include <iostream>
#include <memory>
#include <vector>
#include <SFML/Graphics.hpp>

namespace SB {

enum class Direction {
    Up, Down, Left, Right
};

enum class CellType {
    Empty,
    Wall,
    Box,
    Storage,
    BoxStorage
};

class Sokoban : public sf::Drawable {
 public:
    static const int TILE_SIZE = 64;

    Sokoban();
    explicit Sokoban(const std::string& filename);
    ~Sokoban() = default;

    unsigned int pixelHeight() const;
    unsigned int pixelWidth() const;

    unsigned int height() const;
    unsigned int width() const;

    sf::Vector2u playerLoc() const;
    bool isWon() const;

    void movePlayer(Direction dir);
    void reset();

    friend std::ostream& operator<<(std::ostream& out, const Sokoban& s);
    friend std::istream& operator>>(std::istream& in, Sokoban& s);

 protected:
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

 private:
    unsigned int m_width = 0;
    unsigned int m_height = 0;
    sf::Vector2u m_playerPosition;
    std::vector<CellType> m_grid;

    // For reset functionality
    std::vector<CellType> m_originalGrid;
    sf::Vector2u m_originalPlayerPosition;

    // Textures and sprites
    sf::Texture m_wallTexture;
    sf::Texture m_emptyTexture;
    sf::Texture m_boxTexture;
    sf::Texture m_storageTexture;
    sf::Texture m_boxStorageTexture;
    sf::Texture m_playerTexture;

    sf::Sprite m_wallSprite;
    sf::Sprite m_emptySprite;
    sf::Sprite m_boxSprite;
    sf::Sprite m_storageSprite;
    sf::Sprite m_boxStorageSprite;
    sf::Sprite m_playerSprite;

    void loadTextures();
    CellType getCell(unsigned int x, unsigned int y) const;
    void setCell(unsigned int x, unsigned int y, CellType type);
};

std::ostream& operator<<(std::ostream& out, const Sokoban& s);
std::istream& operator>>(std::istream& in, Sokoban& s);

}  // namespace SB

