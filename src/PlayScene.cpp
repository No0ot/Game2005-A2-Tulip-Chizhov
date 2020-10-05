#include "PlayScene.h"
#include "Game.h"
#include "EventManager.h"
#include "Util.h"
#include "IMGUI/imgui.h"
#include "IMGUI_SDL/imgui_sdl.h"
#include "Renderer.h"

PlayScene::PlayScene()
{
	PlayScene::start();
}

PlayScene::~PlayScene()
= default;

void PlayScene::draw()
{
	drawDisplayList();
	if (EventManager::Instance().isIMGUIActive())
	{
		GUI_Function();
	}
	SDL_SetRenderDrawColor(Renderer::Instance()->getRenderer(), 255, 255, 255, 255);

}

void PlayScene::update(float deltaTime)
{
	updateDisplayList(deltaTime);
	
	if (m_pPlayer->checkDistance(m_pEnemy) <= (m_pPlayer->getWidth() + m_pEnemy->getWidth()) * 0.5f)
		m_pDistanceLabel->setText("Player colliding with Enemy");
	else m_pDistanceLabel->setText("Distance = " + std::to_string(m_pPlayer->checkDistance(m_pEnemy)));
	m_pVelocityLabel->setText("Velocity = " + std::to_string(Util::magnitude(m_pPlayer->getRigidBody()->velocity)));


}

void PlayScene::clean()
{
	removeAllChildren();
}

void PlayScene::handleEvents(float deltaTime)
{
	EventManager::Instance().update();
	if (EventManager::Instance().isKeyDown(SDL_SCANCODE_LSHIFT)) {
		m_pPlayer->SetSprint(true);
	}

	if (EventManager::Instance().isKeyDown(SDL_SCANCODE_A)){
		m_pPlayer->moveLeft();
	}
	if (EventManager::Instance().isKeyDown(SDL_SCANCODE_D)){
		m_pPlayer->moveRight();
	}
	if (EventManager::Instance().isKeyDown(SDL_SCANCODE_W)){
		m_pPlayer->moveUp();
	}
	if (EventManager::Instance().isKeyDown(SDL_SCANCODE_S)){
		m_pPlayer->moveDown();
	}


	if (EventManager::Instance().getMouseButton(2)) {
		m_pEnemy->spawn(EventManager::Instance().getMousePosition());
	}


	if (EventManager::Instance().isKeyDown(SDL_SCANCODE_ESCAPE))
	{
		TheGame::Instance()->quit();
	}

}

void PlayScene::start()
{
	m_buildGrid();

	// Player Sprite
	m_pPlayer = new Player();
	m_pPlayer->setParent(this);
	addChild(m_pPlayer);
	
	// Enemy Sprite
	m_pEnemy = new Enemy();
	m_pEnemy->setParent(this);
	addChild(m_pEnemy);

	// Labels
	const SDL_Color blue = { 0, 0, 255, 255 };

	m_pDistanceLabel = new Label("Distance", "Consolas", 40, blue, glm::vec2(400.0f, 40.0f));
	m_pDistanceLabel->setParent(this);
	addChild(m_pDistanceLabel);

	m_pVelocityLabel = new Label("Velocity", "Consolas", 40, blue, glm::vec2(400.0f, 100.0f));
	m_pVelocityLabel->setParent(this);
	addChild(m_pVelocityLabel);

}

void PlayScene::m_buildGrid()
{
	const auto size = 50;
	const auto offset = size * 0.5f;

	m_pGrid = std::vector<Tile*>();

	for (int row = 0; row < Config::ROW_NUM; ++row)
	{
		for (int col = 0; col < Config::COL_NUM; ++col)
		{
			auto tile = new Tile(glm::vec2(offset + size * col, offset + size * row), glm::vec2(col, row));
			addChild(tile);
			m_pGrid.push_back(tile);
		}
	}
}

void PlayScene::GUI_Function() const
{
	// Always open with a NewFrame
	ImGui::NewFrame();

	// See examples by uncommenting the following - also look at imgui_demo.cpp in the IMGUI filter
	//ImGui::ShowDemoWindow();

	ImGui::Begin("Settings", NULL, ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_MenuBar);

	if (ImGui::Button("Project the Projectile"))
	{
		std::cout << "My Button Pressed" << std::endl;
	}

	ImGui::Separator();

	static float float3[3] = { 0.0f, 1.0f, 1.5f };    // <----- make this the angle thrown
	if (ImGui::SliderFloat3("set angle", float3, 0.0f, 90.0f))
	{
		std::cout << float3[0] << std::endl;
		std::cout << float3[1] << std::endl;
		std::cout << float3[2] << std::endl;
		std::cout << "---------------------------\n";
	}

	ImGui::End();

	// Don't Remove this
	ImGui::Render();
	ImGuiSDL::Render(ImGui::GetDrawData());
	ImGui::StyleColorsDark();
}

