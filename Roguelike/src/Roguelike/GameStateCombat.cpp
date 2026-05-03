#include "GameStateCombat.h"

#include "GameStatePause.h"
#include "GameStateReward.h"
#include "GameStateMap.h"
#include "GameStateMainMenu.h"

#include "SFML/Graphics.hpp"

#include "GameManager.h"
#include "Entity.h"
#include "Sounds.h"
#include "Debug.h"

#include "MainScene.h"
#include "Grid.h"
#include "Button.h"
#include "Tetromino.h"
#include "Player.h"
#include "Enemy.h"

#include "Data.h"
#include "Run.h"
#include "Utils.h"

void GameStateCombat::Initialize()
{
	int windowWidth = scene->GetWindowWidth();
	int windowHeight = scene->GetWindowHeight();

	//Backgrounds
	{
		Entity* backgroundEntity = scene->CreateSprite<Entity>(windowWidth, windowHeight / 2 + 100, "../../../res/assets/Backgrounds/Combat/Castle.png", nullptr);
		backgroundEntity->SetPosition(windowWidth / 2, windowHeight / 2 - 100, 0.5f, 1.f);
		m_backgrounds.push_back(backgroundEntity);

		backgroundEntity = scene->CreateSprite<Entity>(windowWidth, windowHeight / 2 + 100, "../../../res/assets/Backgrounds/Combat/4.png", nullptr);
		backgroundEntity->SetPosition(windowWidth / 2, windowHeight / 2 - 100, 0.5f, 1.f);
		m_backgrounds.push_back(backgroundEntity);

		backgroundEntity = scene->CreateSprite<Entity>(windowWidth, windowHeight / 2 + 100, "../../../res/assets/Backgrounds/Combat/3.png", nullptr);
		backgroundEntity->SetPosition(windowWidth / 2, windowHeight / 2 - 100, 0.5f, 1.f);
		m_backgrounds.push_back(backgroundEntity);

		backgroundEntity = scene->CreateSprite<Entity>(windowWidth, windowHeight / 2 + 100, "../../../res/assets/Backgrounds/Combat/2.png", nullptr);
		backgroundEntity->SetPosition(windowWidth / 2, windowHeight / 2 - 100, 0.5f, 1.f);
		m_backgrounds.push_back(backgroundEntity);

		backgroundEntity = scene->CreateSprite<Entity>(windowWidth, windowHeight / 2 + 100, "../../../res/assets/Backgrounds/Combat/1.png", nullptr);
		backgroundEntity->SetPosition(windowWidth / 2, windowHeight / 2, 0.5f, 1.f);
		m_backgrounds.push_back(backgroundEntity);

		backgroundEntity = scene->CreateSprite<Entity>(windowWidth, windowHeight / 2 + 100, "../../../res/assets/Backgrounds/Combat/0.png", nullptr);
		backgroundEntity->SetPosition(windowWidth / 2, windowHeight / 2, 0.5f, 1.f);
		m_backgrounds.push_back(backgroundEntity);
	}

	data->currentRun->m_player = scene->CreateSprite<Player>(300, 300, "../../../res/assets/Player/soldier.png", nullptr);

	//Boutons du jeu
	{
		Button* tempButton = scene->CreateRectangle<Button>(150, 50, sf::Color::Transparent, nullptr);
		tempButton->Initialize("Terminer", std::bind(&GameStateCombat::RefreshGrid, this));
		tempButton->SetPosition(windowWidth - 100, windowHeight - 60, 0.5f, 0.5f);
		buttons.push_back(tempButton);
	}

	// Autres boutons
	{
		Button* tempButton = scene->CreateRectangle<Button>(200, 50, sf::Color::Transparent, nullptr);
		tempButton->Initialize("Parametres", std::bind(&MainScene::LoadGameState<GameStatePause>, scene));
		tempButton->SetPosition(10, 10, 0.f, 0.f);
		buttons.push_back(tempButton);
	}
}

