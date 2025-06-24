// Copyright 2025 William Nosike
#include "Sokoban.hpp"
#include <fstream>
#include <iostream>

namespace SB {


void Sokoban::loadTextures() {
    // Load textures from files
    if (!m_wallTexture.loadFromFile("sokoban/block_06.png") ||
        !m_emptyTexture.loadFromFile("sokoban/ground_01.png") ||
        !m_boxTexture.loadFromFile("sokoban/crate_03.png") ||
        !m_storageTexture.loadFromFile("sokoban/ground_04.png") ||
        !m_boxStorageTexture.loadFromFile("sokoban/crate_03.png") ||
        !m_playerTexture.loadFromFile("sokoban/player_05.png")) {
        throw std::runtime_error("Failed to load texture files");
    }

    // Set textures to sprites
    m_wallSprite.setTexture(m_wallTexture);
    m_emptySprite.setTexture(m_emptyTexture);
    m_boxSprite.setTexture(m_boxTexture);
    m_storageSprite.setTexture(m_storageTexture);
    m_boxStorageSprite.setTexture(m_boxStorageTexture);
    m_playerSprite.setTexture(m_playerTexture);
}

// Gets cell type at (x,y) using 1D array
CellType Sokoban::getCell(unsigned int x, unsigned int y) const {
    return m_grid[x + y * m_width];
}

// Sets cell type at (x,y) using 1D array
void Sokoban::setCell(unsigned int x, unsigned int y, CellType type) {
    m_grid[x + y * m_width] = type;
}

Sokoban::Sokoban() : m_playerPosition(0, 0) {
    loadTextures();
}

Sokoban::Sokoban(const std::string& filename) : m_playerPosition(0, 0) {
    loadTextures();
    std::ifstream file(filename);
    file >> *this;
}


unsigned int Sokoban::pixelHeight() const {
    return height() * TILE_SIZE;
}

unsigned int Sokoban::pixelWidth() const {
    return width() * TILE_SIZE;
}

unsigned int Sokoban::height() const {
    return m_height;
}

unsigned int Sokoban::width() const {
    return m_width;
}

sf::Vector2u Sokoban::playerLoc() const {
    return m_playerPosition;
}

// Checks if level is won (all boxes on storage)
bool Sokoban::isWon() const {
    int boxOnStorage = 0;
    int totalBoxes = 0;
    int totalStorages = 0;

    // Count each cell type
    for (CellType c : m_grid) {
        if (c == CellType::Box) {
            ++totalBoxes;
        } else if (c == CellType::BoxStorage) {
            ++boxOnStorage;
            ++totalBoxes;  // Count both box and storage
            ++totalStorages;
        } else if (c == CellType::Storage) {
            ++totalStorages;
        }
    }

    return boxOnStorage > 0 && (totalBoxes == boxOnStorage);
}

// Moves player in specified direction, handling box pushing
void Sokoban::movePlayer(Direction dir) {
    // Get current position
    unsigned int x = m_playerPosition.x;
    unsigned int y = m_playerPosition.y;

    // Calculate direction deltas
    int dx = 0, dy = 0;
    switch (dir) {
        case Direction::Up:    dy = -1; break;
        case Direction::Down:  dy = 1;  break;
        case Direction::Left:  dx = -1; break;
        case Direction::Right: dx = 1;  break;
    }

    // Calculate new position
    int nx = x + dx;
    int ny = y + dy;

    // Check bounds
    if (nx < 0 || nx >= static_cast<int>(m_width) ||
        ny < 0 || ny >= static_cast<int>(m_height)) {
        return;
    }

    // Check destination cell
    CellType targetCell = getCell(nx, ny);

    if (targetCell == CellType::Empty || targetCell == CellType::Storage) {
        // Move to empty space or storage
        m_playerPosition.x = nx;
        m_playerPosition.y = ny;
    } else if (targetCell == CellType::Box || targetCell == CellType::BoxStorage) {
        // Try to push box
        int boxNewX = nx + dx;
        int boxNewY = ny + dy;

        // Check if box push is valid
        if (boxNewX >= 0 && boxNewX < static_cast<int>(m_width) &&
            boxNewY >= 0 && boxNewY < static_cast<int>(m_height)) {
            CellType boxTarget = getCell(boxNewX, boxNewY);

            if (boxTarget == CellType::Empty || boxTarget == CellType::Storage) {
                // Handle box movement
                bool boxWasOnStorage = (targetCell == CellType::BoxStorage);
                bool boxGoesToStorage = (boxTarget == CellType::Storage);

                // Update box and player positions
                setCell(boxNewX, boxNewY, boxGoesToStorage ? CellType::BoxStorage : CellType::Box);
                setCell(nx, ny, boxWasOnStorage ? CellType::Storage : CellType::Empty);
                m_playerPosition.x = nx;
                m_playerPosition.y = ny;
            }
        }
    }
}

// Resets level to initial state
void Sokoban::reset() {
    m_grid = m_originalGrid;
    m_playerPosition = m_originalPlayerPosition;
}

// Renders the Sokoban grid to the screen
void Sokoban::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    auto drawAt = [&](const sf::Sprite& spr, sf::Vector2f pos) {
        sf::Sprite sprite = spr;
        sprite.setPosition(pos);
        target.draw(sprite, states);
    };

