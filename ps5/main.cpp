// Copyright 2025 <Jordan Charlot>
#include "EDistance.hpp"
#include <SFML/System.hpp>


int main() {
    std::string x, y;

    // Read input strings
    std::getline(std::cin, x);
    std::getline(std::cin, y);

    // Remove carriage returns if present (for Windows line endings)
    x.erase(std::remove(x.begin(), x.end(), '\r'), x.end());
    y.erase(std::remove(y.begin(), y.end(), '\r'), y.end());

    sf::Clock clock;

    // Compute edit distance and alignment
    EDistance ed(x, y);
    int distance = ed.optDistance();
    std::string align = ed.alignment();

    sf::Time t = clock.getElapsedTime();

    // Output results
    std::cout << "Edit distance = " << distance << "\n";
    std::cout << align;
    std::cout << "Execution time is " << t.asSeconds() << " seconds\n";

    return 0;
}
