#include "Tetromino.h"

#include "Scene.h"
#include "AABBCollider.h"
#include <cstdlib>

#include <SFML/System/Vector2.hpp>

Tetromino::Tetromino(Scene* scene, int sWidth) :
	scene(scene)
{
	position = { 0, 0 };

	squareWidth = sWidth;
}

Tetromino::~Tetromino()
{
	for (Square* square : composingSquares)
		square->entity->Destroy();

	composingSquares.clear();
}

void Tetromino::AddSquare(sf::Vector2f relativePosition)
{
	if (scene == nullptr)
		return;

	Entity* newEntity = scene->CreateRectangle<Entity>(squareWidth, squareWidth, sf::Color::White, nullptr);
	newEntity->GetShape()->setOutlineThickness(1);
	newEntity->GetShape()->setOutlineColor(sf::Color::Black);

	sf::Vector2f tempPosition = position + (relativePosition * squareWidth);
	newEntity->SetPosition(tempPosition.x, tempPosition.y);

	composingSquares.push_back(new Square{ newEntity, relativePosition });
}

void Tetromino::GenerateRandomShape(int squaresAmount)
{
	if (squaresAmount <= 0)
		return;

	sf::Vector2f squarePosition = { 0, 0 };

	AddSquare(squarePosition);

	float randNumber;

	for (int i = 1; i < squaresAmount;)
	{
		randNumber = rand() % 2;
		if (randNumber == 0)
			squarePosition.x += (rand() % 2 - 0.5f) * 2;
		else
			squarePosition.y += (rand() % 2 - 0.5f) * 2;

		if (IsRelativePositionOccupied(squarePosition) != true)
		{
			i++;
			AddSquare(squarePosition);
		}
	}

	UpdateTetrominoCenter();
}

sf::Vector2f Tetromino::GetStaticPosition()
{
	return staticPosition;
}

void Tetromino::SetStaticPosition(sf::Vector2f newPosition)
{
	staticPosition = newPosition;
}

void Tetromino::SetPosition(sf::Vector2f newPosition)
{
	position = newPosition;

	for (Square* currentSquare : composingSquares)
	{
		sf::Vector2f tempPosition = newPosition + (currentSquare->squareRelativePosition * squareWidth);

		currentSquare->entity->SetPosition(tempPosition.x, tempPosition.y);
	}
}

void Tetromino::SetScene(Scene* newScene)
{
	scene = newScene;
}

Square* Tetromino::GetBaseSquare()
{
	for (int i = 0; i < composingSquares.size(); ++i)
	{
		if (composingSquares[i]->squareRelativePosition == sf::Vector2f{ 0.f, 0.f })
			return composingSquares[i];
	}
}

void Tetromino::RotateClockwise()
{
	for (Square* currentSquare : composingSquares)
	{
		sf::Vector2f* relativePosition = &currentSquare->squareRelativePosition;

		float tempX = relativePosition->x;

		relativePosition->x = relativePosition->y;
		relativePosition->y = -tempX;
	}

	SetPosition(position);
}

void Tetromino::RotateCounterClockwise()
{
	for (Square* currentSquare : composingSquares)
	{
		sf::Vector2f* relativePosition = &currentSquare->squareRelativePosition;

		float tempY = relativePosition->y;

		relativePosition->y = relativePosition->x;
		relativePosition->x = -tempY;
	}

	SetPosition(position);
}

void Tetromino::SetSquareSize(float newSquareWidth)
{
	squareWidth = newSquareWidth;

	for (Square* currentSquare : composingSquares)
	{
		currentSquare->entity->Resize(newSquareWidth, newSquareWidth);
	}
}

void Tetromino::CancelDrag()
{
	SetPosition(staticPosition);
}

bool Tetromino::IsRelativePositionOccupied(sf::Vector2f relativePosition)
{
	for (Square* currentSquare : composingSquares)
	{
		if (currentSquare->squareRelativePosition == relativePosition)
			return true;
	}

	return false;
}

bool Tetromino::IsMouseInside(sf::Vector2i mousePosition)
{
	for (Square* currentSquare : composingSquares)
	{
		if (currentSquare->entity->IsInside((float)mousePosition.x, (float)mousePosition.y))
			return true;
	}

	return false;
}

void Tetromino::UpdateTetrominoCenter()
{
	if (composingSquares.size() <= 0)
		return;

	sf::Vector2f center = { 0, 0 };

	for (Square* currentSquare : composingSquares)
		center += currentSquare->squareRelativePosition;

	center.x /= composingSquares.size();
	center.y /= composingSquares.size();

	Square* centerSquare = composingSquares[0];
	sf::Vector2f distance = composingSquares[0]->squareRelativePosition - center;
	float dist = sqrtf(powf(distance.x, 2) + powf(distance.y, 2));
	float smallestDistance = dist;

	for (Square* currentSquare : composingSquares)
	{
		distance = currentSquare->squareRelativePosition - center;
		dist = sqrtf(powf(distance.x, 2) + powf(distance.y, 2));

		if (dist < smallestDistance)
		{
			smallestDistance = dist;
			centerSquare = currentSquare;
		}
	}

	sf::Vector2f offset = -centerSquare->squareRelativePosition;

	for (Square* currentSquare : composingSquares)
		currentSquare->squareRelativePosition += offset;
}

void Tetromino::SetActive(bool active)
{
	for (Square* currentSquare : composingSquares)
		currentSquare->entity->SetActive(active);
}
