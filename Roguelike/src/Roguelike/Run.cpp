#include "Run.h"

#include "Tetromino.h"
#include "Map.h"

Run::Run()
{
	CreateMap();
}

Run::~Run()
{
	DestroyTetrominos();

	delete m_player;
	delete map;
	delete m_grid;
}

void Run::Swap(int i, int j, std::vector<std::vector<sf::Vector2f>>* list)
{
	std::vector<sf::Vector2f> intermed = (*list)[i];
	(*list)[i] = (*list)[j];
	(*list)[j] = intermed;
}

void Run::DestroyTetrominos()
{
	for (int i = m_displayedTetrominos.size() - 1; i >= 0; --i)
	{
		delete m_displayedTetrominos[i];
		m_displayedTetrominos.erase(m_displayedTetrominos.begin() + i);
	}
}

void Run::GenerateTetrominosDeck()
{
	std::vector<sf::Vector2f> verticalTetromino = { sf::Vector2f(0, 0), sf::Vector2f(0, -1), sf::Vector2f(0, 1), sf::Vector2f(0, 2) };
	m_tetrominosDeck.push_back(verticalTetromino);

	std::vector<sf::Vector2f> squareTetromino = { sf::Vector2f(0, 0), sf::Vector2f(1, 0), sf::Vector2f(0, 1), sf::Vector2f(1, 1) };
	m_tetrominosDeck.push_back(squareTetromino);

	std::vector<sf::Vector2f> zTetromino = { sf::Vector2f(0, 0), sf::Vector2f(-1, 0), sf::Vector2f(0, 1), sf::Vector2f(1, 1) };
	m_tetrominosDeck.push_back(zTetromino);

	std::vector<sf::Vector2f> reverseZTetromino = { sf::Vector2f(0, 0), sf::Vector2f(1, 0), sf::Vector2f(0, 1), sf::Vector2f(-1, 1) };
	m_tetrominosDeck.push_back(reverseZTetromino);

	std::vector<sf::Vector2f> tTetromino = { sf::Vector2f(0, 0), sf::Vector2f(0, -1), sf::Vector2f(-1, 0), sf::Vector2f(1, 0) };
	m_tetrominosDeck.push_back(tTetromino);

	std::vector<sf::Vector2f> lTetromino = { sf::Vector2f(0, 0), sf::Vector2f(0, -1), sf::Vector2f(1, 0), sf::Vector2f(2, 0) };
	m_tetrominosDeck.push_back(lTetromino);

	std::vector<sf::Vector2f> jTetromino = { sf::Vector2f(0, 0), sf::Vector2f(0, -1), sf::Vector2f(-1, 0), sf::Vector2f(-2, 0) };
	m_tetrominosDeck.push_back(jTetromino);
}

void Run::GenerateTetrominosBag()
{
	std::vector<std::vector<sf::Vector2f>> tetrominoBag = m_tetrominosDeck;

	for (int i = tetrominoBag.size() - 1; i >= 0; --i)
	{
		int index = 0;

		if (i != 0)
			index = rand() % i + 1;

		m_tetrominosBag.push_back(tetrominoBag[index]);
		Swap(index, i, &tetrominoBag);
	}
}

void Run::CreateMap(int stagesAmount, int stagesMaxWidth)
{
	if (map == nullptr)
		delete map;

	map = new Map();

	map->CreateRandomMap(5, 3, 10, 20);
}
