//
// Created by david on 11/6/2025.
//

#include "Note.hpp"

Note::Note(const sf::Vector2f &position){
    m_shape.setSize(sf::Vector2f(20.f, 20.f));
    m_shape.setFillColor(sf::Color::Yellow);
    m_shape.setPosition(position);
}

void Note::draw(sf::RenderTarget &target) const{
    target.draw(m_shape);
}

sf::FloatRect Note::getBounds() const {
    return m_shape.getGlobalBounds();
}