#include "GameState.h"

#include "Entity.h"
#include "Button.h"
#include "Sounds.h"
#include "MainScene.h"
#include "Data.h"
#include <iostream>

GameState::GameState()
{
	scene = dynamic_cast<MainScene*>(GameManager::Get()->GetScene());

	if (scene == nullptr)
	{
		std::cout << "must use MainScene for the game to run";
		exit(1);
	}

	data = Data::GetInstance();

	randomSounds = Sounds::GetInstance();
}

GameState::~GameState()
{
	for (Entity* entity : entities)
		entity->Destroy();
	for (Button* button : buttons)
		button->Destroy();
}

void GameState::EnableButtons()
{
	for (Button* button : buttons)
		button->SetActive(true);
}

void GameState::DisableButtons()
{
	for (Button* button : buttons)
		button->SetActive(false);
}

void GameState::OnEnterState()
{
	for (Entity* entity : entities)
		entity->SetActive(true);

	for (Button* button : buttons)
		button->SetActive(true);

	EnterState();
}

void GameState::EnterState()
{
}

void GameState::OnExitState()
{
	ExitState();

	for (Entity* entity : entities)
		entity->SetActive(false);

	for (Button* button : buttons)
		button->SetActive(false);
}

void GameState::ExitState()
{
}
