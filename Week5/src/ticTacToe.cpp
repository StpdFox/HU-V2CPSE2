#include "ticTacToe.hpp"

TicTacToe::TicTacToe(sf::RenderWindow& window) :
	TILE_SIZE(static_cast<float>(window.getSize().y) / ROWS - MARGIN),
	window(window),
	resetButton(
		sf::Vector2f{ window.getSize().x - TILE_SIZE - MARGIN,
		static_cast<float>(window.getSize().y) / 2 - TILE_SIZE},
		TILE_SIZE, TILE_TYPES::EMPTY)
{
	// Load font
	if (!font.loadFromFile("resources/consola.ttf")) {
		std::cout << "Could not load font" << std::endl;
	}

	// Reserve a place for every tile
	grid.reserve(ROWS * COLUMNS);
	for (uint8_t y = 0; y < ROWS; ++y) {
		for (uint8_t x = 0; x < COLUMNS; ++x) {
			sf::Vector2f position{
				x * TILE_SIZE + x * MARGIN + window.getSize().x / 4,
				y * TILE_SIZE + y * MARGIN + MARGIN / 2
			};

			// Place tile in grid
			grid.emplace_back(position, TILE_SIZE, TILE_TYPES::EMPTY);
		}
	}

	// The maximum number of moves is ROWS * COLUMNS d;)
	commands.reserve(ROWS * COLUMNS);

	// Set color of reset button
	resetButton.xShape.setFillColor(sf::Color{ 150, 50, 150 });
	resetButton.oShape.setFillColor(sf::Color{ 50, 50, 150 });

	// We render once to show board state in CLI
	render();
}

void TicTacToe::update() {
	// GUI controls
	// We set mousePressed to prevent mousePressed event from firing multiple times on 1 click
	if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left) && !mousePressed) {
		mousePressed = true;
		onMousePress();
	} else if (!sf::Mouse::isButtonPressed(sf::Mouse::Button::Left) && mousePressed) {
		mousePressed = false;
	}

	// CLI controls
	if (cliEnabled) {
		unsigned int m = 10;
		while (m > 9) { // While m > maximum number of commands
			std::cin >> m;
			--m; // We do m - 1 so players can enter 1 - 9
		}
		if (m == 9) {
			undo();
		} else {
			makeMove(m, turn);
		}
	}
}

void TicTacToe::render() const {
	// We can't use this because we need cli
	/*
	for (const Tile& tile : grid) {
		window.draw(tile.tileShape);
		switch (tile.type) {
		case TILE_TYPES::X:
			window.draw(tile.xShape);
			break;
		case TILE_TYPES::O:
			window.draw(tile.oShape);
			break;
		default:
			break;
		}
	}
	*/

	// Render all tiles in grid
	for (uint8_t y = 0; y < COLUMNS; ++y) {
		for (uint8_t x = 0; x < COLUMNS; ++x) {
			const Tile& tile = grid[x + y * COLUMNS];

			window.draw(tile.tileShape);
			switch (tile.type) {
			case TILE_TYPES::EMPTY:
				std::cout << '-';
				break;
			case TILE_TYPES::X:
				std::cout << 'X';
				window.draw(tile.xShape);
				break;
			case TILE_TYPES::O:
				std::cout << 'O';
				window.draw(tile.oShape);
				break;
			default:
				break;
			}
			std::cout << ' ';
		}
		std::cout << std::endl;
	}
	std::cout << std::endl;

	// Render reset button
	window.draw(resetButton.xShape);
	window.draw(resetButton.oShape);

	// Text

	sf::Text text;
	text.setFont(font);
	text.setFillColor(sf::Color{ 0, 0 ,0 });
	text.setCharacterSize(24);
	float x = MARGIN;
	float y = MARGIN;

	// Display commands
	for (uint8_t i = 0; i < commands.size(); ++i) {
		const auto& command = commands[i];

		std::string str = "Command: tile ";
		str += std::to_string(static_cast<int>(command.index));
		str += " to ";
		str += (command.tile == TILE_TYPES::X) ? "X" : "O";
		text.setString(str);
		text.setPosition(sf::Vector2f{ x, y + 25 * i });

		window.draw(text);
	}

	// Display status
	text.setPosition(sf::Vector2f{ x, y + 25 * commands.size() });
	if (winner == TILE_TYPES::EMPTY && commands.size() != ROWS * COLUMNS) {
		std::cout << ((turn == TILE_TYPES::X) ? 'X' : 'O') << "'s move (1 - 9) or 10 to undo: " << std::endl;
		text.setString((turn == TILE_TYPES::X) ? "X's turn" : "O's turn");
	}
	else if (winner == TILE_TYPES::EMPTY && commands.size() == ROWS * COLUMNS) {
		std::cout << "Draw!" << std::endl;
		text.setString("Draw!");
	}
	else {
		std::cout << ((winner == TILE_TYPES::X) ? 'X' : 'O') << " wins!" << std::endl;
		text.setString((winner == TILE_TYPES::X) ? "X wins!" : "O wins!");
	}
	window.draw(text);
}

