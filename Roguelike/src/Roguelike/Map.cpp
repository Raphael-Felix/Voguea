#include "Map.h"

#include "Button.h"
#include "MainScene.h"
#include "GameManager.h"
#include "GameStateCombat.h"
#include "GameStateEvent.h"
#include "Debug.h"
#include "Data.h"
#include "Run.h"

#include <iostream>

// Step

Step::~Step()
{
	linkedButton->Destroy();
}

void Step::SetIsUnlocked(float newIsUnlocked)
{
	isUnlocked = newIsUnlocked;
}

bool Step::CanEnterStep()
{
	return isUnlocked;
}

void Step::EnterStep()
{
	if (CanEnterStep() == true)
		Data::GetInstance()->currentRun->map->currentStep->ExitStep();
	else
		return;

	Data::GetInstance()->currentRun->map->currentStep = this;

	isUnlocked = true;

	for (Step* step : nextLinkedSteps)
		step->SetIsUnlocked(true);

	switch (stepType)
	{
	case StepType::beginning:
		break;
	case StepType::boss:
		break;
	case StepType::combat:
		dynamic_cast<MainScene*>(GameManager::Get()->GetScene())->LoadGameState<GameStateCombat>();
		Data::GetInstance()->currentRun->m_currentLevelIndex += 1;
		break;
	case StepType::event:
		dynamic_cast<MainScene*>(GameManager::Get()->GetScene())->LoadGameState<GameStateEvent>();
		break;
	default:
		break;
	}
}

void Step::ExitStep()
{
	isUnlocked = false;

	std::cout << isUnlocked << std::endl;

	for (Step* step : nextLinkedSteps)
		step->SetIsUnlocked(false);
}

// Map

Map::Map()
{
	currentStep = nullptr;
}

Map::~Map()
{
	for (Step* step : content)
		delete step;
}

void Map::CreateRandomMap(int stagesAmount, int stagesMaxWidth, float emptyProbability, float eventProbability)
{
	// Debut
	Step* firstStep = Map::CreateStep(StepType::beginning, {}, true);
	currentStep = firstStep;

	// Etapes
	int randomInt;
	StepType randomType;
	std::vector<Step*> precedingSteps = { firstStep };
	std::vector<Step*> currentStageSteps;

	for (int i = 0; i < stagesAmount; i++)
	{
		for (int j = 0; j < stagesMaxWidth; j++)
		{
			randomInt = rand() % 100 + 1;

			if (randomInt <= emptyProbability)
				if (!(j >= stagesMaxWidth - 1 && currentStageSteps.size() == 0))
					continue;

			randomInt = rand() % 100 + 1;

			/*if (randomInt <= eventProbability)
			{
				currentStageSteps.push_back(Map::CreateStep(StepType::event, {}, false));
				continue;
			}*/

			currentStageSteps.push_back(Map::CreateStep(StepType::combat, {}, false));
		}

		// Pour chaque etape cree, ajouter un lien vers une etape du stage d'en dessous
		for (Step* step : currentStageSteps)
		{
			randomInt = rand() % precedingSteps.size();

			step->precedingLinkedSteps.push_back(precedingSteps[randomInt]);
			precedingSteps[randomInt]->nextLinkedSteps.push_back(step);
		}

		// Pour chaque etape cree sur la boucle d'avant, ajouter un lien vers une etape cree cette boucle
		for (Step* step : precedingSteps)
		{
			randomInt = rand() % currentStageSteps.size();

			if (std::find(step->nextLinkedSteps.begin(), step->nextLinkedSteps.end(), step) == step->nextLinkedSteps.end())
			{
				step->nextLinkedSteps.push_back(currentStageSteps[randomInt]);
				currentStageSteps[randomInt]->precedingLinkedSteps.push_back(step);
			}
		}

		precedingSteps.clear();
		precedingSteps = currentStageSteps;
		currentStageSteps.clear();
	}

	// Boss
	Step* boss = Map::CreateStep(StepType::boss, precedingSteps, true);

	for (Step* step : firstStep->nextLinkedSteps)
		step->SetIsUnlocked(true);

	// Positionnement des boutons
	UpdateButtonsPositions();

	// Offset maximum
	maxOffset = fmaxf(0, (stagesAmount - 8) * 150);
}

