#pragma once

#include "Scene.h"

#include <stack>
#include <typeindex>

class GameState;
class Data;

class MainScene :
	public Scene
{
private:
	Data* data;

    std::vector<GameState*> m_loadedScenes;
    GameState* m_currentGameState;

	std::map<std::type_index, GameState*> m_loadedGameStates;
	std::stack<GameState*> m_stackGameStates;

public:
	void OnInitialize() override;
	void OnEvent(const sf::Event& event) override;
	void OnUpdate() override;

	// Lancer une nouvelle scene
	template<typename T>
	void LoadGameState();

	void ShowLastState();

	// Misc
	void QuitApp();

	void ClearStatesStack();
};

#include "MainScene.inl"
