#pragma once
#ifndef __PLAY_SCENE__
#define __PLAY_SCENE__

#include "Scene.h"
#include "Plane.h"
#include "Player.h"
#include "Button.h"
#include "Enemy.h"
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

	//scene getters
	Player* getPlayer() {
		assert(m_pPlayer != nullptr);
		return m_pPlayer;
	}

	Enemy* getEnemy() {
		assert(m_pEnemy != nullptr);
		return m_pEnemy;
	}
private:
	glm::vec2 m_mousePosition;
	std::vector<Tile*> m_pGrid;

	Plane* m_pPlaneSprite;
	Player* m_pPlayer;
	Enemy* m_pEnemy;
	Label* m_pDistanceLabel;
	Label* m_pVelocityLabel;

	Button* m_pBackButton;
	Button* m_pNextButton;

	void m_buildGrid();
};

#endif /* defined (__PLAY_SCENE__) */