//
// Created by david on 11/4/2025.
//

#include "Entity.hpp"

Entity::Entity()
    : m_position(0.f, 0.f), m_velocity(0.f, 0.f), m_isMoving(false), m_isAttacking(false),
      m_currentFacingDirection(false) {
    // Set the clocks on stop and time=0 by default
    m_activeAttackClock.reset();
    m_cooldownAttackClock.reset();
}

sf::Vector2f Entity::getPosition() const {
    return m_position;
}

bool Entity::getAttackingState() const {
    return m_isAttacking;
}

sf::Vector2f Entity::getVelocity() const {
    return m_velocity;
}

sf::FloatRect Entity::getBounds() const {
    return m_shape.getGlobalBounds();
}

void Entity::setPosition(const sf::Vector2f &position) {
    m_shape.setPosition(position);
}

void Entity::setVelocity(const sf::Vector2f &velocity) {
    m_velocity = velocity;
}

std::ostream &operator<<(std::ostream &os, const Entity &e) {
    os << "Entity(pos: " << e.m_shape.getGlobalBounds().position.x << ", " << e.m_shape.getGlobalBounds().position.y
            << ", vel: " << e.m_velocity.x << ", " << e.m_velocity.y << ")";
    return os;
}
