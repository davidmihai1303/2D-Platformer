//
// Created by david on 11/1/2025.
//

#ifndef SOUNDFUGUE_WORLD_HPP
#define SOUNDFUGUE_WORLD_HPP
#include <SFML/Graphics.hpp>
#include <vector>
#include "Player.hpp"
#include "Enemy.hpp"
#include "Entity.hpp"

class World {
public:
    explicit World(sf::RenderWindow &window);

    void update(sf::Time dt);

    void draw() const;

    sf::Vector2f getPlayerPosition() const;

private:
    void handleCollisions();

    sf::RenderWindow &m_window;

    sf::RectangleShape m_ground;

    std::vector<std::unique_ptr<Entity>> m_entities;

    Player* m_player = nullptr;
};

#endif //SOUNDFUGUE_WORLD_HPP
