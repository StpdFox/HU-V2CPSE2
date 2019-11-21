#ifndef COMMAND_HPP
#define COMMAND_HPP

#include <stdint.h>
#include "tileTypes.hpp"

/**
* @class Command
* @file command.hpp
* @brief Used to save moves for the TicTacToe game
*
*/
class Command {
public:
	uint8_t index;
	TILE_TYPES tile;
public:
	/**
	* @brief Constructor
	* @param index Grid index for tile
	* @param tile The type the tile needs to be
	*/
	Command(uint8_t index, TILE_TYPES tile);
};

#endif // COMMAND_HPP

