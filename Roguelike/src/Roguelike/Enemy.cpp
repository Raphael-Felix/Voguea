#include "Enemy.h"

#include "Data.h"
#include "Run.h"
#include "Utils.h"
#include "Debug.h"

#include "Player.h"

void Enemy::OnInitialize()
{
	SetStats();
}

void Enemy::OnUpdate()
{
	if (mActive)
		Debug::DrawText(GetPosition().x, GetPosition().y - 50, "HP : " + std::to_string((int)m_stats["Hp"]), 0.5f, 0.5f, sf::Color::Red, 20);
}

void Enemy::PlayTurn()
{
	Player* player = Data::GetInstance()->currentRun->m_player;
	sf::Vector2f playerPos = player->GetPosition();
	sf::Vector2f myPosition = GetPosition();

	float distance = Utils::GetDistance(playerPos.x, playerPos.y, myPosition.x, myPosition.y);

	if (distance > 100)
		GoToPosition(GetPosition().x - 150, GetPosition().y, 150);
	else
	{
		Attack();
	}
		
}

void Enemy::SetStats(int hp, int atk, int def)
{
	m_stats["Hp"] = hp;
	m_stats["Atk"] = atk;
	m_stats["Def"] = def;
}

void Enemy::Attack()
{
	Player* player = Data::GetInstance()->currentRun->m_player;

	player->TakeDamage(m_stats["Atk"]);
}

void Enemy::TakeDamage(float value)
{
	m_stats["Hp"] = std::max(0.f, m_stats["Hp"] - (value - m_stats["Def"]));
}