    // Draw each cell
    for (unsigned int y = 0; y < m_height; ++y) {
        for (unsigned int x = 0; x < m_width; ++x) {
            sf::Vector2f pos(x * TILE_SIZE, y * TILE_SIZE);

            // Draw floor first
            drawAt(m_emptySprite, pos);

            // Draw cell contents
            auto cell = getCell(x, y);
            if (cell == CellType::Wall) {
                drawAt(m_wallSprite, pos);
            } else if (cell == CellType::Box) {
                drawAt(m_boxSprite, pos);
            } else if (cell == CellType::Storage) {
                drawAt(m_storageSprite, pos);
            } else if (cell == CellType::BoxStorage) {
                drawAt(m_storageSprite, pos);
                drawAt(m_boxSprite, pos);
            }

            // Draw player on top
            if (m_playerPosition == sf::Vector2u(x, y)) {
                drawAt(m_playerSprite, pos);
            }
        }
    }
}

// Outputs level as text to stream
std::ostream& operator<<(std::ostream& out, const Sokoban& s) {
    // Write dimensions
    out << s.height() << " " << s.width() << std::endl;

    // Write grid
    for (unsigned int y = 0; y < s.height(); ++y) {
        for (unsigned int x = 0; x < s.width(); ++x) {
            CellType cellType = s.getCell(x, y);
            char symbol;

            // Player gets priority in display
            if (s.playerLoc().x == x && s.playerLoc().y == y) {
                symbol = '@';
            } else {
                // Map cells to symbols
                switch (cellType) {
                    case CellType::Empty: symbol = '.'; break;
                    case CellType::Wall: symbol = '#'; break;
                    case CellType::Box: symbol = 'A'; break;
                    case CellType::Storage: symbol = 'a'; break;
                    case CellType::BoxStorage: symbol = '1'; break;
                    default: symbol = '.';
                }
            }
            out << symbol;
        }
        out << std::endl;
    }

    return out;
}

// Loads level from stream
std::istream& operator>>(std::istream& in, Sokoban& s) {
    unsigned int height, width;
    in >> height >> width;
    in.ignore();  // Skip newline

    // Check dimensions
    if (!in || height == 0 || width == 0 || height > 100 || width > 100) {
        throw std::runtime_error("Invalid level format or dimensions");
    }

    // Setup grid
    s.m_height = height;
    s.m_width = width;
    s.m_grid.clear();
    s.m_grid.resize(width * height, CellType::Empty);
    sf::Vector2u playerPos(0, 0);
    bool playerFound = false;

    // Read grid data
    for (unsigned int y = 0; y < height; ++y) {
        std::string line;
        std::getline(in, line);
        if (!line.empty() && line.back() == '\r') {
            line.pop_back();  // Handle CRLF
        }

        for (unsigned int x = 0; x < width && x < line.length(); ++x) {
            char symbol = line[x];

            // Parse level symbols
            switch (symbol) {
                case '.': s.setCell(x, y, CellType::Empty); break;
                case '#': s.setCell(x, y, CellType::Wall); break;
                case 'A': s.setCell(x, y, CellType::Box); break;
                case 'a': s.setCell(x, y, CellType::Storage); break;
                case '1': s.setCell(x, y, CellType::BoxStorage); break;
                case '@':  // Player
                    s.setCell(x, y, CellType::Empty);
                    playerPos = sf::Vector2u(x, y);
                    playerFound = true;
                    break;
                case '+':  // Player on storage
                    s.setCell(x, y, CellType::Storage);
                    playerPos = sf::Vector2u(x, y);
                    playerFound = true;
                    break;
                default: s.setCell(x, y, CellType::Empty);
            }
        }
    }

    // Set player position
    if (playerFound) {
        s.m_playerPosition = playerPos;
    } else {
        throw std::runtime_error("No player found in level file");
    }

    // Store original state for reset
    s.m_originalGrid = s.m_grid;
    s.m_originalPlayerPosition = s.m_playerPosition;

    return in;
}

}  // namespace SB

