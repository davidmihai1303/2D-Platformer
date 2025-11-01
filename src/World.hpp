//
// Created by david on 11/1/2025.
//

#ifndef SOUNDFUGUE_WORLD_HPP
#define SOUNDFUGUE_WORLD_HPP
#include <SFML/Graphics.hpp>
#include "Player.hpp"

class World {
public:
    explicit World(sf::RenderWindow &window);

    void update(sf::Time dt);

    void draw();

private:
    void handleCollisions();

    sf::RenderWindow &m_window;
    Player m_player;
    sf::RectangleShape m_ground;
};

#endif //SOUNDFUGUE_WORLD_HPP