TILE_TYPES TicTacToe::checkWinner() {
	// NOTE: This should be doable with a for loop :P

		// Horizontal
	if (grid[0].type != TILE_TYPES::EMPTY && grid[0].type == grid[1].type && grid[1].type == grid[2].type) {
		return grid[0].type;
	}
	if (grid[3].type != TILE_TYPES::EMPTY && grid[3].type == grid[4].type && grid[4].type == grid[5].type) {
		return grid[3].type;
	}
	if (grid[6].type != TILE_TYPES::EMPTY && grid[6].type == grid[7].type && grid[7].type == grid[8].type) {
		return grid[6].type;
	}

	// Vertical
	if (grid[0].type != TILE_TYPES::EMPTY && grid[0].type == grid[3].type && grid[3].type == grid[6].type) {
		return grid[0].type;
	}
	if (grid[1].type != TILE_TYPES::EMPTY && grid[1].type == grid[4].type && grid[4].type == grid[7].type) {
		return grid[1].type;
	}
	if (grid[2].type != TILE_TYPES::EMPTY && grid[2].type == grid[5].type && grid[5].type == grid[8].type) {
		return grid[2].type;
	}

	// Diagonal
	if (grid[0].type != TILE_TYPES::EMPTY && grid[0].type == grid[4].type && grid[4].type == grid[8].type) {
		return grid[0].type;
	}
	if (grid[2].type != TILE_TYPES::EMPTY && grid[2].type == grid[4].type && grid[4].type == grid[6].type) {
		return grid[2].type;
	}

	return TILE_TYPES::EMPTY;
}

void TicTacToe::onMousePress() {
	sf::Vector2f mousePos{
		static_cast<float>(sf::Mouse::getPosition(window).x),
		static_cast<float>(sf::Mouse::getPosition(window).y)
	};

	// collision
	for (uint8_t i = 0; i < grid.size(); ++i) {
		auto& tile = grid[i];
		// If a empty tile was clicked
		if (tile.tileShape.getGlobalBounds().contains(mousePos)) {
			makeMove(i, turn);
		}
	}

	// if reset button is pressed
	if (resetButton.tileShape.getGlobalBounds().contains(mousePos)) {
		undo();
	}
}

void TicTacToe::resetGrid() {
	// Clear grid
	for (auto& tile : grid) {
		tile.type = TILE_TYPES::EMPTY;
	}

	// reset turn
	turn = TILE_TYPES::X;

	// No winner
	winner = TILE_TYPES::EMPTY;
}

void TicTacToe::undo() {
	if (commands.size() > 0) {
		resetGrid();

		commands.pop_back();

		// Run all commands
		for (const auto& command : commands) {
			setTile(command.index, command.tile);
		}
	}
}

void TicTacToe::makeMove(uint8_t index, TILE_TYPES type) {
	if (winner == TILE_TYPES::EMPTY && grid[index].type == TILE_TYPES::EMPTY) {
		setTile(index, type); // Set tile
		commands.emplace_back(index, type); // Add move to commands

		// Check if there is a winner
		winner = checkWinner();
	}
}

void TicTacToe::setTile(uint8_t index, TILE_TYPES type) {
	grid[index].type = type;
	turn = getOppositeType(turn); // Give turn to the other
}

