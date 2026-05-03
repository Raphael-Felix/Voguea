#pragma once

#include "GameState.h"

class GameStateMainMenu : public GameState
{
public:
    GameStateMainMenu() {};

    void Initialize() override;

    void OnEvent(const sf::Event& event) override;
    void OnUpdate() override;

    void EnterState() override;
    void ExitState() override;

    void NewRun();
};
