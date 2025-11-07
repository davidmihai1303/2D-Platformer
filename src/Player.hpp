//
// Created by david on 10/31/2025.
//

#ifndef SOUNDFUGUE_PLAYER_HPP
#define SOUNDFUGUE_PLAYER_HPP

#include <SFML/Graphics.hpp>
#include "Entity.hpp"

class Player final : public Entity {
public:
    Player();

    void update(sf::Time dt) override;

    void draw(sf::RenderTarget &target) const override;

    sf::FloatRect getBounds() const override;

    //TODO ??
    sf::FloatRect getPlayerDimensions() const;

    void setPosition(const sf::Vector2f &position) override;

    void setOnGround(bool value);

    void attack();

    // Code=1
    sf::FloatRect getAttackingBounds() const;

private:
    sf::RectangleShape m_shape;
    bool m_onGround = false;
    sf::Time m_cooldownAttackTime = sf::seconds(0.5f);
    sf::Time m_activeAttackTime = sf::seconds(1.f); //TODO not sure

    // Code=1
    sf::RectangleShape attackingShape;
};


#endif //SOUNDFUGUE_PLAYER_HPP
