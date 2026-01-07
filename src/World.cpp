//
// Created by david on 11/1/2025.
//
#include <algorithm>
#include "World.hpp"

World::World(sf::RenderWindow &window) : m_window(window),
                                         m_playerStandingTexture("../resources/sprites/aeris_standing_animation_spritesheet.png"),
                                         m_playerWalkingTexture("../resources/sprites/aeris_walking_animation_spritesheet.png"),
                                         m_playerAttackingTexture("../resources/sprites/aeris_attacking_animation_spritesheet4.png"){
    // Create player
    m_entities.push_back(std::make_unique<Player>(m_playerStandingTexture.get(), m_playerWalkingTexture.get(), m_playerAttackingTexture.get()));
    m_player = dynamic_cast<Player *>(m_entities.back().get()); // We keep a raw pointer to access Player faster

    // Create an enemy
    auto enemy = std::make_unique<Enemy>(sf::Vector2f{400.f, 500.f}, sf::Vector2f{50.f, 50.f});
    m_entities.push_back(std::move(enemy));

    // Being unique pointers, enemy and player will be automatically deleted after the constructor is finished
    // Their ownership is moved to the entities list

    m_ground.setSize({3000.f, 50.f});
    m_ground.setFillColor(sf::Color(100, 60, 30));
    m_ground.setPosition({-500.f, 550.f});

    // Code=2
    addNotes();
}

void World::update(const sf::Time dt, const InputState &inputState) {
    for (const auto &e: m_entities)
        (*e).update(dt);
    // It uses its own specific update func (the one with override)

    if (m_player)
        (*m_player).setInputState(inputState);

    handleCollisions();
}

void World::handleCollisions() {
    sf::FloatRect playerBounds = (*m_player).getBounds();

    // passed through reference to avoid creating+deleting chunks of memory repeatedly
    collision_player_ground(playerBounds);
    collision_player_enemies(playerBounds);
    collision_player_notes(playerBounds);
}

void World::collision_player_ground(sf::FloatRect &playerBounds) {
    if (!m_player)
        return;

    if (const sf::FloatRect groundBounds = m_ground.getGlobalBounds(); groundBounds.findIntersection(playerBounds)) {
        // Move player on top of ground
        (*m_player).setPosition({
            playerBounds.position.x, groundBounds.position.y - (*m_player).getPlayerDimensions().size.y
        });
        (*m_player).setOnGround(true);
        (*m_player).setVelocity({(*m_player).getVelocity().x, 0.f});
        (*m_player).resetDash();
    } else {
        (*m_player).setOnGround(false);
    }
}

void World::collision_player_enemies(const sf::FloatRect &playerBounds) {
    if (!m_player)
        return;

    for (auto &e: m_entities) {
        if (e.get() == m_player)
            continue;

        const sf::FloatRect enemyBounds = (*e).getBounds();
        if (playerBounds.findIntersection(enemyBounds)) {
            // simple reaction: reset player position
            (*m_player).setPosition({100.f, 100.f});
            (*m_player).setVelocity({(*m_player).getVelocity().x, 0.f});
        }
    }

    // Hit logic implementation
    if ((*m_player).getAttackingState() == true) {
        for (auto &e: m_entities) {
            if (e.get() == m_player)
                continue;

            const sf::FloatRect enemyBounds = (*e).getBounds();
            if ((*m_player).getAttackingBounds().findIntersection(enemyBounds)) {
                // simple reaction: add a filter to the enemy
                //TODO manage enemy default color so it doesn't stay purple forever (using a Clock)
                if (auto *enemy = dynamic_cast<Enemy *>(e.get())) {
                    (*enemy).setColor(sf::Color(255, 120, 255, 255));
                }
            }
        }
    }
}

void World::collision_player_notes(const sf::FloatRect &playerBounds) {
    if (!m_player)
        return;

    // Remove the notes which the player intersects
    std::erase_if(
        m_notes,
        [&](const std::unique_ptr<Note> &n) {
            const sf::FloatRect noteBounds = (*n).getBounds();
            return playerBounds.findIntersection(noteBounds).has_value();
        });
}

// Helper func for the attack logic in the Game class
void World::playerAttack() {
    (*m_player).attack();
}

// Helper func for the camera logic in the Game class
sf::Vector2f World::getPlayerPosition() const {
    if (!m_player)
        return sf::Vector2f{0.f, 0.f};
    return (*m_player).getPosition();
}

void World::draw() const {
    m_window.draw(m_ground);

    // Draw all entities
    for (const auto &e: m_entities)
        (*e).draw(m_window);

    // Draw all notes
    // Code=2
    for (const auto &n: m_notes)
        (*n).draw(m_window);
}

// Code=2
void World::addNotes() {
    for (auto &pos: positions)
        m_notes.push_back(std::make_unique<Note>(pos));
}
//
// std::ostream &operator<<(std::ostream &os, const World &w) {
//     os << "World:\n";
//     os << " Player -> " << *w.m_player << "\n";
//     for (const auto &e: w.m_entities)
//         if (e.get() != w.m_player)
//             os << " Enemy -> " << *e << "\n";
//     return os;
// }
