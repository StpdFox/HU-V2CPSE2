#include <array>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>

#include "ticTacToe.hpp"

int main() {
	sf::RenderWindow window(sf::VideoMode(1280, 720), "Tic Tac Toe");
	sf::Event event;

	TicTacToe game{ window };

	while (window.isOpen()) {
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed) {
				window.close();
			}
		}

		window.clear(sf::Color(200, 200, 200));
		game.update();
		game.render();
		window.display();

		sf::sleep(sf::milliseconds(100)); // Sleep a bit
	}

    return 0;
}
