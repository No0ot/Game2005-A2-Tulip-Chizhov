#pragma once
#ifndef __PHYSICS_OBJECT__
#define __PHYSICS_OBJECT__

#include "Sprite.h"
#include "Label.h"

class PhysicsObject : public DisplayObject
{
private:
	const float gravity = 9.8f;

public:
	PhysicsObject() = default;
	~PhysicsObject() = default;

	// Life Cycle Methods
	virtual void draw() = 0;
	virtual void update(float deltaTime) = 0;
	virtual void clean() = 0;

	virtual void spawn(glm::vec2 position) = 0;
	virtual void launch() = 0;

	//Movement
	void applyGravity(float deltaTime);
	void applyNormalForce(float deltaTime);

	
	float m_mass;

	//get/set
};
#endif 