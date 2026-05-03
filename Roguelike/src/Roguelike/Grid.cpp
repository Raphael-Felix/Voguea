#include "Grid.h"
#include "Cell.h"
#include "MainScene.h"
#include "Tetromino.h"

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

Grid::Grid(int rowNb, int colNb, MainScene* scene, int pxByCell) :
	m_rowNb(rowNb), m_colNb(colNb), m_scene(scene), m_pxByCell(pxByCell)
{
	for (int i = 0; i < m_rowNb; ++i)
	{
		std::vector<Cell*> rowCells;
		for (int j = 0; j < m_colNb; ++j)
		{
			rowCells.push_back(scene->CreateRectangle<Cell>(m_pxByCell, m_pxByCell, sf::Color::White, nullptr));

			sf::Vector2f cellPosition = GetPosition(1.f, 1.f);
			cellPosition.x -= (m_colNb - j) * m_pxByCell;
			cellPosition.y -= (m_rowNb - i) * m_pxByCell;

			rowCells[j]->SetPosition(cellPosition.x, cellPosition.y, 0.f, 1.f);
			rowCells[j]->SetGridPlacement(sf::Vector2f{ (float)i, (float)j });
		}
		m_cells.push_back(rowCells);
	}
}

Grid::~Grid()
{
	for (int i = 0; i < m_cells.size(); ++i)
	{
		for (int j = 0; j < m_cells.size(); ++j)
		{
			m_cells[i][j]->Destroy();
		}
	}
}

void Grid::SetPosition(int x, int y, float anchorX, float anchorY)
{
	float sizeX = m_rowNb * m_pxByCell;
	float sizeY = m_colNb * m_pxByCell;

	m_position.x = x - sizeX * anchorX;
	m_position.y = y - sizeY * anchorY;

	for (int i = 0; i < m_rowNb; ++i)
	{
		for (int j = 0; j < m_colNb; ++j)
		{
			sf::Vector2f cellPosition = GetPosition(1.f, 1.f);
			cellPosition.x -= (m_colNb - j) * m_pxByCell;
			cellPosition.y -= (m_rowNb - i - 1) * m_pxByCell;

			m_cells[i][j]->SetPosition(cellPosition.x, cellPosition.y, 0.f, 1.f);
		}
	}
}

sf::Vector2f Grid::GetPosition(float anchorX, float anchorY)
{
	float posX = m_position.x + m_rowNb * m_pxByCell * anchorX;
	float posY = m_position.y + m_colNb * m_pxByCell * anchorY;

	return sf::Vector2f{ posX, posY };
}

void Grid::SetActive(bool active)
{
	m_active = active;

	for (int i = 0; i < m_rowNb; ++i)
	{
		for (int j = 0; j < m_colNb; ++j)
		{
			m_cells[i][j]->SetActive(active);
		}
	}
}

bool Grid::IsInside(float x, float y)
{
	if (x < GetPosition(0.f).x || x > GetPosition(1.f, 0.f).x)
		return false;
	if (y < GetPosition(0.f, 0.f).y || y > GetPosition(0.f, 1.f).y)
		return false;

	return true;
}

bool Grid::Fill(Tetromino* tetromino)
{
	//Position de la souris
	sf::Vector2f baseSquarePos = tetromino->GetBaseSquare()->entity->GetPosition();

	//Vérification que la souris se trouve dans la grille
	if (IsInside(baseSquarePos.x, baseSquarePos.y) == false)
		return false;

	//Récupération de l'index de la cellule à la position de la souris
	int basePosX = baseSquarePos.x - GetPosition(0.f, 0.f).x;
	int basePosY = baseSquarePos.y - GetPosition(0.f, 0.f).y;

	basePosX /= m_pxByCell;
	basePosY /= m_pxByCell;

	int posX = basePosX;
	int posY = basePosY;

	Cell* cell = m_cells[posY][posX];

	//Pour chaque carré du tetromino
	for (int i = 0; i < tetromino->GetSquareNb(); ++i)
	{
		Square* square = tetromino->GetSquare(i);
		sf::Vector2f squarePos = square->entity->GetPosition();

		posX = basePosX + square->squareRelativePosition.x;
		posY = basePosY + square->squareRelativePosition.y;

		if (posX < 0 || posX >= m_cells.size())
			return false;
		else if (posY < 0 || posY >= m_cells.size())
			return false;

		cell = m_cells[posY][posX];

		if (cell->IsFilled())
			return false;
	}

	for (int i = 0; i < tetromino->GetSquareNb(); ++i)
	{
		Square* square = tetromino->GetSquare(i);

		posX = basePosX + square->squareRelativePosition.x;
		posY = basePosY + square->squareRelativePosition.y;

		cell = m_cells[posY][posX];

		cell->Fill(true);
	}

	tetromino->SetPosition(m_cells[basePosY][basePosX]->GetPosition());
	return true;
}

bool Grid::Unfill(Tetromino* tetromino)
{
	//Position de la souris
	sf::Vector2f baseSquarePos = tetromino->GetBaseSquare()->entity->GetPosition();

	//Vérification que la souris se trouve dans la grille
	if (IsInside(baseSquarePos.x, baseSquarePos.y) == false)
		return false;

	//Récupération de l'index de la cellule à la position de la souris
	int basePosX = baseSquarePos.x - GetPosition(0.f, 0.f).x;
	int basePosY = baseSquarePos.y - GetPosition(0.f, 0.f).y;

	basePosX /= m_pxByCell;
	basePosY /= m_pxByCell;

	int posX;
	int posY;

	Cell* cell;

	for (int i = 0; i < tetromino->GetSquareNb(); ++i)
	{
		Square* square = tetromino->GetSquare(i);

		posX = basePosX + square->squareRelativePosition.x;
		posY = basePosY + square->squareRelativePosition.y;

		cell = m_cells[posY][posX];

		cell->Fill(false);
	}

	return true;
}

bool Grid::IsFull()
{
	for (int i = 0; i < m_cells.size(); ++i)
	{
		for (int j = 0; j < m_cells[i].size(); ++j)
		{
			if (m_cells[i][j]->IsFilled() == false)
				return false;
		}
	}

	return true;
}
