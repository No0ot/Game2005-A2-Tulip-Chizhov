#include "Player.h"
#include "EventManager.h"
#include "TextureManager.h"
#include "Util.h"

Player::Player()
{
	TextureManager::Instance()->load("../Assets/textures/Wookie.png", "wookie");
	
	auto size = TextureManager::Instance()->getTextureSize("wookie");
	setWidth(100);
	setHeight(100);

	getTransform()->position = glm::vec2(400.0f, 300.0f);
	getRigidBody()->velocity = glm::vec2(0.0f, 0.0f);
	getRigidBody()->acceleration = glm::vec2(0.0f, 0.0f);
	getRigidBody()->isColliding = false;
	setType(PLAYER);
	SetSprint(false);

	//Ramp Set up
	rampWidth = 4.0f;
	rampHeight = 3.0f;

	groundFriction = -0.42f;
	rampFriction = -1.00f;
}

Player::~Player()
= default;

void Player::draw()
{
	// alias for x and y
	const auto x = getTransform()->position.x;
	const auto y = getTransform()->position.y;

	//TextureManager::Instance()->draw("wookie", x, y, getWidth(), getHeight(), 0, 255, true, SDL_FLIP_HORIZONTAL);
	glm::vec4 colour = {0.0f, 0.0f, 1.0f, 1.0f};

	for (int i = 0; i < 50; i += 2) {
		Util::DrawLine({ Rise.x, Rise.y + i }, { Run.x, Run.y + i }, colour);
	}
}

void Player::update(float deltaTime)
{
	/*glm::vec2 pos = getTransform()->position;

	getRigidBody()->velocity += Util::limitMagnitude(getRigidBody()->acceleration, currentSpeed());

	pos.x += getRigidBody()->velocity.x * deltaTime;
	pos.y += getRigidBody()->velocity.y * deltaTime;

	getTransform()->position = pos;
	slow();
	SetSprint(false);*/
}

void Player::clean()
{

}

void Player::spawn(glm::vec2 position, int width, int height) //accepts height in meters
{
	Origin = position;
	rampWidth = width;
	rampHeight = height;
	BuildRamp();
}

float Player::currentAcceleration()
{
	return m_sprintFlag ? RUN_ACCELERATION : WALK_ACCELERATION;
}

float Player::currentSpeed()
{
	return m_sprintFlag ? RUN_SPEED : WALK_SPEED;
}

void Player::moveLeft() {
	getRigidBody()->acceleration.x -= currentAcceleration();
}

void Player::moveRight() {
	getRigidBody()->acceleration.x += currentAcceleration();
}

void Player::moveUp() {
	getRigidBody()->acceleration.y -= currentAcceleration();
}

void Player::moveDown() {
	getRigidBody()->acceleration.y += currentAcceleration();
}

void Player::slow()
{
	getRigidBody()->acceleration *= 0.5f;
	getRigidBody()->velocity *= 0.8f;
}

void Player::stop()
{
	getRigidBody()->acceleration = { 0.0f, 0.0f };
	getRigidBody()->velocity = { 0.0f, 0.0f };
}

float Player::checkDistance(GameObject* pGameObject) {
	return Util::distance(getTransform()->position, pGameObject->getTransform()->position);
}

void Player::BuildRamp()
{
	Rise = { Origin.x, Origin.y - rampHeight * PX_PER_METER };
	Run = { Origin.x + rampWidth * PX_PER_METER, Origin.y };
}

float Player::GetCurrentHeight(float x)
{
	if (x < Origin.x) return Rise.y;
	if (x > Run.x) return Origin.y;
	return Rise.y + (rampHeight / rampWidth) * (x - Origin.x);
}

float Player::GetCurrentNormal(float x)
{
	if (x < Origin.x || x > Run.x) return 0.0f;
	return atan(rampHeight / rampWidth);
}


