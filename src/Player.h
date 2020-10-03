#pragma once
#ifndef __PLAYER__
#define __PLAYER__

#include "Sprite.h"
#include "Label.h"

class Player final : public Sprite
{
private:
	bool m_sprintFlag;
	const float WALK_SPEED = 35.0f;
	const float RUN_SPEED = 50.0f;
	const float WALK_ACCELERATION = 20.0f;
	const float RUN_ACCELERATION = 45.0f;
	glm::vec2 m_targetPosition;

public:
	Player();
	~Player();

	// Life Cycle Methods
	virtual void draw() override;
	virtual void update(float deltaTime) override;
	virtual void clean() override;
	
	//Movement
	float currentAcceleration();
	float currentSpeed();
	void moveLeft();
	void moveRight();
	void moveUp();
	void moveDown();
	void slow();
	void stop();

	//temp
	float checkDistance(GameObject* pGameObject);

	//get/set
	bool GetSprint() { return m_sprintFlag; }
	void SetSprint(bool n) { m_sprintFlag = n; }
	glm::vec2 GetTargetPosition() { return m_targetPosition; }
	void SetTargetPosition(glm::vec2 n) { m_targetPosition = n; }
};

#endif /* defined (__PLAYER__) */