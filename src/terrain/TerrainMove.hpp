#ifndef SOUNDFUGUE_TERRAINMOVE_HPP
#define SOUNDFUGUE_TERRAINMOVE_HPP

#include <SFML/Graphics/Rect.hpp>
#include "terrain/TerrainContacts.hpp"

struct TerrainMove {
    sf::FloatRect bounds{};
    TerrainContacts contacts{};
};

#endif // SOUNDFUGUE_TERRAINMOVE_HPP
