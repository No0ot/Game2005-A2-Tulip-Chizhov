#pragma once
#ifndef __PLAY_SCENE__
#define __PLAY_SCENE__

#include "Scene.h"
#include "Plane.h"
#include "Player.h"
#include "Button.h"
#include "Enemy.h"
#include "Grenade.h"
#include "Tile.h"
#include <cassert>

class PlayScene : public Scene
{
public:
	PlayScene();
	~PlayScene();

	// Scene LifeCycle Functions
	virtual void draw() override;
	virtual void update(float deltaTime) override;
	virtual void clean() override;
	virtual void handleEvents(float deltaTime) override;
	virtual void start() override;

	void calculateAngle();
	void calculateIncline();

	void resetSim();
	void reset();
	void launch();

	//scene getters
	Player* getPlayer() {
		assert(m_pPlayer != nullptr);
		return m_pPlayer;
	}

	Enemy* getEnemy() {
		assert(m_pEnemy != nullptr);
		return m_pEnemy;
	}

	Grenade* getGrenade() {
		assert(m_pGrenade != nullptr);
		return m_pGrenade;
	}
private:
	// IMGUI Function
	void GUI_Function() ;

	void m_buildGrid();

	bool m_inputValid;
	glm::vec2 m_mousePosition;
	glm::vec2 m_launchVector;
	float m_inclineAngle;
	float m_launchAngle = 15.9f;
	float m_launchSpeed, m_launchSpeedDefault = 0, m_launchSpeedLowest = 5, m_launchSpeedHighest = 155;
	float m_groundLevel = 800.0f;

	float m_distanceToTarget = 485.0f;

	std::vector<Tile*> m_pGrid;
	Player* m_pPlayer;
	Enemy* m_pEnemy;
	Grenade* m_pGrenade;

	Label* m_pDistanceLabel;
	Label* m_pVelocityLabel;
	Label* m_pAngleLabel;
	Label* m_pScaleLabel;

	Button* m_pBackButton;
	Button* m_pNextButton;
};

#endif /* defined (__PLAY_SCENE__) */