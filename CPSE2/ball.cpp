#include "ball.hpp"
#include <math.h>

Ball::Ball(sf::Vector2f position, sf::Color color, sf::CircleShape& shape):
	Entity(position, shape, color),
	velocity(speed, speed)
{}

void Ball::update(sf::RenderWindow & window) {
	move(velocity);
	shape.setPosition(position);
}

void Ball::interact(const Entity& other) {
	if (overlaps(other)) {
		float angle = atan2f(velocity.y, velocity.x) - 3.141592654f / 2;

		velocity.x = cos(angle) * speed;
		velocity.y = sin(angle) * speed;
		move(velocity); // Move out of entity
	}
};
