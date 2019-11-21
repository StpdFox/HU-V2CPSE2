#include "tile.hpp"

Tile::Tile(sf::Vector2f position, float size,  TILE_TYPES type):
	fillColor(sf::Color{ 200, 50, 50 }),
	tileShape(sf::Vector2f{ size, size }),
	xShape(sf::Vector2f{ size - OFFSET, size - OFFSET }),
	oShape(size / 2 - OFFSET / 2),
	type(type)
{
	tileShape.setPosition(position);
	xShape.setFillColor(fillColor);
	xShape.setPosition(position.x + OFFSET / 2, position.y + OFFSET / 2);
	oShape.setFillColor(fillColor);
	oShape.setPosition(position.x + OFFSET / 2, position.y + OFFSET / 2);
}
