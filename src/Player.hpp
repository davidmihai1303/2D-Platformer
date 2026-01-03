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
    friend std::ostream& operator<<(std::ostream& os, const Player& p);

    explicit Player(const sf::Texture& texture);

    void update(sf::Time dt) override;

    void draw(sf::RenderTarget &target) const override;

    void movementLogic(sf::Time dt) override;

    void attackingLogic() override;

    //TODO ??
    sf::FloatRect getPlayerDimensions() const;

    void setOnGround(bool value);

    void attack();

    void setInputState(const InputState &inputState);

    void resetDash();

    void setPosition(const sf::Vector2f &position) override;

    // Code=1
    sf::FloatRect getAttackingBounds() const;

private:
    sf::Sprite m_sprite;

    InputState m_inputState;
    sf::Vector2f m_movement;
    bool m_onGround;
    sf::Time m_cooldownAttackTime = sf::seconds(.5f);
    sf::Time m_activeAttackTime = sf::seconds(.8f); //TODO experiment with other values

    // Code=1
    sf::RectangleShape attackingShape;
    bool m_lastFacingDirection;

    // Attacking in-air helpers
    sf::Vector2f m_frozenVelocity;
    bool m_isFrozen;

    bool m_shiftFromGround;    // If you pressed Shift while you were on ground
    // We need this variable to tell whether the jump was while moving or while running, regardless of pressing Shift in-air

    bool m_dashAttack;
    bool m_hasDashed;

    // --- Animation Variables ---
    int m_currentFrame;       // Current frame index (0 to 7)
    float m_animDuration;     // How long one frame stays on screen (e.g. 0.1s)
    float m_elapsedTime;      // Timer accumulator
    sf::Vector2u m_frameSize; // Width and Height of a single frame
    int m_numFrames;          // Total frames (8 in your case)
    // ---------------------------

};


#endif //SOUNDFUGUE_PLAYER_HPP
