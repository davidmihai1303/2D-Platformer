//
// Created by david on 11/4/2025.
//

#include "Entity.hpp"

Entity::Entity()
    : m_position(0.f, 0.f), m_velocity(0.f, 0.f) {
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

void Entity::setAttackingState(bool state) {
    m_isAttacking = state;
}

sf::Vector2f Entity::getVelocity() const {
    return m_velocity;
}

void Entity::setVelocity(const sf::Vector2f &velocity) {
    m_velocity = velocity;
}
