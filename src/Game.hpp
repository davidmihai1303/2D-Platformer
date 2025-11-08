//
// Created by david on 10/31/2025.
//

#ifndef SOUNDFUGUE_GAME_HPP
#define SOUNDFUGUE_GAME_HPP
#include <SFML/Graphics.hpp>
#include "World.hpp"
#include "InputState.hpp"

class Game {
public:
    Game();

    void run();

private:
    void processEvents();

    void updateView(float x, float y);

    void updateCamera();

    sf::RenderWindow m_window;
    sf::View m_view;
    World m_world;
    const unsigned int m_fps = 60;

    InputState m_inputState;
};


#endif //SOUNDFUGUE_GAME_HPP
