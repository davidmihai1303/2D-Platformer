//
// Created by david on 10/31/2025.
//

#include "Game.hpp"
#include "World.hpp"

Game::Game() : m_window(sf::VideoMode({800, 600}), "Sound Fugue"), m_world(m_window) {
}

void Game::run() {
    sf::Clock clock;
    while (m_window.isOpen()) {
        const sf::Time dt = clock.restart();
        processEvents();
        m_world.update(dt);
        m_window.clear(sf::Color::Blue);
        m_world.draw();
        m_window.display();
    }
}


void Game::processEvents() {
    while (const auto event = m_window.pollEvent()) {
        if (event->is<sf::Event::Closed>()) {
            m_window.close();
        }
        // else if (auto* resize = event->getIf<sf::Event::Resized>()) {
        //     // Maintain a fixed world size, e.g. 800x600
        //     const float windowRatio = static_cast<float>(resize->size.x) / resize->size.y;
        //     constexpr float viewRatio = 800.f / 600.f;
        //     float sizeX = 1.f;
        //     float sizeY = 1.f;
        //     float posX = 0.f;
        //     float posY = 0.f;
        //
        //     if (windowRatio > viewRatio) {
        //         // window too wide
        //         sizeX = viewRatio / windowRatio;
        //         posX = (1.f - sizeX) / 2.f;
        //     } else {
        //         // window too tall
        //         sizeY = windowRatio / viewRatio;
        //         posY = (1.f - sizeY) / 2.f;
        //     }
        //
        //     sf::View view({400.f, 300.f}, {800.f, 600.f});
        //     view.setViewport(sf::FloatRect({posX, posY}, {sizeX, sizeY}));
        //     m_window.setView(view);
        // }
    }
}