//
// Created by david on 10/31/2025.
//

#include "Player.hpp"

Player::Player(const sf::Texture &standingTexture, const sf::Texture &walkingTexture) : m_standingSprite(
        standingTexture), m_walkingSprite(walkingTexture), m_onGround(false), m_lastFacingDirection(true),
    m_frozenVelocity(sf::Vector2f(0, 0)),
    m_isFrozen(false), m_shiftFromGround(false), m_dashAttack(false),
    m_hasDashed(false),
    m_animationToDraw(0),
    m_standing_currentFrame(0),
    m_standing_animDuration(0.2f),
    m_standing_elapsedTime(0.f),
    m_standing_numFrames(8),
    m_walking_currentFrame(0),
    m_walking_animDuration(0.2f),
    m_walking_elapsedTime(0.f),
    m_walking_numFrames(8) {
    // Create the player's hitbox
    m_shape.setSize(sf::Vector2f({50.f, 100.f}));
    m_shape.setFillColor(sf::Color::Green);
    m_shape.setPosition({0.f, 250.f});
    m_currentFacingDirection = true; // Different from all the other entities (enemies)


    // -------- STANDING ANIMATION --------
    // CALCULATE FRAME SIZE
    // A horizontal strip: Width / 8, Height = Full Height
    const sf::Vector2u standingTextureSize = standingTexture.getSize();
    m_standing_frameSize = sf::Vector2u(standingTextureSize.x / m_standing_numFrames, standingTextureSize.y);
    // Set the first frame
    m_standingSprite.setTextureRect(sf::IntRect({0, 0}, sf::Vector2<int>(m_standing_frameSize)));
    m_standingSprite.setOrigin({
        m_standingSprite.getLocalBounds().size.x / 2 + 5.f, m_standingSprite.getLocalBounds().size.y
    }); //origin in the middle bottom with offset to match the body

    //     --------- WALKING ANIMATION --------
    const sf::Vector2u walkingTextureSize = standingTexture.getSize();
    m_walking_frameSize = sf::Vector2u(walkingTextureSize.x / m_walking_numFrames, walkingTextureSize.y);
    m_walkingSprite.setTextureRect(sf::IntRect({0, 0}, sf::Vector2<int>(m_walking_frameSize)));
    m_walkingSprite.setOrigin({
        m_walkingSprite.getLocalBounds().size.x / 2 + 5.f, m_walkingSprite.getLocalBounds().size.y
    }); //origin in the middle bottom with offset to match the body
}

void Player::update(const sf::Time dt) {
    movementLogic(dt);
    attackingLogic();
    animationLogic(dt);

    // To have access to the player's position at all times without auxiliary func
    m_position = m_shape.getPosition();
}

void Player::movementLogic(const sf::Time dt) {
    constexpr float gravity = 2000.f;

    // Left-Right movement
    m_movement = sf::Vector2f(0.f, 0.f);
    if (!m_isFrozen) {
        constexpr float moveSpeed = 350.f;
        // so the player can't move while he's attacking in air
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scan::A)) {
            m_movement.x -= moveSpeed;
            m_currentFacingDirection = false;
            m_isMoving = true;
        } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scan::D)) {
            m_movement.x += moveSpeed;
            m_currentFacingDirection = true;
            m_isMoving = true;
        } else {
            m_shiftFromGround = false;
            m_isMoving = false;
        }
    }

    // Jumping logic and gravity
    if (m_onGround && sf::Keyboard::isKeyPressed(sf::Keyboard::Scan::Space)) {
        constexpr float jumpStrength = 550.f;
        m_velocity.y = -jumpStrength;
        m_onGround = false;
        // Stop attacking only when jump begins
        if (m_isAttacking) {
            m_isAttacking = false;
            m_activeAttackClock.reset();
        }
    }
    if (!m_isFrozen)
        m_velocity.y += gravity * dt.asSeconds(); // Make sure gravity doesn't stack up while frozen in-air

    // Running Logic
    if (m_inputState.shiftDown) {
        m_movement.x *= 1.71f; //TODO experiment with other values
        if (m_onGround)
            m_shiftFromGround = true;
    }

    if (!m_inputState.shiftDown && m_onGround)
        m_shiftFromGround = false;


    // Stop moving if attacking
    if (m_isAttacking && !m_dashAttack) {
        if (m_inputState.firstPressed != 's')
            m_movement.x = 0.f;
        else
            m_movement.x *= 1.2f;
    }

    // Smoothen dash attack so it decreases in speed over time
    if (m_dashAttack)
        m_velocity.x *= 0.985f; //TODO experiment with other values

    // Move horizontally and vertically
    m_shape.move((m_movement + m_velocity) * dt.asSeconds());

    //TODO MAYBE - Make player move for heavier A/D presses. For subtle presses only change facing direction

    if (m_lastFacingDirection != m_currentFacingDirection) {
        m_standingSprite.setScale({-1.f * m_standingSprite.getScale().x, 1.f});
    }
}

