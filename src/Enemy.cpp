//
// Created by david on 11/2/2025.
//

#include "Enemy.hpp"

Enemy::Enemy(const sf::Vector2f &position, const sf::Vector2f &size) {
    m_shape.setSize(size);
    m_shape.setFillColor(sf::Color::Red);
    m_shape.setPosition(position);
    m_velocity = (sf::Vector2f(100.f, 0.f));

    // Set limits to which it moves
    m_leftLimit = position.x - 100.f;
    m_rightLimit = position.x + 100.f;
}

void Enemy::update(const sf::Time dt) {

    movementLogic(dt);

    // To have access to the enemy's position at all times without auxiliary func
    m_position = m_shape.getPosition();
}

void Enemy::draw(sf::RenderTarget &target) const {
    target.draw(m_shape);
}

void Enemy::movementLogic(const sf::Time dt) {
    m_shape.move(m_velocity * dt.asSeconds());

    if (const float x = m_shape.getPosition().x; x < m_leftLimit) {
        m_shape.setPosition({m_leftLimit, m_shape.getPosition().y});
        m_velocity.x = std::abs(m_velocity.x);
    } else if (x + m_shape.getSize().x > m_rightLimit) {
        m_shape.setPosition({m_rightLimit - m_shape.getSize().x, m_shape.getPosition().y});
        m_velocity.x = -std::abs(m_velocity.x);
    }
}

void Enemy::attackingLogic() {
    //TODO
}

void Enemy::setColor(const sf::Color colour) {
    m_shape.setFillColor(colour);
}
