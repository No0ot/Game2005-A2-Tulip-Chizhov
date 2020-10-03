#include "Enemy.h"
#include "TextureManager.h"
#include "Util.h"

Enemy::Enemy() {
	TextureManager::Instance()->load("../Assets/textures/Stormtrooper.png", "stormtrooper");

	auto size = TextureManager::Instance()->getTextureSize("stormtrooper");
	setWidth(size.x);
	setHeight(size.y);

	getTransform()->position = glm::vec2(700.0f, 300.0f);
	getRigidBody()->velocity = glm::vec2(0.0f, 0.0f);
	getRigidBody()->acceleration = glm::vec2(0.0f, 0.0f);
	getRigidBody()->isColliding = false;
	setType(ENEMY);
}

Enemy::~Enemy()
= default;

void Enemy::draw() {
	// alias for x and y
	const auto x = getTransform()->position.x;
	const auto y = getTransform()->position.y;

	TextureManager::Instance()->draw("stormtrooper", x, y, 0, 255, true);
}

void Enemy::update(float deltaTime) {
	switch (getBehaviorState()) {
	case WANDERING:
		break;
	case SEEKING:
		break;
	default:
		break;
	}
}

void Enemy::clean() {

}

void Enemy::spawn(glm::vec2 position)
{
	getTransform()->position = position;
}

void Enemy::seek()
{
	getRigidBody()->acceleration += Util::normalize(m_targetPosition - getTransform()->position) * SPEED;
}