void GameStateCombat::OnEvent(const sf::Event& event)
{
	// Rotation des pieces
	if (event.type == sf::Event::KeyPressed)
	{
		if (event.key.code == sf::Keyboard::Q && data->currentRun->m_draggedTetromino != nullptr && data->currentRun->m_tetrominoRotation)
		{
			randomSounds->PlayRandomizedSound("swipe");
			data->currentRun->m_draggedTetromino->RotateClockwise();
			data->currentRun->m_draggedTetrominoRotationCount += 1;
		}
		else if (event.key.code == sf::Keyboard::D && data->currentRun->m_draggedTetromino != nullptr && data->currentRun->m_tetrominoRotation)
		{
			randomSounds->PlayRandomizedSound("swipe");
			data->currentRun->m_draggedTetromino->RotateCounterClockwise();
			data->currentRun->m_draggedTetrominoRotationCount -= 1;
		}
	}

	// Drag and drop
	if (event.type == sf::Event::MouseButtonPressed)
	{
		if (event.mouseButton.button == sf::Mouse::Left)
		{
			sf::Vector2i mousePosition = sf::Mouse::getPosition(*dynamic_cast<sf::Window*>(GameManager::Get()->mpWindow));

			if (data->currentRun->m_draggedTetromino == nullptr)
			{
				for (Tetromino* tempTetromino : data->currentRun->m_displayedTetrominos)
				{
					if (tempTetromino->IsMouseInside(mousePosition))
					{
						randomSounds->PlayRandomizedSound("click");
						data->currentRun->m_draggedTetromino = tempTetromino;

						if (data->currentRun->m_grid->Unfill(tempTetromino))
						{

						}
					}

				}
			}
			else
			{
				if (data->currentRun->m_grid->Fill(data->currentRun->m_draggedTetromino))
				{
					randomSounds->PlayRandomizedSound("click");
					

					//Get the staticPosition of the draggedTetromino and change it
					sf::Vector2f draggedTetrominoPos = data->currentRun->m_draggedTetromino->GetStaticPosition();

					data->currentRun->m_draggedTetromino->SetStaticPosition(data->currentRun->m_draggedTetromino->GetBaseSquare()->entity->GetPosition());

					data->currentRun->m_draggedTetrominoRotationCount = 0;

					if (data->currentRun->m_draggedTetromino->HasBeenReplaced() == false)
					{
						data->currentRun->m_draggedTetromino->Replace();

						data->currentRun->m_mult += std::max(1.f / ((data->currentRun->m_mult + 1.f) * 2.f), 0.1f);

						//Create new tetromino
						Tetromino* tetromino = GenerateTetromino();
						tetromino->SetPosition(sf::Vector2f(draggedTetrominoPos.x, draggedTetrominoPos.y));
						tetromino->SetStaticPosition(sf::Vector2f(draggedTetrominoPos.x, draggedTetrominoPos.y));
						tetromino->SetSquareSize(data->currentRun->m_levelSquareSize);
					}

					data->currentRun->m_draggedTetromino = nullptr;
				}
			}
		}
		else if (event.mouseButton.button == sf::Mouse::Right && data->currentRun->m_draggedTetromino != nullptr)
		{
			randomSounds->PlayRandomizedSound("click");

			for (int i = 0; i < std::abs(data->currentRun->m_draggedTetrominoRotationCount); ++i)
			{
				if (data->currentRun->m_draggedTetrominoRotationCount < 0)
					data->currentRun->m_draggedTetromino->RotateClockwise();
				else
					data->currentRun->m_draggedTetromino->RotateCounterClockwise();
			}

			data->currentRun->m_draggedTetrominoRotationCount = 0;

			data->currentRun->m_draggedTetromino->CancelDrag();

			if (data->currentRun->m_grid->Fill(data->currentRun->m_draggedTetromino))
			{
				
			}

			data->currentRun->m_draggedTetromino = nullptr;
		}
	}
}

void GameStateCombat::OnUpdate()
{
	int windowWidth = scene->GetWindowWidth();
	int windowHeight = scene->GetWindowHeight();

	float mult = Data::GetInstance()->currentRun->m_mult;

	Debug::DrawText(windowWidth / 2, 30, "Multiplicateur : x" + std::to_string(mult), 0.5f, 0.5f, sf::Color::White);

	Debug::DrawLine(0, windowHeight / 2, windowWidth, windowHeight / 2, sf::Color::White);

	// Le tetromino selectionne suis la souris
	if (data->currentRun->m_draggedTetromino != nullptr)
	{
		sf::Vector2i mousePosition = sf::Mouse::getPosition(*dynamic_cast<sf::Window*>(GameManager::Get()->mpWindow));
		data->currentRun->m_draggedTetromino->SetPosition({ (float)mousePosition.x , (float)mousePosition.y });
	}
}

void GameStateCombat::EnterState()
{
	Run* run = data->currentRun;

	run->m_enemiesToSpawn = run->m_currentLevelIndex;
	run->m_mult = 0;

	data->currentRun->GenerateTetrominosDeck();

	if (run->m_player != nullptr)
		run->m_player->SetActive(true);
	else
		run->m_player = scene->CreateSprite<Player>(300, 300, "../../../res/assets/Player/soldier.png", nullptr);
		

	if (run->m_grid != nullptr)
		run->m_grid->SetActive(true);
	else
		RefreshGrid();

	if (entities.size() <= 0)
		SpawnEnemy();

	for (Tetromino* tetromino : run->m_displayedTetrominos)
	{
		tetromino->SetActive(true);
	}

	for (Entity* entity : m_backgrounds)
	{
		entity->SetActive(true);
	}
}

