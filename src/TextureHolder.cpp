//
// Created by david on 11/2/2025.
//

#include "TextureHolder.hpp"
#include <iostream>

TextureHolder::TextureHolder(const std::string &path) {
    m_texture = new sf::Texture();
    if (!m_texture->loadFromFile(path)) {
        std::cerr << "Error: couldn't load texture at " << path << "\n";
    }
}

TextureHolder::TextureHolder(const TextureHolder &other) {
    m_texture = new sf::Texture(*other.m_texture);
}

TextureHolder &TextureHolder::operator=(const TextureHolder &other) {
    if (this != &other) {
        delete m_texture;
        m_texture = new sf::Texture(*other.m_texture);
    }
    return *this;
}

TextureHolder::~TextureHolder() {
    delete m_texture;
}

const sf::Texture &TextureHolder::get() const {
    if (!m_texture) {
        throw std::runtime_error("Texture not loaded!");
    }
    return *m_texture;
}
