//
// Created by david on 11/4/2025.
//

#include "Entity.hpp"

Entity::Entity()
    : m_position(0.f, 0.f), m_velocity(0.f, 0.f) {
}

sf::Vector2f Entity::getPosition() const {
    return m_position;
}

sf::Vector2f Entity::getVelocity() const {
    return m_velocity;
}

void Entity::setVelocity(const sf::Vector2f &velocity) {
    m_velocity = velocity;
}
