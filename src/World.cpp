//
// Created by david on 11/1/2025.
//

#include "World.hpp"
#include <iostream>

World::World(sf::RenderWindow &window)
    : m_window(window), m_enemy({400.f, 500.f}, {50.f, 50.f}) {
    m_ground.setSize({3000.f, 50.f});
    m_ground.setFillColor(sf::Color(100, 60, 30));
    m_ground.setPosition({0.f, 550.f});
}

void World::update(const sf::Time dt) {
    m_player.update(dt);
    m_enemy.update(dt);
    handleCollisions();
}

void World::draw() const {
    m_window.draw(m_ground);
    m_player.draw(m_window);
    m_enemy.draw(m_window);
}

void World::handleCollisions() {
    // player - ground
    sf::FloatRect playerBounds = m_player.getPlayerBounds();

    if (const sf::FloatRect groundBounds = m_ground.getGlobalBounds(); groundBounds.findIntersection(playerBounds)) {
        // put player back on top
        m_player.setPlayerPosition({
            playerBounds.position.x, groundBounds.position.y - m_player.getPlayerDimensions().size.y
        });
        m_player.setOnGround(true);
        m_player.setVelocityY(0.f);
    } else {
        m_player.setOnGround(false);
    }

    //player - enemy
    if (const sf::FloatRect enemyBounds = m_enemy.getEnemyBounds(); playerBounds.findIntersection(enemyBounds)) {
        // simple reaction: reset player position
        m_player.setPlayerPosition({100.f, 100.f});
        m_player.setVelocityY(0.f);
        std::cout<<"x"<<'\n';

    }
}
