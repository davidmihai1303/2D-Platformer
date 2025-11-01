//
// Created by david on 10/31/2025.
//

#include "Player.hpp"

Player::Player() {
    m_shape.setSize(sf::Vector2f({50.f, 100.f}));
    m_shape.setFillColor(sf::Color::Green);
}

void Player::update(const sf::Time dt) {
    constexpr float speed = 200.f;
    sf::Vector2f movement(0.f, 0.f);

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scan::A)) movement.x -= speed;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scan::D)) movement.x += speed;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scan::W)) movement.y -= speed;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scan::S)) movement.y += speed;

    m_shape.move(movement * dt.asSeconds());

}

void Player::draw(sf::RenderTarget &target) const {
    target.draw(m_shape);
}

sf::FloatRect Player::getPlayerBounds() const {
    return m_shape.getGlobalBounds();
}

void Player::setPlayerPosition(const sf::Vector2f position) {
    m_shape.setPosition(position);
}

sf::FloatRect Player::getPlayerDimensions() const {
    return m_shape.getLocalBounds();
}