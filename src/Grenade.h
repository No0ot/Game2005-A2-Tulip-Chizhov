#pragma once
#ifndef __GRENADE__
#define __GRENADE__

#include "PhysicsObject.h"

enum GrenadeState {
	SETUP,
	FLIGHT,
	LANDED
};

class Grenade : public PhysicsObject
{
private:
	GrenadeState m_state;
	float m_groundHeight, m_contactRadius = 5.0f;
public:
	Grenade();
	~Grenade() = default;

	void draw();
	void update(float deltaTime);
	void clean();

	void spawn(glm::vec2 position);
	void launch(glm::vec2 acceleration);

	float checkDistance(GameObject* pGameObject);

	GrenadeState getGrenadeState() { return m_state; }
	void setGrenadeState(GrenadeState n) { m_state = n; }
	float getGroundHeight() { return m_groundHeight; }
	void setGroundHeight(float n) { m_groundHeight = n; }
	float getContactRadius() { return m_contactRadius; }
	void setContactRadius(float n) { m_contactRadius = n; }

	float m_angleRotation;
};
#endif 