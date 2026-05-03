#pragma once

#include "GameState.h"

class Map;

class GameStateMap : public GameState
{
private:
    Map* currentMap = nullptr;

public:
    GameStateMap() {};

    void Initialize() override;

    void OnEvent(const sf::Event& event) override;
    void OnUpdate() override;

    void EnterState() override;
    void ExitState() override;

    void ChangeOffset(float value);
};
