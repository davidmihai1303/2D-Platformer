//
// Created by david on 10/31/2025.
//

#include "Player.hpp"

Player::Player() {
    m_shape.setSize(sf::Vector2f({50.f, 100.f}));
    m_shape.setFillColor(sf::Color::Green);
    m_shape.setPosition({0.f, 450.f});
}

void Player::update(const sf::Time dt) {
    constexpr float moveSpeed = 350.f;
    constexpr float gravity = 2000.f;

    // Left-Right movement
    sf::Vector2f movement(0.f, 0.f);
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scan::A)) movement.x -= moveSpeed;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scan::D)) movement.x += moveSpeed;

    // Jumping logic and gravity
    if (m_onGround && sf::Keyboard::isKeyPressed(sf::Keyboard::Scan::Space)) {
        constexpr float jumpStrength = 550.f;
        m_velocity.y = -jumpStrength;
        m_onGround = false;
    }
    m_velocity.y += gravity * dt.asSeconds();

    // Running Logic
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scan::LShift) ||
        sf::Keyboard::isKeyPressed(sf::Keyboard::Scan::RShift))
        movement.x *= 1.71f; //TODO not sure of the value

    // Move horizontally and vertically
    m_shape.move((movement + m_velocity) * dt.asSeconds());

    // Reset the attack cooldown
    if (m_cooldownAttackClock.getElapsedTime() >= m_cooldownAttackTime)
        m_cooldownAttackClock.reset();

    // Reset the active attack
    if (m_activeAttackClock.getElapsedTime() >= m_activeAttackTime) {
        m_activeAttackClock.reset();
        m_isAttacking = false;
    }

    // Code=1
    // Draw a rectangle representing the hitbox of the Hit-Area
    attackingShape.setSize(sf::Vector2f({40.f, 65.f}));
    attackingShape.setFillColor(sf::Color::Blue);
    attackingShape.setPosition(m_shape.getPosition() + sf::Vector2f(m_shape.getSize().x, 0.f));

    // To have access to the player's position at all times without auxiliary func
    m_position = m_shape.getPosition();
}

void Player::draw(sf::RenderTarget &target) const {
    target.draw(m_shape);
    // Code=1
        if (m_isAttacking) {
            target.draw(attackingShape);
        }
}

sf::FloatRect Player::getBounds() const {
    return m_shape.getGlobalBounds();
}

sf::FloatRect Player::getPlayerDimensions() const {
    return m_shape.getLocalBounds();
}

void Player::setPosition(const sf::Vector2f &position) {
    m_shape.setPosition(position);
}

void Player::setOnGround(const bool value) {
    m_onGround = value;
}

void Player::attack() {
    // if cooldown has passed
    if (m_cooldownAttackClock.getElapsedTime() == sf::Time::Zero && m_activeAttackClock.getElapsedTime() <= m_activeAttackTime) {
        m_cooldownAttackClock.start();
        // Using restart() to be able to spam-attack
        m_activeAttackClock.restart();
        m_isAttacking = true;
    }

}

// Code=1
sf::FloatRect Player::getAttackingBounds() const {
    return attackingShape.getGlobalBounds();
}
