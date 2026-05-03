#pragma once
#include "Entity.h"

#include <map>

class Enemy;

class Player : public Entity
{
private:
	//Stats
	std::map<std::string, float> m_baseStats;
	std::map<std::string, float> m_stats;

	int m_exp = 0;

public:
	void OnInitialize() override;
	void OnUpdate() override;

	void Heal(float value);
	void TakeDamage(float value);
	void Attack(Enemy* target, float mult = 1);

	std::map<std::string, float> GetStats() { return m_stats; }
	float GetStat(std::string statName) { return m_stats[statName]; }

	void GainExp(int value) { m_exp += value; }
	void UseExp(int value) { m_exp -= value; }
	int GetExp() { return m_exp; }
};
