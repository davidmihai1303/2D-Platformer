//
// Created by david on 11/4/2025.
//

#ifndef SOUNDFUGUE_ENTITY_HPP
#define SOUNDFUGUE_ENTITY_HPP

#include <SFML/Graphics.hpp>

class Entity {
public:
    Entity();

    virtual ~Entity() = default;

    virtual void update(sf::Time dt) = 0;

    virtual void draw(sf::RenderTarget &target) const = 0;

    virtual sf::FloatRect getBounds() const = 0;

    // Position and velocity helpers
    virtual sf::Vector2f getPosition() const;

    virtual void setPosition(const sf::Vector2f &position) = 0;

    sf::Vector2f getVelocity() const;

    void setVelocity(const sf::Vector2f &velocity);

protected:
    sf::Vector2f m_position;
    sf::Vector2f m_velocity;
};


#endif //SOUNDFUGUE_ENTITY_HPP
