#include "Grenade.h"
#include "EventManager.h"
#include "TextureManager.h"
#include "Util.h"
#include "Player.h"
#include "Config.h"

Grenade::Grenade()
{
	TextureManager::Instance()->load("../Assets/textures/box.png", "box");

	auto size = TextureManager::Instance()->getTextureSize("box");
	setWidth(size.x/5.0f);
	setHeight(size.y/5.0f);
	m_mass = 12.8;

	getTransform()->position = glm::vec2(0.0f, 0.0f);
	getRigidBody()->velocity = glm::vec2(0.0f, 0.0f);
	getRigidBody()->acceleration = glm::vec2(0.0f, 0.0f);

	slope = nullptr;
	setGrenadeState(SETUP);
	rotation = 0.0f;
}

void Grenade::draw()
{
	const auto x = getTransform()->position.x;
	const auto y = getTransform()->position.y;
	TextureManager::Instance()->draw("box", x, y, getWidth(), getHeight(), Util::Rad2Deg*rotation, 255, true);

	/*glm::vec4 green {0.0f,1.0f,0.0f,1.0f};
	Util::DrawCircle(getTransform()->position, getWidth() /2, green);*/
}

void Grenade::update(float deltaTime)
{
	assert(slope != nullptr);
	rotation = slope->GetCurrentNormal(Ground.x);
	switch (getGrenadeState()) {
	case SETUP:
		break;
	case INCLINE:
		getRigidBody()->acceleration.x = slope->rampFriction * GRAVITY * PX_PER_METER * sin(rotation) * deltaTime;
		getRigidBody()->velocity.x += getRigidBody()->acceleration.x;
		Ground.x += getRigidBody()->velocity.x * deltaTime;
		Ground.y = slope->GetCurrentHeight(Ground.x);
		CalculatePosition();
		if (Ground.x > slope->Run.x) setGrenadeState(FLAT);
		break;
	case FLAT:
		getRigidBody()->acceleration.x = -slope->groundFriction * GRAVITY * PX_PER_METER * deltaTime;
		getRigidBody()->velocity.x += getRigidBody()->acceleration.x;
		Ground.x += getRigidBody()->velocity.x * deltaTime;
		Ground.y = slope->GetCurrentHeight(Ground.x);
		CalculatePosition();
		if (getRigidBody()->velocity.x <= 0) {
			getRigidBody()->velocity.x = 0.0f;
			setGrenadeState(STOP);
		}
		break;
	case STOP:
		break;
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
	Ground = position;
	CalculatePosition();
	getRigidBody()->acceleration = { 0.0f, 0.0f };
	getRigidBody()->velocity = { 0.0f, 0.0f };
	setGrenadeState(SETUP);
}

void Grenade::launch()
{
	setGrenadeState(INCLINE);
}

float Grenade::checkDistance(GameObject* pGameObject)
{
	return Util::distance(getTransform()->position, pGameObject->getTransform()->position);
}

void Grenade::CalculatePosition()
{
	getTransform()->position = Ground + (Util::rotateVector({ 0, -1 }, rotation) * (float)getHeight() * 0.5f);
}
