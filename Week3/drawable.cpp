#include "drawable.hpp"

Drawable::Drawable(sf::Vector2f position, sf::Color color) :
    position(position),
    color(color),
    selectedColor(sf::Color(255, 0, 100))
{}

std::string Drawable::getColorName(sf::Color color) const {
    const struct { const char * name; sf::Color color; } colors[]{
        {"black",   sf::Color::Black},
        {"blue",    sf::Color::Blue},
        {"cyan",    sf::Color::Cyan},
        {"green",   sf::Color::Green},
        {"magenta", sf::Color::Magenta},
        {"red",     sf::Color::Red},
        {"white",   sf::Color::White},
        {"yellow",  sf::Color::Yellow}
    };
    for (auto const & c : colors) {
        if (color == c.color) {
            return c.name;
        }
    }

    return "UNKNOWN_COLOR";
}

void Drawable::move(sf::Vector2f delta) {
    position += delta;
}

void Drawable::jump(sf::Vector2f target) {
    position = target;
}

void Drawable::jump(sf::Vector2i target) {
    jump(sf::Vector2f(
        static_cast< float >(target.x),
        static_cast< float >(target.y)
    ));
}