void Player::attackingLogic() {
    // Reset the attack cooldown
    if (m_cooldownAttackClock.getElapsedTime() >= m_cooldownAttackTime)
        m_cooldownAttackClock.reset();
    // Reset the active attack
    if (m_activeAttackClock.getElapsedTime() >= m_activeAttackTime) {
        m_activeAttackClock.reset();
        m_isAttacking = false;
        if (m_isFrozen) {
            m_velocity = m_frozenVelocity; // Restore pre-attack motion
            m_isFrozen = false;
        }
        m_dashAttack = false;
    }

    if (m_isAttacking) {
        // Stop attacking if changing facing direction
        if (m_currentFacingDirection != m_lastFacingDirection) {
            m_isAttacking = false;
            m_activeAttackClock.reset();
        }
    }
    m_lastFacingDirection = m_currentFacingDirection; // update for next frame

    // Code=1
    // Draw a rectangle representing the hitbox of the Hit-Area
    attackingShape.setSize(sf::Vector2f({40.f, 65.f}));
    attackingShape.setFillColor(sf::Color::Blue);
    if (m_currentFacingDirection) {
        // facing right
        attackingShape.setOrigin({0.f, 0.f}); // Set origin back to default
        attackingShape.setPosition(m_shape.getPosition() + sf::Vector2f(m_shape.getSize().x, 0.f));
    } else {
        // facing left
        attackingShape.setOrigin({attackingShape.getLocalBounds().size.x, 0.f}); // Set origin to the top-right corner
        attackingShape.setPosition(m_shape.getPosition());
    }
}

void Player::attack() {
    // if cooldown has passed
    if (m_cooldownAttackClock.getElapsedTime() == sf::Time::Zero && m_activeAttackClock.getElapsedTime() <=
        m_activeAttackTime) {
        m_isAttacking = true;
        m_cooldownAttackClock.start();
        // Using restart() to be able to spam-attack
        m_activeAttackClock.restart();

        if (!m_onGround) {
            // We are already in the air when starting the attack
            m_isFrozen = true;
            if (m_shiftFromGround && !m_hasDashed) {
                m_hasDashed = true;
                // Running jump - keep moving forward, no A/D control
                m_dashAttack = true;
                constexpr float dashSpeed = 300.f; //TODO experiment with other values
                m_velocity.x = m_currentFacingDirection ? dashSpeed : -dashSpeed;
                m_velocity.y = 0.f;
            } else {
                // Neutral jump -> classic freeze in air
                m_frozenVelocity = m_velocity;
                m_velocity = {0.f, 0.f};
            }
        }
    }
}

void Player::animationLogic(const sf::Time dt) {
    standingAnimation(dt);
   // walkingAnimation(dt);
}

void Player::standingAnimation(const sf::Time dt) {

    m_standing_elapsedTime += dt.asSeconds();

    // If enough time passed, switch to next frame
    if (m_standing_elapsedTime >= m_standing_animDuration) {
        m_standing_elapsedTime = 0.f; // Reset timer
        m_standing_currentFrame++; // Next frame

        // Loop back to 0 if we exceed the count (0 -> 1 -> ... -> 7 -> 0)
        if (m_standing_currentFrame >= m_standing_numFrames) {
            m_standing_currentFrame = 0;
        }

        // Calculating the coordinate for every frame;
        // Frame x starts at x * width (80 here)
        const long long leftAux = m_standing_currentFrame * m_standing_frameSize.x;
        int left = static_cast<int>(leftAux); // weird conversion

        int top = 0; // Top is always 0 for a single row spritesheet

        m_standingSprite.setTextureRect(sf::IntRect({left, top}, sf::Vector2<int>(m_standing_frameSize)));
    }

    // --- SYNC POSITION ---
    // Snap sprite to hitbox
    m_standingSprite.setPosition({
        m_shape.getPosition().x + m_shape.getSize().x / 2, m_shape.getPosition().y + m_shape.getSize().y
    });
}

void walkingAnimation(const sf::Time dt) {
}


void Player::setInputState(const InputState &inputState) {
    m_inputState = inputState;
}

// Code=1
sf::FloatRect Player::getAttackingBounds() const {
    return attackingShape.getGlobalBounds();
}

void Player::setOnGround(const bool value) {
    m_onGround = value;
}

sf::FloatRect Player::getPlayerDimensions() const {
    return m_shape.getLocalBounds();
}

void Player::resetDash() {
    m_hasDashed = false;
}

void Player::setPosition(const sf::Vector2f &position) {
    m_shape.setPosition(position);
    m_standingSprite.setPosition({
        m_shape.getPosition().x + m_shape.getSize().x / 2, m_shape.getPosition().y + m_shape.getSize().y
    });
}

void Player::draw(sf::RenderTarget &target) const {
    target.draw(m_shape);
    switch (m_animationToDraw) {
        case 0:
            target.draw(m_standingSprite);
            break;

        case 1:
            target.draw(m_walkingSprite);
            break;

        default:
            throw std::runtime_error("Invalid animation index");
    }

    // Code=1
    if (m_isAttacking) {
        target.draw(attackingShape);
    }
}

std::ostream &operator<<(std::ostream &os, const Player &p) {
    os << "Player{";
    os << static_cast<const Entity &>(p); // apelează operatorul din Entity
    os << ", attacking=" << (p.m_isAttacking ? "true" : "false");
    os << ", sprite= " << p.m_standingSprite.getLocalBounds().size.x << ", " << p.m_standingSprite.getLocalBounds().size
            .y;
    os << "}";
    return os;
}
