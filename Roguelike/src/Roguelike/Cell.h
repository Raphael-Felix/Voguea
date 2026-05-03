#pragma once
#include "Entity.h"
#include <vector>

class Cell : 
	public Entity
{
private:
	int m_row;
	int m_col;

	bool m_isFilled = false;

public:
	void OnInitialize() override;
	bool IsFilled() { return m_isFilled; }
	void Fill(bool fill) { m_isFilled = fill;}

	void SetGridPlacement(sf::Vector2f placement) { m_row = placement.x, m_col = placement.y; }
};