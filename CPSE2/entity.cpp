#include "entity.hpp"

Entity::Entity(sf::Vector2f position, sf::Shape& shape, sf::Color color):
	position(position),
	shape(shape),
	color(color)
{
	shape.setFillColor(color);
	shape.setPosition(position);
}

void Entity::draw(sf::RenderWindow & window) const {
	window.draw(shape);
}

void Entity::move(sf::Vector2f delta) {
	position += delta;
}

void Entity::jump(sf::Vector2f target) {
	position = target;
}

void Entity::jump(sf::Vector2i target) {
	jump(sf::Vector2f(
		static_cast< float >(target.x),
		static_cast< float >(target.y)
	));
}

bool Entity::overlaps(const Entity& other) {
	return shape.getGlobalBounds().intersects(other.shape.getGlobalBounds());
}