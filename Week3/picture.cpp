#include "picture.hpp"

#include <iostream>

Picture::Picture(sf::Vector2f position, sf::Color color, const std::string& filename):
    Drawable(position, color),
    filename(filename)
{
    text.loadFromFile(filename);
    sprite.setTexture(text);
    sprite.setColor(color);
}


void Picture::update(sf::RenderWindow & window) {
    sprite.setPosition(position);
}

void Picture::draw(sf::RenderWindow & window) {
    sf::Color tmp = color;
    if (selected) {
        sprite.setColor(selectedColor);
    }
    window.draw(sprite);
    if (sprite.getColor() != tmp) {
        sprite.setColor(tmp);
    }
}

void Picture::print(std::ofstream& stream) const {
    // (-400, -550) PICTURE white picture.jpg
    stream << "(" << position.x << ", " << position.y << ")"; // Position
    stream << " PICTURE "; // Name
    stream << getColorName(color) << " "; // color
    stream << filename; // filename
}