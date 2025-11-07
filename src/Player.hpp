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

    void movementLogic(sf::Time dt) override;

    void attackingLogic() override;

    //TODO ??
    sf::FloatRect getPlayerDimensions() const;

    void setOnGround(bool value);

    void attack();

    // Code=1
    sf::FloatRect getAttackingBounds() const;

private:
    bool m_onGround = false;
    sf::Time m_cooldownAttackTime = sf::seconds(0.5f);
    sf::Time m_activeAttackTime = sf::seconds(1.f); //TODO not sure

    // Code=1
    sf::RectangleShape attackingShape;

    bool m_lastFacingDirection;

};


#endif //SOUNDFUGUE_PLAYER_HPP
