//
// Created by david on 10/31/2025.
//

#ifndef SOUNDFUGUE_PLAYER_HPP
#define SOUNDFUGUE_PLAYER_HPP

#include <SFML/Graphics.hpp>
#include "Entity.hpp"
#include "InputState.hpp"

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

    void setInputState(const InputState& inputState);


    // Code=1
    sf::FloatRect getAttackingBounds() const;

private:
    InputState m_inputState;
    sf::Vector2f m_movement;
    bool m_onGround;
    sf::Time m_cooldownAttackTime = sf::seconds(0.5f);
    sf::Time m_activeAttackTime = sf::seconds(1.f); //TODO not sure

    // Code=1
    sf::RectangleShape attackingShape;
    bool m_lastFacingDirection;

    // Attacking in-air helpers
    sf::Vector2f m_frozenVelocity;
    bool m_isFrozen;

};


#endif //SOUNDFUGUE_PLAYER_HPP
