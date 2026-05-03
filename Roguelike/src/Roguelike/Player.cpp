#include "Player.h"

#include "Enemy.h"

#include "Debug.h"

void Player::OnInitialize()
{
	m_baseStats["MaxHp"] = 10;
	m_baseStats["Atk"] = 3;
	m_baseStats["Def"] = 1;

	m_stats["Hp"] = 10;
	m_stats["Atk"] = 3;
	m_stats["Def"] = 1;

	SetPosition(GetScene()->GetWindowWidth() / 2 - 200, GetScene()->GetWindowHeight() / 2, 0.5f, 0.57f);
}

void Player::OnUpdate()
{
	if (mActive)
		Debug::DrawText(GetPosition().x, GetPosition().y - 50, "HP : " + std::to_string((int)m_stats["Hp"]), 0.5f, 0.5f, sf::Color::Red, 20);
}

void Player::Heal(float value)
{
	m_stats["Hp"] = std::min(m_baseStats["MaxHp"], m_stats["Hp"] + value);
}

void Player::TakeDamage(float value)
{
	m_stats["Hp"] = std::max(0.f, m_stats["Hp"] - (value - m_stats["Def"]));
}

void Player::Attack(Enemy* enemy, float mult)
{
	enemy->TakeDamage(m_stats["Atk"] * mult);
}
