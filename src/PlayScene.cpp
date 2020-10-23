#include "PlayScene.h"
#include "Game.h"
#include "EventManager.h"
#include "Util.h"

// required for IMGUI
#include "IMGUI/imgui.h"
#include "IMGUI_SDL/imgui_sdl.h"
#include "Renderer.h"



PlayScene::PlayScene()
{
	TextureManager::Instance()->load("../Assets/textures/background.png", "background");
	PlayScene::start();
}

PlayScene::~PlayScene()
= default;

void PlayScene::draw()
{
	TextureManager::Instance()->draw("background", Config::SCREEN_WIDTH / 2, Config::SCREEN_HEIGHT / 2, Config::SCREEN_WIDTH, Config::SCREEN_HEIGHT, 0, 255, true, SDL_FLIP_NONE);

	if (EventManager::Instance().isIMGUIActive())
	{
		GUI_Function();
	}

	SDL_SetRenderDrawColor(Renderer::Instance()->getRenderer(), 232, 236, 241, 255);
	SDL_RenderFillRect(Renderer::Instance()->getRenderer(), &StartSurface);
	SDL_RenderFillRect(Renderer::Instance()->getRenderer(), &SlideSurface);
	drawDisplayList();
	SDL_SetRenderDrawColor(Renderer::Instance()->getRenderer(), 255, 255, 255, 255);
}

void PlayScene::update(float deltaTime)
{
	updateDisplayList(deltaTime);

	m_pDistanceLabel->setText("Box position X: " + std::to_string(m_pGrenade->getTransform()->position.x) + ", Y: " + std::to_string(m_pGrenade->getTransform()->position.y));
	m_pVelocityLabel->setText("Box velocity on X axis: " + std::to_string(m_pGrenade->getRigidBody()->velocity.x / PX_PER_METER) + " m/s");
	m_pAngleLabel->setText("Box angle: " + std::to_string(Util::Rad2Deg * m_pGrenade->rotation) + " degrees");
	if (m_pGrenade->getGrenadeState()!=SETUP)
		m_pScaleLabel->setText("Current Friction Coefficient: " + (m_pGrenade->getGrenadeState() == INCLINE ? "0" : std::to_string(-m_pPlayer->mu)));
}

void PlayScene::clean()
{
	removeAllChildren();
}

void PlayScene::handleEvents(float deltaTime)
{
	EventManager::Instance().update();

	if (EventManager::Instance().isKeyDown(SDL_SCANCODE_ESCAPE))
	{
		TheGame::Instance()->quit();
	}
}

void PlayScene::start()
{
	//// Player Sprite
	m_pPlayer = new Player();
	m_pPlayer->setParent(this);
	addChild(m_pPlayer);
	
	// Box Sprite
	m_pGrenade = new Grenade();
	m_pGrenade->setParent(this);
	addChild(m_pGrenade);
	m_pGrenade->slope = m_pPlayer;
	resetSim();

	// Labels
	const SDL_Color blue = { 0, 0, 255, 255 };

	m_pDistanceLabel = new Label("Distance", "Consolas", 30, blue, glm::vec2(700, 40.0f));
	m_pDistanceLabel->setParent(this);
	addChild(m_pDistanceLabel);

	m_pVelocityLabel = new Label("Velocity", "Consolas", 30, blue, glm::vec2(700, 70.0f));
	m_pVelocityLabel->setParent(this);
	addChild(m_pVelocityLabel);

	m_pAngleLabel = new Label("Velocity", "Consolas", 30, blue, glm::vec2(700, 100.0f));
	m_pAngleLabel->setParent(this);
	addChild(m_pAngleLabel);

	m_pScaleLabel = new Label("Scale = 100 px/m", "Consolas", 30, blue, glm::vec2(700, 130.0f));
	m_pScaleLabel->setParent(this);
	addChild(m_pScaleLabel);

	//graphics
	BuildStartSurface();
	BuildSlideSurface();
}

