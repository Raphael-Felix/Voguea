#pragma once

#include "GameState.h"

class GameStateSkillTree : public GameState
{
public:
    GameStateSkillTree() {};

    void Initialize() override;

    void OnEvent(const sf::Event& event) override;
    void OnUpdate() override;

    void EnterState() override;
    void ExitState() override;
};
