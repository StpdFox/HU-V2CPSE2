#pragma once
#include <SFML/Graphics.hpp>
#include "entity.hpp"

class Ball: public Entity {
private:
	static const uint8_t speed = 6;
	sf::Vector2f velocity;
public:
	Ball(sf::Vector2f position, sf::Color color, sf::CircleShape& shape);

	void update(sf::RenderWindow & window) override;
	void interact(const Entity& other) override;
};