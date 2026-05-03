#pragma once

#include "GameState.h"

class Tetromino;

class GameStateCombat : public GameState
{
private:
    std::vector<Entity*> m_backgrounds;

public:
    GameStateCombat() {};

    void Initialize() override;

    void OnEvent(const sf::Event& event) override;
    void OnUpdate() override;

    void EnterState() override;
    void ExitState() override;

    void RefreshGrid();
    Tetromino* GenerateTetromino();
    void SpawnEnemy();
};
