#pragma once

#include "DisplayObject.h"
#include "TextureManager.h"

class Tile : public DisplayObject
{
public:
	Tile(glm::vec2 world_position, glm::vec2 grid_position);
	~Tile();

	//Inherited from DisplayObject
	virtual void draw() override;
	virtual void update(float deltaTime) override;
	virtual void clean() override;

private:
	glm::vec2 m_gridPosition;
};

