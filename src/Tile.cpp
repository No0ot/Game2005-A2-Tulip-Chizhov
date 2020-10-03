#include "Tile.h"
#include "Game.h"

Tile::Tile(glm::vec2 world_position, glm::vec2 grid_position)
{
	TextureManager::Instance()->load("../Assets/textures/tile.png", "tile");
	auto size = TextureManager::Instance()->getTextureSize("tile");

	setWidth(size.x);
	setHeight(size.y);

	getTransform()->position = world_position;
	m_gridPosition = grid_position;
}

Tile::~Tile()
{
}

void Tile::draw()
{
	const auto x = getTransform()->position.x;
	const auto y = getTransform()->position.y;

	TextureManager::Instance()->draw("tile", x, y, 0, 255, true);
}

void Tile::update(float deltaTime)
{
}

void Tile::clean()
{
}