void PlayScene::resetSim()
{
	m_pPlayer->spawn(glm::vec2(Config::SCREEN_WIDTH / 4, (Config::SCREEN_HEIGHT / 4) * 3), 4, 3);
	m_pPlayer->BuildRamp();
	reset();
}

void PlayScene::reset()
{
	m_pGrenade->spawn(m_pPlayer->Rise);
	BuildStartSurface();
	BuildSlideSurface();
}

void PlayScene::launch()
{
	m_pGrenade->launch();
}

void PlayScene::GUI_Function()
{
	// Always open with a NewFrame
	ImGui::NewFrame();

	// See examples by uncommenting the following - also look at imgui_demo.cpp in the IMGUI filter
	//ImGui::ShowDemoWindow();

	ImGui::Begin("Settings", NULL, ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoMove);

	ImGui::SetWindowPos(ImVec2(0, 0), true);

	ImGui::Separator();

	if (ImGui::Button("Release"))
	{
		if (m_pGrenade->getGrenadeState() == SETUP)
			launch();
	}

	ImGui::SameLine();

	if (ImGui::Button("Reset Box"))
	{
		reset();
	}

	ImGui::SameLine();

	if (ImGui::Button("Reset Sim"))
	{
		resetSim();
	}

	ImGui::Separator();

	
	if (ImGui::SliderFloat("Ramp Width", &m_pPlayer->rampWidth, 1.0f, 10.0f))
	{
		m_pPlayer->BuildRamp();
		reset();
	}

	if (ImGui::SliderFloat("Ramp Height", &m_pPlayer->rampHeight, 1.0f, 10.0f))
	{
		m_pPlayer->BuildRamp();
		reset();
	}

	if (ImGui::SliderFloat("Ramp Position (X)", &m_pPlayer->Origin.x, 0.0f, Config::SCREEN_WIDTH))
	{
		m_pPlayer->spawn(m_pPlayer->Origin, m_pPlayer->rampWidth, m_pPlayer->rampHeight);
		reset();
	}

	if (ImGui::SliderFloat("Ramp Position (Y)", &m_pPlayer->Origin.y, 0.0f, Config::SCREEN_HEIGHT))
	{
		m_pPlayer->spawn(m_pPlayer->Origin, m_pPlayer->rampWidth, m_pPlayer->rampHeight);
		reset();
	}
	if (ImGui::SliderFloat("Box Position (X)", &m_pGrenade->Ground.x, 0.0f, Config::SCREEN_WIDTH))
	{
		m_pGrenade->Ground.y = m_pPlayer->GetCurrentHeight(m_pGrenade->Ground.x);
		m_pGrenade->CalculatePosition();
	}
	ImGui::End();

	// Don't Remove this
	ImGui::Render();
	ImGuiSDL::Render(ImGui::GetDrawData());
	ImGui::StyleColorsDark();
}

void PlayScene::m_buildGrid()
{
	const auto size = Config::TILE_SIZE;
	const auto offset = size * 0.5f;

	m_pGrid = std::vector<Tile*>();

	for (int row = 0; row < Config::ROW_NUM; ++row)
	{
		for (int col = 0; col < Config::COL_NUM; ++col)
		{
			auto tile = new Tile(glm::vec2(offset + size * col, offset + size * row), glm::vec2(col, row));
			//addChild(tile);
			m_pGrid.push_back(tile);
		}
	}
}

void PlayScene::BuildStartSurface()
{
	StartSurface.x = 0.0f;
	StartSurface.y = m_pPlayer->Rise.y;
	StartSurface.w = m_pPlayer->Origin.x;
	StartSurface.h = Config::SCREEN_HEIGHT - m_pPlayer->Rise.y;
}

void PlayScene::BuildSlideSurface()
{
	SlideSurface.x = m_pPlayer->Run.x;
	SlideSurface.y = m_pPlayer->Run.y;
	SlideSurface.w = Config::SCREEN_WIDTH - m_pPlayer->Run.x;
	SlideSurface.h = Config::SCREEN_HEIGHT - m_pPlayer->Run.y;
}