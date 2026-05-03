#include "GameStateMap.h"

#include "Button.h"
#include "MainScene.h"
#include "GameStatePause.h"
#include "GameStateCombat.h"
#include "Data.h"
#include "Run.h"
#include "Map.h"
#include "Sounds.h"
#include <iostream>

void GameStateMap::Initialize()
{
	int windowWidth = scene->GetWindowWidth();
	int windowHeight = scene->GetWindowHeight();

	// Pause
	{
		Button* tempButton = scene->CreateRectangle<Button>(200, 50, sf::Color::Transparent, nullptr);
		tempButton->Initialize("Parametres", std::bind(&MainScene::LoadGameState<GameStatePause>, scene));
		tempButton->SetPosition(10, 10, 0.f, 0.f);
		buttons.push_back(tempButton);
	}
}

void GameStateMap::OnEvent(const sf::Event& event)
{
	// Offset
	if (event.type == sf::Event::KeyPressed)
	{
		if (event.key.code == sf::Keyboard::Q)
		{
			currentMap->OffsetButtons(-15);
		}
		else if (event.key.code == sf::Keyboard::D)
		{
			currentMap->OffsetButtons(15);
		}
	}
}

void GameStateMap::OnUpdate()
{
	Data::GetInstance()->currentRun->map->DisplayButtonsConnections();
}

void GameStateMap::EnterState()
{
	currentMap = Data::GetInstance()->currentRun->map;

	Data::GetInstance()->currentRun->map->ShowMap();
}

void GameStateMap::ExitState()
{
	Data::GetInstance()->currentRun->map->HideMap();
}
