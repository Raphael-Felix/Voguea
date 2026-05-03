#pragma once

#include <vector>
#include <SFML/System/Vector2.hpp>

class Entity;
class Scene;

struct Square
{
	Entity* entity;

	sf::Vector2f squareRelativePosition;
};

class Tetromino
{
private:
	Scene* scene;

	// Position du Tetromino lorsqu'il est immobile
	sf::Vector2f staticPosition;
	// Position du Tetromino dynamique
	sf::Vector2f position;

	std::vector<Square*> composingSquares;

	float squareWidth;

	bool hasBeenReplaced = false;

public:
	Tetromino(Scene* scene, int sWidth = 50);

	~Tetromino();

	// Ajout d'un carré à la forme 
	// relativePosition : position en "cases" par rapport au centre de la forme (ex: centre = {0, 0}; case a droite du centre = {1, 0} etc)
	void AddSquare(sf::Vector2f relativePosition);

	void GenerateRandomShape(int squaresAmount = 4);

	sf::Vector2f GetStaticPosition();
	void SetStaticPosition(sf::Vector2f newPosition);

	void SetPosition(sf::Vector2f newPosition);

	void SetScene(Scene* newScene);

	void Replace() { hasBeenReplaced = true; }

	bool HasBeenReplaced() { return hasBeenReplaced; }

	int GetSquareNb() { return composingSquares.size(); }

	Square* GetSquare(int index)
	{
		return composingSquares[index];
	}

	Square* GetBaseSquare();

	void RotateClockwise();

	void RotateCounterClockwise();

	void SetSquareSize(float newSquareWidth);

	void CancelDrag();

	bool IsRelativePositionOccupied(sf::Vector2f relativePosition);

	bool IsMouseInside(sf::Vector2i mousePosition);

	void UpdateTetrominoCenter();

	void SetActive(bool active);
};