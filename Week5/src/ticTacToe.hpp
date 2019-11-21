#ifndef TIC_TAC_TOE_HPP
#define TIC_TAC_TOE_HPP

#include <assert.h>
#include <iostream>
#include <vector>
#include <SFML\Graphics.hpp>
#include "command.hpp"
#include "tile.hpp"
#include "tileTypes.hpp"

/**
* @class TicTacToe
* @file ticTacToe.hpp
* @brief Main game logic for Tic Tac Toe game
*
*/
class TicTacToe {
private:
	static constexpr const uint8_t ROWS = 3;
	static constexpr const uint8_t COLUMNS = 3;
	static constexpr const uint8_t MARGIN = 5;
	const float TILE_SIZE;
	sf::RenderWindow& window;

	sf::Font font;
	std::vector<Tile> grid; // We save the 2d grid in a 1d vector
	Tile resetButton;

	std::vector<Command> commands;
	bool mousePressed = false;
	bool cliEnabled = false;
	TILE_TYPES turn = TILE_TYPES::X;
	TILE_TYPES winner = TILE_TYPES::EMPTY;

public:
	/**
	* @brief Constructor
	* @param window The window used for displaying the grid
	*/
	TicTacToe(sf::RenderWindow& window);

	/**
	* @brief Updates the game
	*
	* @details
	* Handles all input events for the game and updates the grid
	*/
	void update();
	/**
	* @brief Renders the game
	*
	* @details
	* Renders grid both for CLI and for GUI
	*/
	void render() const;

private:/**
	* @brief returns opposite of given type
	* @param type the type
	* @return opposite of given type
	*/
	inline TILE_TYPES getOppositeType(TILE_TYPES type) const {
		assert(type != TILE_TYPES::EMPTY);
		return (type == TILE_TYPES::X) ? TILE_TYPES::O : TILE_TYPES::X;
	};

	/**
	* @brief Checks if current grid state has a winner
	* @return The winner, EMPTY returned if no winner
	*
	* @details
	* Checks if there is a winner according to the TicTacToe rules
	*/
	TILE_TYPES checkWinner();
	/**
	* @brief Deals with logic for mouse press
	*
	* @details
	* makesMove if tile is clicked or undo's if undoButton is clicked
	*/
	void onMousePress();
	/**
	* @brief Resets grid state
	*
	* @details
	* Makes every tile empty and sets turn and winner to default values
	*/
	void resetGrid();
	/**
	* @brief Undo's last move
	*
	* @details
	* Replays game till last command
	*/
	void undo();
	/**
	* @brief sets tile (using the setTile method) and adds the move to commands
	* @param index The index in grid
	* @param type The type that the tile needs to be
	*/
	void makeMove(uint8_t index, TILE_TYPES type);

	/**
	* @brief sets tile in grid
	* @param index The index in grid
	* @param type The type that the tile needs to be
	*/
	void setTile(uint8_t index, TILE_TYPES type);
};

#endif // TIC_TAC_TOE_HPP
