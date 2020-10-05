#include "Grenade.h"
#include "EventManager.h"
#include "TextureManager.h"
#include "Util.h"

Grenade::Grenade()
{
	TextureManager::Instance()->load("../Assets/textures/ThermalDetonator.png", "ThermalDetonator");

	auto size = TextureManager::Instance()->getTextureSize("ThermalDetonator");
	setWidth(size.x);
	setHeight(size.y);

	getTransform()->position = glm::vec2(400.0f, 300.0f);
	getRigidBody()->velocity = glm::vec2(0.0f, 0.0f);
	getRigidBody()->acceleration = glm::vec2(0.0f, 0.0f);
}

void Grenade::draw()
{
	const auto x = getTransform()->position.x;
	const auto y = getTransform()->position.y;

	TextureManager::Instance()->draw("ThermalDetonator", x, y, getWidth(), getHeight(), 0, 255, true);
}

void Grenade::update(float deltaTime)
{
	switch (getGrenadeState()) {
	case FLIGHT:
		//apply acceleration
		applyGravity(deltaTime);

		//update position
		getRigidBody()->velocity += getRigidBody()->acceleration;
		getTransform()->position.x += getRigidBody()->velocity.x * deltaTime * PX_PER_METER;
		getTransform()->position.y += getRigidBody()->velocity.y * deltaTime * PX_PER_METER;

		if (getTransform()->position.y >= getGroundHeight()) {
			getTransform()->position.y = getGroundHeight();
			setGrenadeState(LANDED);
		}
	default:
		break;
	}

	getRigidBody()->acceleration = { 0.0f, 0.0f };
}

void Grenade::clean()
{
}

void Grenade::spawn(glm::vec2 position)
{
	getTransform()->position = position;
	getRigidBody()->acceleration = { 0.0f, 0.0f };
	getRigidBody()->velocity = { 0.0f, 0.0f };
	setGrenadeState(SETUP);
}

void Grenade::launch(glm::vec2 acceleration)
{
	getRigidBody()->acceleration = acceleration;
	setGrenadeState(FLIGHT);
}

float Grenade::checkDistance(GameObject* pGameObject)
{
	return Util::distance(getTransform()->position, pGameObject->getTransform()->position);
}
