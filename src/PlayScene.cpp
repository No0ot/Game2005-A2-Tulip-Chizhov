#include "PlayScene.h"
#include "Game.h"
#include "EventManager.h"
#include "Util.h"

PlayScene::PlayScene()
{
	PlayScene::start();
}

PlayScene::~PlayScene()
= default;

void PlayScene::draw()
{
	drawDisplayList();
}

void PlayScene::update(float deltaTime)
{
	updateDisplayList(deltaTime);
	
	switch (m_pGrenade->getGrenadeState()) {
	case SETUP:
		calculateAngle();
		m_pDistanceLabel->setText("Wookie Distance to Trooper = " + std::to_string(m_pPlayer->checkDistance(m_pEnemy) / PX_PER_METER));
		m_pVelocityLabel->setText("Launch Velocity = " + std::to_string(m_launchSpeed) + "m/s");
		m_pAngleLabel->setText("Angle of attack = " + std::to_string(m_launchAngle));
		break;
	case FLIGHT:
		m_pVelocityLabel->setText("Grenade Height = " + std::to_string((m_groundLevel - m_pGrenade->getTransform()->position.y) / PX_PER_METER) + "m");
		break;
	case LANDED:
		if (m_pGrenade->checkDistance(m_pEnemy) <= m_pGrenade->getContactRadius() + m_pEnemy->getWidth() * 0.5f)
			m_pDistanceLabel->setText("Troopers hit");
		else m_pDistanceLabel->setText("LZ " + std::to_string(m_pGrenade->checkDistance(m_pEnemy) / PX_PER_METER) + " meters away from enemy");
		break;
	}
}

void PlayScene::clean()
{
	removeAllChildren();
}

void PlayScene::handleEvents(float deltaTime)
{
	EventManager::Instance().update();
	m_mousePosition = EventManager::Instance().getMousePosition();

	if (EventManager::Instance().getMouseButton(0)) {
		switch (m_pGrenade->getGrenadeState()) {
		case SETUP:
			if (m_inputValid) {
				launch();
				m_inputValid = false;
			}
			break;
		case LANDED:
			if (m_inputValid) {
				reset();
				m_inputValid = false;
			}
			break;
		default:
			break;
		}
	}
	else m_inputValid = true;

	if (EventManager::Instance().isKeyDown(SDL_SCANCODE_ESCAPE))
	{
		TheGame::Instance()->quit();
	}
}

void PlayScene::start()
{
	m_launchSpeed = m_launchSpeedDefault;

	// Player Sprite
	m_pPlayer = new Player();
	m_pPlayer->setParent(this);
	addChild(m_pPlayer);
	m_pPlayer->spawn(glm::vec2(30, m_groundLevel));
	m_pPlayer->setHeight(10.0f);
	m_pPlayer->setWidth(10.0f);
	
	// Enemy Sprite
	m_pEnemy = new Enemy();
	m_pEnemy->setParent(this);
	addChild(m_pEnemy);
	m_pEnemy->spawn(glm::vec2(m_pPlayer->getTransform()->position.x + 485*PX_PER_METER, m_groundLevel));
	m_pEnemy->setHeight(10.0f);
	m_pEnemy->setWidth(15.0f);

	m_pGrenade = new Grenade();
	m_pGrenade->setParent(this);
	addChild(m_pGrenade);
	m_pGrenade->setHeight(5.0f);
	m_pGrenade->setWidth(5.0f);
	m_pGrenade->setGroundHeight(m_groundLevel);
	reset();

	// Labels
	
	const SDL_Color blue = { 0, 0, 255, 255 };

	m_pDistanceLabel = new Label("Distance", "Consolas", 40, blue, glm::vec2(Config::SCREEN_WIDTH / 2, 40.0f));
	m_pDistanceLabel->setParent(this);
	addChild(m_pDistanceLabel);

	m_pVelocityLabel = new Label("Velocity", "Consolas", 40, blue, glm::vec2(Config::SCREEN_WIDTH / 2, 100.0f));
	m_pVelocityLabel->setParent(this);
	addChild(m_pVelocityLabel);

	m_pAngleLabel = new Label("Velocity", "Consolas", 40, blue, glm::vec2(Config::SCREEN_WIDTH / 2, 160.0f));
	m_pAngleLabel->setParent(this);
	addChild(m_pAngleLabel);
}

void PlayScene::calculateAngle()
{
	if (m_mousePosition.x > m_pPlayer->getTransform()->position.x && m_mousePosition.y < m_pPlayer->getTransform()->position.y) {
		m_launchVector = Util::normalize(m_mousePosition - m_pPlayer->getTransform()->position);
		m_launchAngle = Util::angle(glm::vec2(1.0f, 0.0f), m_launchVector);
	}
}

void PlayScene::reset()
{
	m_pGrenade->spawn(m_pPlayer->getTransform()->position);
	m_pGrenade->setGrenadeState(SETUP);
}

void PlayScene::launch()
{
	m_pGrenade->getRigidBody()->acceleration = m_launchVector * m_launchSpeed;
	m_pGrenade->setGrenadeState(FLIGHT);
}
