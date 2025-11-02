//
// Created by david on 11/2/2025.
//

#ifndef SOUNDFUGUE_ENEMY_HPP
#define SOUNDFUGUE_ENEMY_HPP
#include <SFML/Graphics.hpp>

class Enemy {
public:
    Enemy(const sf::Vector2f &position, const sf::Vector2f &size);

    void update(sf::Time dt);

    void draw(sf::RenderTarget &target) const;

    sf::FloatRect getEnemyBounds() const;

private:
    sf::RectangleShape m_shape;
    sf::Vector2f m_velocity;
    float m_leftLimit;
    float m_rightLimit;
};

#endif //SOUNDFUGUE_ENEMY_HPP
