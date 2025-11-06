//
// Created by david on 11/2/2025.
//

#ifndef SOUNDFUGUE_ENEMY_HPP
#define SOUNDFUGUE_ENEMY_HPP

#include <SFML/Graphics.hpp>
#include "Entity.hpp"

class Enemy : public Entity {
public:
    Enemy(const sf::Vector2f &position, const sf::Vector2f &size);

    void update(sf::Time dt) override;

    void draw(sf::RenderTarget &target) const override;

    void setPosition(const sf::Vector2f &position) override;

    sf::FloatRect getBounds() const override;

private:
    sf::RectangleShape m_shape;
    float m_leftLimit;
    float m_rightLimit;
};

#endif //SOUNDFUGUE_ENEMY_HPP
