//
// Created by david on 11/6/2025.
//

#ifndef SOUNDFUGUE_NOTE_HPP
#define SOUNDFUGUE_NOTE_HPP

#include <SFML/Graphics.hpp>

class Note {
public:
    explicit Note(const sf::Vector2f& position);

    void draw(sf::RenderTarget &target) const;

    sf::FloatRect getBounds() const;

private:
    sf::RectangleShape m_shape;
    float m_topLimit;
    float m_bottomLimit;
};


#endif //SOUNDFUGUE_NOTE_HPP
