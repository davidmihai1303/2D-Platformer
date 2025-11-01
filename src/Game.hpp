//
// Created by david on 10/31/2025.
//

#ifndef SOUNDFUGUE_GAME_HPP
#define SOUNDFUGUE_GAME_HPP
#include <SFML/Graphics.hpp>
#include "World.hpp"

class Game {
public:
    Game();

    void run();

private:
    void processEvents();

    void render();

    sf::RenderWindow m_window;
    World m_world;
};


#endif //SOUNDFUGUE_GAME_HPP
