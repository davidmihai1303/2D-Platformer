//
// Created by david on 10/31/2025.
//

#ifndef SOUNDFUGUE_PLAYER_HPP
#define SOUNDFUGUE_PLAYER_HPP

#include <SFML/Graphics.hpp>

class Player {
public:
    Player();

    void update(sf::Time dt);

    void draw(sf::RenderTarget &target) const;

    sf::FloatRect getPlayerBounds() const;

    sf::FloatRect getPlayerDimensions() const;

    void setPlayerPosition(sf::Vector2f position);

    void setVelocityY(float y);

    void setOnGround(bool value);

private:
    sf::RectangleShape m_shape;
    sf::Vector2f m_velocity;
    bool m_onGround = false;
};


#endif //SOUNDFUGUE_PLAYER_HPP
