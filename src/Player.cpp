//
// Created by david on 10/31/2025.
//

#include "Player.hpp"
#include <iostream>

Player::Player() {
    m_shape.setSize(sf::Vector2f({50.f, 100.f}));
    m_shape.setFillColor(sf::Color::Green);
    m_shape.setPosition({0.f, 450.f});
    m_currentFacingDirection = true; // Different from all the other entities (enemies)
    m_lastFacingDirection = m_currentFacingDirection;
}

void Player::update(const sf::Time dt) {

    movementLogic(dt);

    attackingLogic();


    std::cout << m_velocity.x << " " << m_velocity.y <<'\n';


    // To have access to the player's position at all times without auxiliary func
    m_position = m_shape.getPosition();
}

void Player::movementLogic(const sf::Time dt) {
    constexpr float moveSpeed = 350.f;
    constexpr float gravity = 2000.f;

    // Left-Right movement
    sf::Vector2f movement(0.f, 0.f);
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scan::A)) {
        movement.x -= moveSpeed;
        m_currentFacingDirection = false;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scan::D)) {
        movement.x += moveSpeed;
        m_currentFacingDirection = true;
    }

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
        movement.x *= 1.71f; //TODO experiment with other values

    // Move horizontally and vertically
    m_shape.move((movement + m_velocity) * dt.asSeconds());
}

void Player::attackingLogic() {
    // Reset the attack cooldown
    if (m_cooldownAttackClock.getElapsedTime() >= m_cooldownAttackTime)
        m_cooldownAttackClock.reset();

    // Reset the active attack
    if (m_activeAttackClock.getElapsedTime() >= m_activeAttackTime) {
        m_activeAttackClock.reset();
        m_isAttacking = false;
    }

    // Stop attacking if changing facing direction
    if (m_currentFacingDirection != m_lastFacingDirection) {
        if (m_isAttacking) {
            m_isAttacking = false;
            m_activeAttackClock.reset();
        }
    }
    m_lastFacingDirection = m_currentFacingDirection; // update for next frame

    // Code=1
    // Draw a rectangle representing the hitbox of the Hit-Area
    attackingShape.setSize(sf::Vector2f({40.f, 65.f}));
    attackingShape.setFillColor(sf::Color::Blue);
    if (m_currentFacingDirection) {
        // facing right
        attackingShape.setOrigin({0.f, 0.f}); // Set origin back to default
        attackingShape.setPosition(m_shape.getPosition() + sf::Vector2f(m_shape.getSize().x, 0.f));
    } else {
        // facing left
        attackingShape.setOrigin({attackingShape.getLocalBounds().size.x, 0.f}); // Set origin to the top-right corner
        attackingShape.setPosition(m_shape.getPosition());
    }
}

void Player::attack() {
    // if cooldown has passed
    if (m_cooldownAttackClock.getElapsedTime() == sf::Time::Zero && m_activeAttackClock.getElapsedTime() <=
        m_activeAttackTime) {
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

void Player::setOnGround(const bool value) {
    m_onGround = value;
}

sf::FloatRect Player::getPlayerDimensions() const {
    return m_shape.getLocalBounds();
}

void Player::draw(sf::RenderTarget &target) const {
    target.draw(m_shape);
    // Code=1
    if (m_isAttacking) {
        target.draw(attackingShape);
    }
}
