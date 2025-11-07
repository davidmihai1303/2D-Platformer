//
// Created by david on 10/31/2025.
//

#include "Game.hpp"

Game::Game() : m_window(sf::VideoMode({1920, 1080}), "Sound Fugue"),
               m_view({960.f, 540.f}, {1920.f, 1080.f}),
               m_world(m_window) {
}

void Game::run() {
    m_window.setFramerateLimit(m_fps);
    m_window.setView(m_view);
    sf::Clock clock;
    while (m_window.isOpen()) {
        sf::Time dt = clock.restart();

        // Clamp to prevent large jumps (resize, alt-tab, etc.)
        if (dt.asSeconds() > 0.05f)
            dt = sf::seconds(0.05f);

        processEvents();
        m_world.update(dt);
        updateCamera();

        m_window.setView(m_view);

        m_window.clear();
        m_world.draw();
        m_window.display();
    }
}


void Game::processEvents() {
    while (auto event = m_window.pollEvent()) {
        if (event->is<sf::Event::Closed>()) {
            m_window.close();
        } else if (auto *resize = event->getIf<sf::Event::Resized>()) {
            updateView(static_cast<float>(resize->size.x), static_cast<float>(resize->size.y));
        } else if (auto *button = event->getIf<sf::Event::MouseButtonPressed>()) {
            if (button->button == sf::Mouse::Button::Left)
                m_world.playerAttack(); // triggers once
        }
    }
}

// Letter-box type view. Black bars will appear in order to keep the aspect ratio 16:9
void Game::updateView(const float x, const float y) {
    constexpr float baseRatio = 1920.f / 1080.f;
    const float newRatio = x / y;

    float sizeX = 1.f;
    float sizeY = 1.f;
    float posX = 0.f;
    float posY = 0.f;

    if (newRatio > baseRatio) {
        // Window is wider -> add vertical bars on the sides
        sizeX = baseRatio / newRatio;
        posX = (1.f - sizeX) / 2.f;
    } else if (newRatio < baseRatio) {
        // Window is taller -> add horizontal bars top/bottom
        sizeY = newRatio / baseRatio;
        posY = (1.f - sizeY) / 2.f;
    }

    // Reset the view to the logical world (1920x1080)
    m_view.setSize({1920.f, 1080.f});
    m_view.setViewport(sf::FloatRect({posX, posY}, {sizeX, sizeY}));
    m_window.setView(m_view);
}

void Game::updateCamera() {
    // Camera follows the player, but with added delay to make it more fluid
    const sf::Vector2f currentCenter = m_view.getCenter();
    const sf::Vector2f target = m_world.getPlayerPosition();
    constexpr float smoothing = 0.04f; // between 0 and 1, //TODO experiment with values between 0.01 and 0.1
    m_view.setCenter(currentCenter + (target - currentCenter) * smoothing);
    //TODO - make it frame rate independent
}
