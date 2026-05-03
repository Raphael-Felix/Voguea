#include "MainScene.h"

#include "GameState.h"

template<typename T>
void MainScene::LoadGameState()
{
	if (m_currentGameState)
		m_currentGameState->OnExitState();

	auto it = m_loadedGameStates.find(typeid(T));
	if (it != m_loadedGameStates.end())
	{
		m_currentGameState = it->second;
		m_currentGameState->OnEnterState();
		m_stackGameStates.push(m_currentGameState);
		return;
	}

	m_currentGameState = new T();
	m_currentGameState->Initialize();
	m_currentGameState->OnEnterState();
	m_loadedGameStates.emplace(typeid(T), m_currentGameState);
	m_stackGameStates.push(m_currentGameState);
}
