//
// Created by david on 11/1/2025.
//
#include <iostream>
#include <algorithm>
#include "World.hpp"

World::World(sf::RenderWindow &window)
    : m_window(window) {
    // Create player
    auto player = std::make_unique<Player>();
    m_entities.push_back(std::make_unique<Player>());
    m_player = static_cast<Player *>(m_entities.back().get()); // We keep a raw pointer to access Player faster

    // Create an enemy
    auto enemy = std::make_unique<Enemy>(sf::Vector2f{400.f, 500.f}, sf::Vector2f{50.f, 50.f});
    m_entities.push_back(std::move(enemy));

    // Being unique pointers, enemy and player will be automatically deleted after the constructor is finished
    // Their ownership is moved to the entities list

    m_ground.setSize({3000.f, 50.f});
    m_ground.setFillColor(sf::Color(100, 60, 30));
    m_ground.setPosition({-500.f, 550.f});
}

void World::update(const sf::Time dt)  {
    for (const auto &e: m_entities)
        (*e).update(dt); // I prefer this syntax to better visualize variable type
    // It uses its own specific update func (the one with override)

    handleCollisions();
}

void World::draw() const {
    m_window.draw(m_ground);

    for (const auto &e: m_entities)
        (*e).draw(m_window);
}

void World::handleCollisions() {
    if (!m_player)
        return;

    const sf::FloatRect playerBounds = (*m_player).getBounds();

    // player - ground
    if (const sf::FloatRect groundBounds = m_ground.getGlobalBounds(); groundBounds.findIntersection(playerBounds)) {
        // Move player on top of ground
        (*m_player).setPosition({
            playerBounds.position.x, groundBounds.position.y - (*m_player).getPlayerDimensions().size.y
        });
        (*m_player).setOnGround(true);
        (*m_player).setVelocityY(0.f);
    } else {
        (*m_player).setOnGround(false);
    }

    for (auto &e: m_entities) {
        if (e.get() == m_player)
            continue;

        const sf::FloatRect enemyBounds = (*e).getBounds();
        if (playerBounds.findIntersection(enemyBounds)) {
            // simple reaction: reset player position
            (*m_player).setPosition({100.f, 100.f});
            (*m_player).setVelocityY(0.f);
        }
    }
}

sf::Vector2f World::getPlayerPosition() const {
    if (!m_player)
        return sf::Vector2f{0.f, 0.f};
    else {
        return (*m_player).getPosition();
    }
}
