//
// Created by david on 11/1/2025.
//

#ifndef SOUNDFUGUE_WORLD_HPP
#define SOUNDFUGUE_WORLD_HPP
#include <SFML/Graphics.hpp>
#include "Player.hpp"
#include "Enemy.hpp"

class World {
public:
    explicit World(sf::RenderWindow &window);

    void update(sf::Time dt);

    void draw() const;

private:
    void handleCollisions();

    sf::RenderWindow &m_window;
    sf::RectangleShape m_ground;
    Player m_player;
    Enemy m_enemy;
};

#endif //SOUNDFUGUE_WORLD_HPP
