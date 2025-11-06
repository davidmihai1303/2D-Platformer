//
// Created by david on 11/2/2025.
//

#ifndef SOUNDFUGUE_TEXTUREHOLDER_HPP
#define SOUNDFUGUE_TEXTUREHOLDER_HPP
#include <SFML/Graphics.hpp>
#include <string>

class TextureHolder {
public:
    explicit TextureHolder(const std::string &path);

    ~TextureHolder();

    // We use reference to avoid making a copy of the large texture object
    [[nodiscard]] const sf::Texture &get() const;

private:
    sf::Texture *m_texture;
};

#endif //SOUNDFUGUE_TEXTUREHOLDER_HPP
