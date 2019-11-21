#pragma once

#include <fstream>
#include <SFML\Graphics.hpp>

class Drawable {
protected:
    sf::Vector2f position;
    sf::Color color;
    sf::Color selectedColor;
public:
    bool selected = false;
protected:
    std::string getColorName(sf::Color color) const;
public:
    Drawable(sf::Vector2f position, sf::Color color);

    virtual void draw(sf::RenderWindow & window) = 0;
    virtual void update(sf::RenderWindow & window) = 0;

    virtual void move(sf::Vector2f delta);
    virtual void jump(sf::Vector2f target);
    virtual void jump(sf::Vector2i target);

    virtual void interact(const Drawable& other) {};
    virtual sf::FloatRect getBounds() const = 0;
    virtual void print(std::ofstream& stream) const = 0;
};

/*
std::ofstream& operator<<(std::ofstream& stream, const Rectangle& draw) {
    draw.print(stream);
    return stream;
};
*/
