#pragma once

#include <vector>

class Button;

enum class StepType
{
	beginning = 0,
	boss = 1,
	combat = 2,
	event = 3
};

struct Step
{
	StepType stepType;

	std::vector<Step*> precedingLinkedSteps;
	std::vector<Step*> nextLinkedSteps;

	bool isUnlocked;

	Button* linkedButton;

	~Step();

	void SetIsUnlocked(float newIsUnlocked);

	bool CanEnterStep();

	void EnterStep();

	void ExitStep();
};

class Map
{
private:
	std::vector<Step*> content;

	float currentOffset = 0;
	float maxOffset = 0;

public:
	Step* currentStep;

	Map();
	~Map();

	// Cree la carte aleatoirement
	// La carte contient un nombre X de stages avant d'atteindre le boss.
	// Pochaque stage, le joueur peut choisir entre Y etapes cote a cote. Il ne peut pas realiser plus d'une etape par stage.
	// Les etapes sont par defaut des combats, et au moins une etape est cree par stage.
	// 
	// - stagesAmount : nombre de stages dans la carte avant d'atteindre le boss
	// - stagesMaxWidth : nombre d'étapes maximum cote a cote par stage
	// - emptyProbability : probabilite sur 100% qu'une etape n'existe pas
	// - eventProbability : probabilite sur 100% qu'une etape existante soit un evenement
	void CreateRandomMap(int stagesAmount = 10, int stagesMaxWidth = 5, float emptyProbability = 0, float eventProbability = 0);

	// Création d'une étape
	Step* CreateStep(StepType stepType, std::vector<Step*> precedingSteps, bool isUnlocked);

	void AddStep(Step* newStep);

	// A appeler une fois la creation de la carte terminee
	void UpdateButtonsPositions();

	void DisplayButtonsConnections();

	void ShowMap();

	void HideMap();

	void OffsetButtons(float value);
};
