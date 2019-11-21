#include "ball.hpp"
#include <math.h>

Ball::Ball(sf::Vector2f position, sf::Color color, sf::CircleShape _shape) :
    Drawable(position, color),
    velocity(speed, speed),
    shape(_shape)
{
    shape.setPosition(position);
    shape.setFillColor(color);
}

void Ball::update(sf::RenderWindow & window) {
    move(velocity);
    shape.setPosition(position);
}

void Ball::draw(sf::RenderWindow & window) {
    sf::Color tmp = color;
    if (selected) {
        shape.setFillColor(selectedColor);
    }
    window.draw(shape);
    if (shape.getFillColor() != tmp) {
        shape.setFillColor(tmp);
    }
}

void Ball::interact(const Drawable& other) {
    if (getBounds().intersects(other.getBounds())) {
        float angle = atan2f(velocity.y, velocity.x) - 3.141592654f / 2;

        velocity.x = cos(angle) * speed;
        velocity.y = sin(angle) * speed;
        move(velocity); // Move out of entity
    }
};

#include <iostream>

void Ball::print(std::ofstream& stream) const {
    // (50,60) BALL blue 10
    stream << "(" << position.x << ", " << position.y << ")"; // Position
    stream << " BALL "; // Name
    stream << getColorName(color) << " "; // Color
    stream <<  shape.getRadius(); // Size
}
