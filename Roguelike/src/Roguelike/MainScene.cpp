#include "MainScene.h"

#include "SoundManager.h"
#include "GameState.h"
#include "GameStateMainMenu.h"
#include "gameStateMap.h"
#include "Data.h"
#include "Run.h"

#include "SFML/Graphics.hpp"
#include "SFML/Window.hpp"

void MainScene::OnInitialize()
{
	srand(time(NULL));

	// Chargement du menu principal
	LoadGameState<GameStateMainMenu>();
}

void MainScene::OnEvent(const sf::Event& event)
{
	m_currentGameState->OnEvent(event);
}

void MainScene::OnUpdate()
{
	m_currentGameState->OnUpdate();
}

void MainScene::QuitApp()
{
	GameManager::Get()->mpWindow->close();
}

void MainScene::ShowLastState()
{
	if (m_stackGameStates.size() <= 1)
		return;

	if (m_currentGameState)
		m_currentGameState->OnExitState();

	m_stackGameStates.pop();
	m_currentGameState = m_stackGameStates.top();

	m_currentGameState->OnEnterState();
	m_stackGameStates.push(m_currentGameState);
}

void MainScene::ClearStatesStack()
{
	while (m_stackGameStates.empty() != true)
		m_stackGameStates.pop();
}
