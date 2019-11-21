#include "rectangle.hpp"

Rectangle::Rectangle(sf::Vector2f position, sf::Color color, sf::RectangleShape& shape):
	Entity(position, shape, color)
{}

void Rectangle::update(sf::RenderWindow& window) {
	shape.setPosition(position);
}