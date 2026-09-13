#include "terrain/TerrainCollision.hpp"

#include <utility>

TerrainCollision::TerrainCollision(std::vector<sf::FloatRect> solids)
    : m_solids(std::move(solids)) {}

TerrainCollision::~TerrainCollision() = default;

TerrainMove TerrainCollision::resolveMovement(sf::FloatRect startBounds, const sf::Vector2f displacement) {
    startBounds.position += displacement;
    return {startBounds, {}};
}

const std::vector<sf::FloatRect>& TerrainCollision::getSolids() const {
    return m_solids;
}
