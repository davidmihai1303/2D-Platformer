//
// Created by david on 10/31/2025.
//

#include "Player.hpp"
#include <iostream>

Player::Player() : m_onGround(false), m_lastFacingDirection(true), m_frozenVelocity(sf::Vector2f(0, 0)),
                   m_isFrozen(false) {
    m_shape.setSize(sf::Vector2f({50.f, 100.f}));
    m_shape.setFillColor(sf::Color::Green);
    m_shape.setPosition({0.f, 450.f});
    m_currentFacingDirection = true; // Different from all the other entities (enemies)
}

void Player::update(const sf::Time dt) {
    movementLogic(dt);

    attackingLogic();


    //std::cout << m_movement.x << "    " << m_movement.y << "   " << '\n';
    std::cout << m_velocity.x << " " << m_velocity.y << '\n';
    // std::cout << m_inputState.shiftDown << " " << m_inputState.clickDown << " " << m_inputState.firstPressed << '\n';


    // To have access to the player's position at all times without auxiliary func
    m_position = m_shape.getPosition();
}

void Player::movementLogic(const sf::Time dt) {
    constexpr float moveSpeed = 350.f;
    constexpr float gravity = 2000.f;

    // Left-Right movement
    m_movement = sf::Vector2f(0.f, 0.f);
    if (!m_isFrozen) {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scan::A)) {
            m_movement.x -= moveSpeed;
            m_currentFacingDirection = false;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scan::D)) {
            m_movement.x += moveSpeed;
            m_currentFacingDirection = true;
        }
    }

    // Jumping logic and gravity
    if (m_onGround && sf::Keyboard::isKeyPressed(sf::Keyboard::Scan::Space)) {
        constexpr float jumpStrength = 550.f;
        m_velocity.y = -jumpStrength;
        m_onGround = false;
        // Stop attacking only when jump begins
        if (m_isAttacking) {
            m_isAttacking = false;
            m_activeAttackClock.reset();
        }
    }
    if (!m_isFrozen)
        m_velocity.y += gravity * dt.asSeconds(); // Make sure gravity doesn't stack upp while frozen in-air

    // Running Logic
    if (m_inputState.shiftDown) {
        m_movement.x *= 1.71f; //TODO experiment with other values
    }

    // Stop moving if attacking
    if (m_isAttacking) {
        if (m_inputState.firstPressed != 's')
            m_movement.x = 0;
        else
            m_movement.x *= 1.2f;       // Running and attacking gives speed boost
    }

    // Move horizontally and vertically
    m_shape.move((m_movement + m_velocity) * dt.asSeconds());
}

void Player::attackingLogic() {
    // Reset the attack cooldown
    if (m_cooldownAttackClock.getElapsedTime() >= m_cooldownAttackTime)
        m_cooldownAttackClock.reset();
    // Reset the active attack
    if (m_activeAttackClock.getElapsedTime() >= m_activeAttackTime) {
        m_activeAttackClock.reset();
        m_isAttacking = false;
        if (m_isFrozen) {
            m_velocity = m_frozenVelocity; // Restore pre-attack motion
            m_isFrozen = false;
        }
    }

    if (m_isAttacking) {
        // Stop attacking if changing facing direction
        if (m_currentFacingDirection != m_lastFacingDirection) {
            m_isAttacking = false;
            m_activeAttackClock.reset();
        }

        // Attacking in-air logic
        if (!m_onGround) {
            m_frozenVelocity = m_velocity;
            m_velocity = {0.f, 0.f};
            m_isFrozen = true;
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
        m_isAttacking = true;
        m_cooldownAttackClock.start();
        // Using restart() to be able to spam-attack
        m_activeAttackClock.restart();
    }
}

void Player::setInputState(const InputState &inputState) {
    m_inputState = inputState;
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
