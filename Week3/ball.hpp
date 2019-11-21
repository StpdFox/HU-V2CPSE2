#pragma once

#include <SFML/Graphics.hpp>
#include "drawable.hpp"

class Ball : public Drawable {
private:
    static const uint8_t speed = 6;
    sf::Vector2f velocity;
    sf::CircleShape shape;

public:
    Ball(sf::Vector2f position, sf::Color color, sf::CircleShape _shape);
    sf::FloatRect getBounds() const override {
        return shape.getGlobalBounds();
    };

    void update(sf::RenderWindow & window) override;
    void draw(sf::RenderWindow & window) override;
    void interact(const Drawable& other) override;
    void print(std::ofstream& stream) const override;
};