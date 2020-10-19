#include "Grenade.h"
#include "EventManager.h"
#include "TextureManager.h"
#include "Util.h"

Grenade::Grenade()
{
	TextureManager::Instance()->load("../Assets/textures/square.png", "square");

	auto size = TextureManager::Instance()->getTextureSize("square");
	setWidth(size.x);
	setHeight(size.y);
	m_mass = 12.8;

	getTransform()->position = glm::vec2(400.0f, 300.0f);
	getRigidBody()->velocity = glm::vec2(0.0f, 0.0f);
	getRigidBody()->acceleration = glm::vec2(0.0f, 0.0f);
}

void Grenade::draw()
{
	const auto x = getTransform()->position.x;
	const auto y = getTransform()->position.y;
	//if(getGrenadeState() != SETUP)
		TextureManager::Instance()->draw("square", x, y, getWidth(), getHeight(), m_angleRotation, 255, true);

	glm::vec4 green {0.0f,1.0f,0.0f,1.0f};
	Util::DrawCircle(getTransform()->position, getWidth() /2, green);
}

void Grenade::update(float deltaTime)
{
	switch (getGrenadeState()) {
	case FLIGHT:
		//apply acceleration
		applyGravity(deltaTime);
		getRigidBody()->acceleration.x = (9.8 * sin(-m_inclineAngle)) / PX_PER_METER;
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
