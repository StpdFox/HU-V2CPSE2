#pragma once

#include <SFML\Graphics.hpp>
#include "drawable.hpp"

class Picture : public Drawable {
private:
    sf::Texture text;
    sf::Sprite sprite;
    std::string filename;

public:
    Picture(sf::Vector2f position, sf::Color color, const std::string& filename);
    virtual sf::FloatRect getBounds() const {
        return sf::FloatRect{position, sf::Vector2f(
            static_cast<float>(text.getSize().x),
            static_cast<float>(text.getSize().y)
        )};
    };

    virtual void update(sf::RenderWindow & window);
    virtual void draw(sf::RenderWindow & window);
    void print(std::ofstream& stream) const;
};