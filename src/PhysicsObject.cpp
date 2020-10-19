#include "PhysicsObject.h"

void PhysicsObject::applyGravity(float deltaTime)
{
	if (isEnabled()) getRigidBody()->acceleration.y += (GRAVITY * m_mass) * deltaTime;
}

void PhysicsObject::applyNormalForce(float deltaTime)
{

	if (isEnabled()) getRigidBody()->acceleration.y -= ((GRAVITY * m_mass) * deltaTime);
	
}

