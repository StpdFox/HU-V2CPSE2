#include "rectangle.hpp"

Rectangle::Rectangle(sf::Vector2f position, sf::Color color, sf::RectangleShape _shape) :
    Drawable(position, color),
    shape(_shape)
{
    shape.setPosition(position);
    shape.setFillColor(color);
}

void Rectangle::update(sf::RenderWindow& window) {
    shape.setPosition(position);
}

void Rectangle::draw(sf::RenderWindow & window) {
    sf::Color tmp = color;
    if (selected) {
        shape.setFillColor(selectedColor);
    }
    window.draw(shape);
    if (shape.getFillColor() != tmp) {
        shape.setFillColor(tmp);
    }
}


void Rectangle::print(std::ofstream& stream) const {
    // (0,0) RECTANGLE black (640,40)
    stream << "(" << position.x << ", " << position.y << ")"; // Position
    stream << " RECTANGLE "; // Name
    stream << getColorName(color) << " "; // Color
    stream << "(" << shape.getSize().x << ", " << shape.getSize().y << ")"; // Size
}