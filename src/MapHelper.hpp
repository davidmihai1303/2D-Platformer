//
// Created by david on 1/9/2026.
//

#ifndef SOUNDFUGUE_MAPHELPER_HPP
#define SOUNDFUGUE_MAPHELPER_HPP
#include <SFML/Graphics.hpp>
#include <tmxlite/Map.hpp>

class MapHelper final : public sf::Drawable, public sf::Transformable {
public:
    // We pass the loaded map and the index of the layer we want to draw (0, 1, 2...)
    MapHelper(const tmx::Map &map, std::size_t layerIdx);

private:
    // This function is required by sf::Drawable
    void draw(sf::RenderTarget &target, sf::RenderStates states) const override;

    // A map might use multiple images (tilesets).
    // We group vertices by the texture they need so we can draw them efficiently.
    struct RenderBatch {
        std::shared_ptr<sf::Texture> texture; // Keep the texture alive
        sf::VertexArray vertices;
    };

    std::vector<RenderBatch> m_batches;
};


#endif //SOUNDFUGUE_MAPHELPER_HPP
