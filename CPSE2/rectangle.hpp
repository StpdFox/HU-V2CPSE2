#pragma once

#include <SFML\Graphics.hpp>
#include "entity.hpp"

class Rectangle: public Entity {
public:
	Rectangle(sf::Vector2f position, sf::Color color, sf::RectangleShape& shape);

	void update(sf::RenderWindow& window) override;
};

