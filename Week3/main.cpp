#include <iostream>
#include <memory>
#include <string>
#include <fstream>
#include <array>

#include <SFML/Graphics.hpp>

#include "exceptions.hpp"
#include "drawable.hpp"
#include "ball.hpp"
#include "rectangle.hpp"
#include "picture.hpp"

// >> Vector
std::ifstream & operator>>(std::ifstream & input, sf::Vector2f & rhs) {
    char c;
    if (!(input >> c)) { throw endOfFile(); }
    if (c != '(') { throw invalidPosition(c); }

    if (!(input >> rhs.x)) {
        input.clear();
        char err;
        input >> err;
        std::cout << err << std::endl;
        throw invalidValue("x position", err);
    }

    if (!(input >> c)) {
        throw endOfFile();
    }

    if (!(input >> rhs.y)) {
        input.clear();
        char err;
        input >> err;
        throw invalidValue("y position", err);
    }

    if (!(input >> c)) {
        throw endOfFile();
    }

    if (c != ')') { throw invalidPosition(c); }

    return input;
};

// >> sf::Color
std::ifstream & operator>>(std::ifstream & input, sf::Color & rhs) {
    // Color by name
    std::string s;
    input >> s;
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
    for (auto const & color : colors) {
        if (color.name == s) {
            rhs = color.color;
            return input;
        }
    }

    throw unknownColor(s);
};
    

std::unique_ptr<Drawable> screen_object_read(std::ifstream & input) {
    sf::Vector2f position;
    std::string name;
    sf::Color color;
    input >> position >> name;
    input >> color;

    if (name == "BALL") {
        float size;
        input >> size;
        return std::make_unique<Ball>(position, color, sf::CircleShape{size});
    } else if (name == "RECTANGLE") {
        sf::Vector2f size;
        input >> size;
        return std::make_unique<Rectangle>(position, color, sf::RectangleShape{size});
    } else if (name == "PICTURE") {
        std::string fileName;
        input >> fileName;
        return std::make_unique<Picture>(position, color, fileName);
    } else if (name == "") {
        throw endOfFile();
    }

    throw unknownShape(name);
}


int main(int argc, char *argv[]) {
    std::cout << "Starting application Week 2\n";

    constexpr const float windowWidth = 640.0;
    constexpr const float windowHeight = 480.0;

    sf::RenderWindow window{sf::VideoMode{static_cast<unsigned int>(windowWidth), static_cast<unsigned int>(windowHeight)}, "SFML window"};

    // Load drawables from file
    const std::string fileName = "drawables.txt";
    bool hadError = false;
    std::ifstream input(fileName);
    std::vector<std::unique_ptr<Drawable>> drawables;
    drawables.reserve(10);
    try {
        while (true) {
            drawables.push_back(screen_object_read(input));
        }
    } catch (endOfFile) {
        // do nothing
    } catch (std::exception & problem) {
        std::cout << problem.what() << std::endl;
        hadError = true;
    }


    // Selected
    std::unique_ptr<Drawable>* selected = &drawables[0];

    // Window
    while (window.isOpen()) {
        // clear window
        window.clear(sf::Color(55, 55, 55));

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
            (*selected)->move(sf::Vector2f{0, -1});
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
            (*selected)->move(sf::Vector2f{1, 0});
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
            (*selected)->move(sf::Vector2f{0, 1});
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
            (*selected)->move(sf::Vector2f{-1, 0});
        }

        for (auto& drawable : drawables) {
            // Update
            drawable->update(window);

            int i = 0;
            for (auto& other : drawables) {
                if (drawable != other) {
                    drawable->interact(*other);
                }
            }

            // Select a drawable
            if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)) {
                if (drawable->getBounds().contains(
                    static_cast<float>(sf::Mouse::getPosition(window).x),
                    static_cast<float>(sf::Mouse::getPosition(window).y)
                )) {
                    selected = &drawable;
                }
            }

            // Select logic
            if ((*selected) == drawable) {
                drawable->selected = true;
            } else {
                drawable->selected = false;
            }



            // Render
            drawable->draw(window);
        }
        window.display();

        sf::sleep(sf::milliseconds(20));

        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }
    }

    if (hadError) {
        std::cout << "There was a error while loading drawables, game state will not be saved" << std::endl;
        return 0;
    }

    std::cout << "Saving game state\n";

    std::ofstream out(fileName);
    if (!out) {
        std::cout << "Could not open: " + fileName << std::endl;
    }

    for (const auto& drawable : drawables) {
        drawable->print(out);
        out << std::endl;
    }

    out.close();

    std::cout << "Terminating application\n";
    return 0;
}

