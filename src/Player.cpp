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

    sf::Vector2f movement(0.f, 0.f);
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scan::A)) movement.x -= moveSpeed;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scan::D)) movement.x += moveSpeed;

    if (m_onGround && sf::Keyboard::isKeyPressed(sf::Keyboard::Scan::Space)) {
        constexpr float jumpStrength = 550.f;
        m_velocity.y = -jumpStrength;
        m_onGround = false;
    }
    // Apply gravity
    m_velocity.y += gravity * dt.asSeconds();

    // Move horizontally and vertically
    m_shape.move((movement + m_velocity) * dt.asSeconds());

    //TODO ??
    m_position = m_shape.getPosition();
}

void Player::draw(sf::RenderTarget &target) const {
    target.draw(m_shape);
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

void Player::setVelocityY(const float y) {
    m_velocity.y = y;
}

void Player::setOnGround(const bool value) {
    m_onGround = value;
}