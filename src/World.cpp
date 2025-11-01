//
// Created by david on 11/1/2025.
//

#include "World.hpp"
#include <iostream>
World::World(sf::RenderWindow &window)
    : m_window(window) {
    m_ground.setSize({800.f, 50.f});
    m_ground.setFillColor(sf::Color(100, 60, 30));
    m_ground.setPosition({0.f, 550.f});
}

void World::update(sf::Time dt) {
    m_player.update(dt);
    handleCollisions();
}

void World::draw() {
    m_window.draw(m_ground);
    m_player.draw(m_window);
}

void World::handleCollisions() {
    // Very simple example: stop player from falling below ground
    sf::FloatRect playerBounds = m_player.getPlayerBounds();
    sf::FloatRect groundBounds = m_ground.getGlobalBounds();

    if (groundBounds.findIntersection(playerBounds)) {
        // put player back on top
        m_player.setPlayerPosition({playerBounds.position.x, groundBounds.position.y - m_player.getPlayerDimensions().size.y});
    }
}
