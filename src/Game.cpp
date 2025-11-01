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
        m_window.clear(sf::Color::Black);
        m_world.draw();
        m_window.display();
    }
}


void Game::processEvents() {
    while (auto event = m_window.pollEvent()) {
        if (event->is<sf::Event::Closed>()) {
            m_window.close();
        }
    }
}

void Game::render() {
    m_window.clear(sf::Color::Black);
    m_window.display();
}
