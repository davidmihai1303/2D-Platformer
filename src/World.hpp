//
// Created by david on 11/1/2025.
//

#ifndef SOUNDFUGUE_WORLD_HPP
#define SOUNDFUGUE_WORLD_HPP
#include <SFML/Graphics.hpp>
#include <vector>
#include <memory>
#include "Player.hpp"
#include "Enemy.hpp"
#include "Entity.hpp"
#include "Note.hpp"

class World {
public:
    explicit World(sf::RenderWindow &window);

    void update(sf::Time dt);

    void draw() const;

    sf::Vector2f getPlayerPosition() const;

    void playerAttack();

private:
    void handleCollisions();

    void collision_player_ground(sf::FloatRect &playerBounds);

    void collision_player_enemies(sf::FloatRect &playerBounds);

    void collision_player_notes(sf::FloatRect &playerBounds);

    sf::RenderWindow &m_window;

    sf::RectangleShape m_ground;

    std::vector<std::unique_ptr<Entity> > m_entities;

    Player *m_player = nullptr;

    std::vector<std::unique_ptr<Note> > m_notes;

    // Code=2
    std::vector<sf::Vector2f> positions = {
        {100, 300}, {200, 350}, {300, 380}, {400, 320}, {500, 310},
        {600, 340}, {700, 360}, {800, 300}, {900, 330}, {1000, 350}
    };
    void addNotes();

};

#endif //SOUNDFUGUE_WORLD_HPP
