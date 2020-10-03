#pragma once
#ifndef __START_SCENE__
#define __START_SCENE__

#include "Scene.h"
#include "Label.h"
#include "ship.h"
#include "Button.h"

class StartScene final : public Scene
{
public:
	StartScene();
	~StartScene();

	// Inherited via Scene
	virtual void draw() override;
	virtual void update(float deltaTime) override;
	virtual void clean() override;
	virtual void handleEvents(float deltaTime) override;
	virtual void start() override;
	
private:
	Label* m_pStartLabel{};
	Label* m_pInstructionsLabel{};
	Label* m_pChrisLabel{};
	Label* m_pAndreyLabel{};

	Ship* m_pShip{};

	Button* m_pStartButton;
};

#endif /* defined (__START_SCENE__) */