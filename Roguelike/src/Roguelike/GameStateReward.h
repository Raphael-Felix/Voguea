#pragma once

#include "GameState.h"

class GameStateReward : public GameState
{
public:
    GameStateReward() {};

    void Initialize() override;

    void OnEvent(const sf::Event& event) override;
    void OnUpdate() override;

    void EnterState() override;
    void ExitState() override;
};
