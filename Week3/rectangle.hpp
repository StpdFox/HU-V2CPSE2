#pragma once

#include <fstream>
#include <SFML\Graphics.hpp>
#include "drawable.hpp"

class Rectangle : public Drawable {
private:
    sf::RectangleShape shape;
public:
    Rectangle(sf::Vector2f position, sf::Color color, sf::RectangleShape _shape);
    sf::FloatRect getBounds() const override {
        return shape.getGlobalBounds();
    };

    void update(sf::RenderWindow& window) override;
    void draw(sf::RenderWindow & window) override;
    void print(std::ofstream& stream) const override;
};