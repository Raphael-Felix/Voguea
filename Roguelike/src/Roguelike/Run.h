#pragma once

#include <vector>
#include "SFML/System/Vector2.hpp"

class Player;
class Map;
class Grid;
class Tetromino;

class Run
{
public:
    // Joueur
    Player* m_player;

    //Enemies
    int m_currentTurn = 0;
    int m_enemiesToSpawn = 0;
    int m_spawnRate = 3;
    int m_lastSpawn = 0;

    // Carte

    Map* map;
    int mapDepth;

    // Grille
	Grid* m_grid;

    float m_mult = 0;

    // Tetrominos
	std::vector<Tetromino*> m_displayedTetrominos;
    std::vector<std::vector<sf::Vector2f>> m_tetrominosDeck;
    std::vector<std::vector<sf::Vector2f>> m_tetrominosBag;

    Tetromino* m_draggedTetromino;
    int m_draggedTetrominoRotationCount = 0;

	bool m_tetrominoRotation = true;

    // Niveaux
    int m_levelSquareSize = 64;
    int m_levelsCount = 3;
    int m_currentLevelIndex = 1;

    std::vector<int> m_bestScores;

    Run();
    ~Run();

    void Swap(int i, int j, std::vector<std::vector<sf::Vector2f>>* list);
    void DestroyTetrominos();
    void GenerateTetrominosDeck();
    void GenerateTetrominosBag();

    void CreateMap(int stagesAmount = 10, int stagesMaxWidth = 5);
};
