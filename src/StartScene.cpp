#include "StartScene.h"
#include <algorithm>
#include "Game.h"
#include "glm/gtx/string_cast.hpp"
#include "EventManager.h"

StartScene::StartScene()
{
	StartScene::start();
}

StartScene::~StartScene()
= default;

void StartScene::draw()
{
	drawDisplayList();
}

void StartScene::update(float deltaTime)
{
	updateDisplayList(deltaTime);
}

void StartScene::clean()
{
	removeAllChildren();
}

void StartScene::handleEvents(float deltaTime)
{
	EventManager::Instance().update();

	// Keyboard Events
	if(EventManager::Instance().isKeyDown(SDL_SCANCODE_ESCAPE))
	{
		TheGame::Instance()->quit();
	}

	if(EventManager::Instance().isKeyDown(SDL_SCANCODE_1))
	{
		TheGame::Instance()->changeSceneState(PLAY_SCENE);
	}
}

void StartScene::start()
{
	const SDL_Color blue = { 0, 0, 255, 255 };
	const SDL_Color red = { 255, 0, 0, 255 };
	m_pStartLabel = new Label("GAME2005 Assignment 1", "Consolas", 80, blue, glm::vec2(Config::SCREEN_WIDTH / 2, 40.0f));
	m_pStartLabel->setParent(this);
	addChild(m_pStartLabel);

	m_pInstructionsLabel = new Label("Press \"1\" to Play", "Consolas", 40, blue, glm::vec2(Config::SCREEN_WIDTH / 2, 120.0f));
	m_pInstructionsLabel->setParent(this);
	addChild(m_pInstructionsLabel);

	m_pChrisLabel = new Label("Chris Tulip - 100 818 050", "Consolas" , 40, red, glm::vec2(Config::SCREEN_WIDTH / 1.3, 300.0f));
	m_pChrisLabel->setParent(this);
	addChild(m_pChrisLabel);

	m_pAndreyLabel = new Label("Andrey Chizhov - 101 255 069", "Consolas", 40, red, glm::vec2(Config::SCREEN_WIDTH / 4.2, 300.0f));
	m_pAndreyLabel->setParent(this);
	addChild(m_pAndreyLabel);


	m_pPlayer = new Player();
	m_pPlayer->getTransform()->position = glm::vec2(Config::SCREEN_WIDTH / 2, 300.0f);
	addChild(m_pPlayer); 

	//// Start Button
	//m_pStartButton = new Button();
	//m_pStartButton->getTransform()->position = glm::vec2(400.0f, 400.0f); 

	//m_pStartButton->addEventListener(CLICK, [&]()-> void
	//{
	//	m_pStartButton->setActive(false);
	//	TheGame::Instance()->changeSceneState(PLAY_SCENE);
	//});
	//
	//m_pStartButton->addEventListener(MOUSE_OVER, [&]()->void
	//{
	//	m_pStartButton->setAlpha(128);
	//});

	//m_pStartButton->addEventListener(MOUSE_OUT, [&]()->void
	//{
	//	m_pStartButton->setAlpha(255);
	//});
	//addChild(m_pStartButton);
}

