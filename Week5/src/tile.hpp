#ifndef TILE_HPP
#define TILE_HPP

#include <SFML\Graphics.hpp>
#include "tileTypes.hpp"

/**
* @class Tile
* @file tile.hpp
* @brief Tile class use to display the TicTacToe grid
*
*/
class Tile {
private:
	static constexpr const float OFFSET = 20;
	sf::Color fillColor;
public:
	sf::RectangleShape tileShape;
	sf::RectangleShape xShape;
	sf::CircleShape oShape;
	TILE_TYPES type;
public:
	/**
	* @brief constructor
	* @param position Position of Tile (on window)
	* @param size Size of Tile
	* @param type Type of Tile (EMPTY by default)
	*/
	Tile(sf::Vector2f position, float size, TILE_TYPES type = TILE_TYPES::EMPTY);
};

#endif // TILE_HPP

