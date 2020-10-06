#include "PhysicsObject.h"

void PhysicsObject::applyGravity(float deltaTime)
{
	if (isEnabled()) getRigidBody()->acceleration.y += GRAVITY * deltaTime;
}
