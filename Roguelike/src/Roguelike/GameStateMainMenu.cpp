#include "GameStateMainMenu.h"

#include "MainScene.h"
#include "Sounds.h"
#include "Debug.h"
#include "Button.h"
#include "Data.h"
#include "GameStatePause.h"
#include "GameStateCombat.h"
#include "GameStateMap.h"

void GameStateMainMenu::Initialize()
{
	int windowWidth = scene->GetWindowWidth();
	int windowHeight = scene->GetWindowHeight();
	
	// Bckground menu principal
	{

		Entity* backgroundEntity = scene->CreateSprite<Entity>(windowWidth, windowHeight, "../../../res/assets/Backgrounds/Sky/1.png", nullptr);
		backgroundEntity->SetPosition(windowWidth / 2, windowHeight / 2, 0.5f, 0.5f);
		entities.push_back(backgroundEntity);

		backgroundEntity = scene->CreateSprite<Entity>(windowWidth, windowHeight, "../../../res/assets/Backgrounds/Sky/2.png", nullptr);
		backgroundEntity->SetPosition(windowWidth / 2, windowHeight / 2, 0.5f, 0.5f);
		entities.push_back(backgroundEntity);

		backgroundEntity = scene->CreateSprite<Entity>(windowWidth, windowHeight, "../../../res/assets/Backgrounds/Sky/3.png", nullptr);
		backgroundEntity->SetPosition(windowWidth / 2, windowHeight / 2, 0.5f, 0.5f);
		entities.push_back(backgroundEntity);

		backgroundEntity = scene->CreateSprite<Entity>(windowWidth, windowHeight, "../../../res/assets/Backgrounds/Sky/4.png", nullptr);
		backgroundEntity->SetPosition(windowWidth / 2, windowHeight / 2, 0.5f, 0.5f);
		entities.push_back(backgroundEntity);
	}

	// Main Menu buttons
	{
		sf::Color transparentRectangle = sf::Color(30, 30, 30);
		transparentRectangle.a = 20;

		Button* tempButton = scene->CreateRectangle<Button>(windowWidth, 200, transparentRectangle, nullptr);
		tempButton->GetShape()->setOutlineColor(sf::Color::Transparent);
		tempButton->Initialize("Voguea", nullptr, 120, 0, sf::Color(148, 135, 182));
		tempButton->SetPosition(windowWidth / 2, 200);
		buttons.push_back(tempButton);

		transparentRectangle.a = 75;

		/*tempButton = scene->CreateRectangle<Button>(200, 50, transparentRectangle, nullptr);
		tempButton->Initialize("Continuer", std::bind(&MainScene::LoadGameState<GameStateMap>, scene));
		tempButton->SetPosition(windowWidth / 2, windowHeight - 320);
		buttons.push_back(tempButton);*/

		tempButton = scene->CreateRectangle<Button>(200, 50, transparentRectangle, nullptr);
		tempButton->Initialize("Nouvelle partie", std::bind(&GameStateMainMenu::NewRun, this));
		tempButton->SetPosition(windowWidth / 2, windowHeight - 230);
		buttons.push_back(tempButton);

		tempButton = scene->CreateRectangle<Button>(200, 50, transparentRectangle, nullptr);
		tempButton->Initialize("Paramètres", std::bind(&MainScene::LoadGameState<GameStatePause>, scene));
		tempButton->SetPosition(windowWidth / 2, windowHeight - 160, 0.5f, 0.5f);
		buttons.push_back(tempButton);

		tempButton = scene->CreateRectangle<Button>(200, 50, transparentRectangle, nullptr);
		tempButton->Initialize("Quitter", std::bind(&MainScene::QuitApp, scene));
		tempButton->SetPosition(windowWidth / 2, windowHeight - 80, 0.5f, 0.5f);
		buttons.push_back(tempButton);
	}
}

void GameStateMainMenu::OnEvent(const sf::Event& event)
{
}

void GameStateMainMenu::OnUpdate()
{
	
}

void GameStateMainMenu::EnterState()
{
	scene->ClearStatesStack();
}

void GameStateMainMenu::ExitState()
{
}

void GameStateMainMenu::NewRun()
{
	Data::GetInstance()->StartNewRun();

	scene->LoadGameState<GameStateMap>();
}
