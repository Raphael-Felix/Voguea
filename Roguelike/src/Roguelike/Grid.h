#pragma once
#include <vector>
#include "Entity.h"

class Cell;
class MainScene;
class Tetromino;

class Grid
{
private:
	MainScene* m_scene;

	std::vector<std::vector<Cell*>> m_cells;

	int m_rowNb;
	int m_colNb;

	bool m_active = true;

	sf::Vector2f m_position = { 0.f, 0.f };

	int m_pxByCell;
public:
	Grid(int rowNb, int colNb, MainScene* scene, int pxByCell = 64);
	~Grid();

	void SetPosition(int x, int y, float anchorX = 0.5f, float anchorY = 0.5f);
	sf::Vector2f GetPosition(float anchorX = 0.5f, float anchorY = 0.5f);

	void SetActive(bool active);
	bool IsActive() { return m_active; }


	bool IsInside(float x, float y);
	bool Fill(Tetromino* tetromino);
	bool Unfill(Tetromino* tetromino);

	bool IsFull();
};