#pragma once
#include "Entity.h"
#include <map>
#include <string>

class Player;

class Enemy :
    public Entity
{
private:
    std::map<std::string, float> m_stats;

    bool m_canAttack = false;

public:
    void OnInitialize() override;
    void OnUpdate() override;

    void PlayTurn();

    void SetStats(int hp = 12, int atk = 2, int def = 0);
    void Attack();
    void TakeDamage(float value);

    float GetStat(std::string statName) { return m_stats[statName]; }
};