Step* Map::CreateStep(StepType stepType, std::vector<Step*> precedingSteps, bool isUnlocked)
{
	Step* newStep = new Step(stepType, precedingSteps, {}, isUnlocked);

	for (Step* precedingStep : precedingSteps)
	{
		if (std::find(precedingStep->nextLinkedSteps.begin(), precedingStep->nextLinkedSteps.end(), newStep) == precedingStep->nextLinkedSteps.end())
			precedingStep->nextLinkedSteps.push_back(newStep);
	}

	std::string imagePath;

	switch (stepType)
	{
	case StepType::beginning:
		imagePath = "../../../res/assets/Steps/doorway.png";
		break;
	case StepType::boss:
		imagePath = "../../../res/assets/Steps/skull2.png";
		break;
	case StepType::combat:
		imagePath = "../../../res/assets/Steps/skull.png";
		break;
	case StepType::event:
		imagePath = "../../../res/assets/Steps/dice.png";
		break;
	default:
		break;
	}

	newStep->linkedButton = GameManager::Get()->GetScene()->CreateSprite<Button>(50, 50, imagePath, nullptr);
	newStep->linkedButton->Initialize("", std::bind(&Step::EnterStep, newStep));

	content.push_back(newStep);

	return newStep;
}

void Map::AddStep(Step* newStep)
{
	content.push_back(newStep);
}

void Map::UpdateButtonsPositions()
{
	std::map<Step*, bool> visited;
	std::map<int, std::vector<Step*>> levels;

	std::vector<std::pair<Step*, int>> queue;
	queue.push_back({ currentStep, 0 });

	while (!queue.empty())
	{
		auto [node, depth] = queue.front();
		queue.erase(queue.begin());

		if (!node || visited[node])
			continue;

		visited[node] = true;
		levels[depth].push_back(node);

		for (Step* child : node->nextLinkedSteps)
		{
			if (child)
				queue.push_back({ child, depth + 1 });
		}
	}

	// Placement
	int count;
	float x;
	float y;
	sf::Vector2f offset = {100.f, GameManager::Get()->mWindowHeight / 2.f };
	for (auto& [depth, nodes] : levels)
	{
		count = nodes.size();

		for (int i = 0; i < count; i++)
		{
			x = depth * 150 + offset.x;
			y = (i - (count - 1) / 2.f) * 100 + offset.y;

			nodes[i]->linkedButton->SetPosition(x, y);
		}
	}
}

void Map::DisplayButtonsConnections()
{
	for (Step* step : content)
	{
		sf::Vector2f parentPos = step->linkedButton->GetPosition();

		for (Step* otherStep : step->nextLinkedSteps)
		{
			sf::Vector2f childPos = otherStep->linkedButton->GetPosition();

			sf::Color lineColor = (step->isUnlocked && otherStep->isUnlocked) ? sf::Color(200, 200, 200, 220) : sf::Color(90, 90, 90, 180);

			Debug::DrawLine(parentPos.x, parentPos.y, childPos.x, childPos.y, lineColor);
		}
	}
}

void Map::ShowMap()
{
	for (Step* step : content)
		step->linkedButton->SetActive(true);
}

void Map::HideMap()
{
	for (Step* step : content)
		step->linkedButton->SetActive(false);
}

void Map::OffsetButtons(float value)
{
	value = fmax(0, fmin(maxOffset, currentOffset + value)) - currentOffset;

	sf::Vector2f position;
	for (Step* step : content)
	{
		position = step->linkedButton->GetPosition();

		step->linkedButton->SetPosition(position.x - value, position.y);
	}

	currentOffset += value;
}
