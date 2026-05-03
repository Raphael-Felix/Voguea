#pragma once

#include "GameState.h"

class SoundManager;

class GameStatePause : public GameState
{
private:
    SoundManager* m_soundManager;

public:
    GameStatePause();

    void Initialize() override;

    void OnEvent(const sf::Event& event) override;
    void OnUpdate() override;

    void EnterState() override;
    void ExitState() override;

    void IncreaseEffectSound();
    void DecreaseEffectSound();
    
    void IncreaseMusicSound();
    void DecreaseMusicSound();
};
