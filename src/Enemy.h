#pragma once
#ifndef __ENEMY__
#define __ENEMY__

#include "Sprite.h"

enum SimpleEnemyBehavior {
	IDLE,
	WANDERING,
	SEEKING
};

class Enemy : public Sprite
{
private:
	const float SPEED = 40.0f;
	glm::vec2 m_targetPosition;
	SimpleEnemyBehavior m_behaviorState;

public:
	Enemy();
	~Enemy();

	// Life Cycle Methods
	virtual void draw() override;
	virtual void update(float deltaTime) override;
	virtual void clean() override;

	void spawn(glm::vec2 position);
	void seek();

	//get/set
	glm::vec2 getTargetPosition() { return m_targetPosition; }
	void setTargetPosition(glm::vec2 n) { m_targetPosition = n; }
	SimpleEnemyBehavior getBehaviorState() { return m_behaviorState; }
	void setBehaviorState(SimpleEnemyBehavior n) { m_behaviorState = n; }
};

#endif


