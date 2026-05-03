#pragma once

#include "GameState.h"

class GameStateEvent : public GameState
{
public:
    GameStateEvent() {};

    void Initialize() override;

    void OnEvent(const sf::Event& event) override;
    void OnUpdate() override;

    void EnterState() override;
    void ExitState() override;
};