void GameStateCombat::ExitState()
{
	data->currentRun->m_draggedTetromino = nullptr;
	Run* run = data->currentRun;

	if (run->m_player != nullptr)
	{
		run->m_player->SetActive(false);
	}

	if (run->m_grid != nullptr)
		run->m_grid->SetActive(false);

	for (Tetromino* tetromino : run->m_displayedTetrominos)
	{
		tetromino->SetActive(false);
	}

	for (Entity* entity : m_backgrounds)
	{
		entity->SetActive(false);
	}
}

void GameStateCombat::RefreshGrid()
{
	Run* run = data->currentRun;

	run->m_currentTurn += 1;

	if (entities.size() > 0 && run->m_player != nullptr && run->m_currentTurn > 1)
		run->m_player->Attack(dynamic_cast<Enemy*> (entities[0]), run->m_mult);

	std::vector<int> destroyEntitiesIndex;
	
	for (int i = 0; i < entities.size(); ++i)
	{
		if (Enemy* enemy = dynamic_cast<Enemy*>(entities[i]))
		{
			if (enemy->GetStat("Hp") <= 1)
			{
				enemy->Destroy();
				destroyEntitiesIndex.push_back(i);
			}
			else
			{
				enemy->PlayTurn();
			}
		}
	}

	for (int i = 0; i < destroyEntitiesIndex.size(); ++i)
	{
		entities.erase(entities.begin() + destroyEntitiesIndex[0]);
		destroyEntitiesIndex.erase(destroyEntitiesIndex.begin());
	}

	if (run->m_grid != nullptr)
	{
		if (run->m_grid->IsFull() == false)
			run->m_mult = 0;
		delete run->m_grid;
	}

	run->DestroyTetrominos();

	run->m_levelSquareSize = 50;
	run->m_grid = new Grid(4, 4, scene, run->m_levelSquareSize);

	run->m_grid->SetPosition(scene->GetWindowWidth() / 2, scene->GetWindowHeight() / 2 + 200, 0.5f, 0.5f);

	for (int i = 0; i < 3; ++i)
	{
		Tetromino* tetromino = GenerateTetromino();
		tetromino->SetPosition(sf::Vector2f(200 + (i == 0) * 800, std::min(scene->GetWindowHeight(), 100 * (i + 1) + 300 + (i == 0) * 100)));
		tetromino->SetStaticPosition(sf::Vector2f(200 + (i == 0) * 800, std::min(scene->GetWindowHeight(), 100 * (i + 1) + 300 + (i == 0) * 100)));

		tetromino->SetSquareSize(run->m_levelSquareSize);
	}

	if (run->m_player->GetStat("Hp") <= 0)
	{
		run->m_player->Destroy();
		run->m_player = nullptr;

		for (int i = 0; i < entities.size(); ++i)
		{
			entities[i]->Destroy();
		}

		entities.clear();

		scene->LoadGameState<GameStateMainMenu>();
		return;
	}

	bool canSpawn = run->m_currentTurn - run->m_lastSpawn >= run->m_spawnRate;

	if (run->m_enemiesToSpawn > 0 && canSpawn)
		SpawnEnemy();
	else if (run->m_enemiesToSpawn <= 0 && entities.size() == 0)
	{
		scene->LoadGameState<GameStateMap>();
		run->m_player->GainExp(run->m_currentLevelIndex);
	}
}

Tetromino* GameStateCombat::GenerateTetromino()
{
	if (0 >= data->currentRun->m_tetrominosBag.size())
		data->currentRun->GenerateTetrominosBag();

	MainScene* mainScene = dynamic_cast<MainScene*> (scene);

	Tetromino* tetromino = new Tetromino(mainScene);
		
	for (int j = 0; j < data->currentRun->m_tetrominosBag[0].size(); ++j)
	{
		tetromino->AddSquare(data->currentRun->m_tetrominosBag[0][j]);
	}

	data->currentRun->m_displayedTetrominos.push_back(tetromino);

	data->currentRun->m_tetrominosBag.erase(data->currentRun->m_tetrominosBag.begin());

	return tetromino;
}

void GameStateCombat::SpawnEnemy()
{
	Enemy* enemy = scene->CreateSprite<Enemy>(300, 300, "../../../res/assets/Enemies/orc.png", nullptr);
	enemy->SetPosition(scene->GetWindowWidth(), scene->GetWindowHeight() / 2, 0.5f, 0.57f);
	entities.push_back(enemy);
	//enemy->GoToPosition(scene->GetWindowWidth() - 50, scene->GetWindowHeight() / 2 - 273, 150);

	data->currentRun->m_lastSpawn = data->currentRun->m_currentTurn;
	data->currentRun->m_enemiesToSpawn -= 1;
}