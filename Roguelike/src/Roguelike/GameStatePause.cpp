#include "GameStatePause.h"

#include "Button.h"
#include "MainScene.h"
#include "GameStateMainMenu.h"
#include "SoundManager.h"
#include "Debug.h"

GameStatePause::GameStatePause()
{
	m_soundManager = SoundManager::GetInstance();
}

void GameStatePause::Initialize()
{
	int windowWidth = scene->GetWindowWidth();
	int windowHeight = scene->GetWindowHeight();

	// Background menu principal
	{

		Entity * backgroundEntity = scene->CreateSprite<Entity>(windowWidth, windowHeight, "../../../res/assets/Backgrounds/Night-Sky/1.png", nullptr);
		backgroundEntity->SetPosition(windowWidth / 2, windowHeight / 2, 0.5f, 0.5f);
		entities.push_back(backgroundEntity);

		backgroundEntity = scene->CreateSprite<Entity>(windowWidth, windowHeight, "../../../res/assets/Backgrounds/Night-Sky/2.png", nullptr);
		backgroundEntity->SetPosition(windowWidth / 2, windowHeight / 2, 0.5f, 0.5f);
		entities.push_back(backgroundEntity);

		backgroundEntity = scene->CreateSprite<Entity>(windowWidth, windowHeight, "../../../res/assets/Backgrounds/Night-Sky/3.png", nullptr);
		backgroundEntity->SetPosition(windowWidth / 2, windowHeight / 2, 0.5f, 0.5f);
		entities.push_back(backgroundEntity);

		backgroundEntity = scene->CreateSprite<Entity>(windowWidth, windowHeight, "../../../res/assets/Backgrounds/Night-Sky/4.png", nullptr);
		backgroundEntity->SetPosition(windowWidth / 2, windowHeight / 2, 0.5f, 0.5f);
		entities.push_back(backgroundEntity);
	}

	// Boutons du menu des parametres
	{
		Button* tempButton = scene->CreateRectangle<Button>(50, 50, sf::Color::Transparent, nullptr);
		tempButton->Initialize("-", std::bind(&GameStatePause::DecreaseEffectSound, this));
		tempButton->SetPosition(windowWidth - 900, windowHeight - 600, 0.5f, 0.5f);
		tempButton->SetActive(false);
		buttons.push_back(tempButton);

		tempButton = scene->CreateRectangle<Button>(50, 50, sf::Color::Transparent, nullptr);
		tempButton->Initialize("+", std::bind(&GameStatePause::IncreaseEffectSound, this));
		tempButton->SetPosition(windowWidth - 400, windowHeight - 600, 0.5f, 0.5f);
		tempButton->SetActive(false);
		buttons.push_back(tempButton);

		tempButton = scene->CreateRectangle<Button>(50, 50, sf::Color::Transparent, nullptr);
		tempButton->Initialize("-", std::bind(&GameStatePause::DecreaseMusicSound, this));
		tempButton->SetPosition(windowWidth - 900, windowHeight - 400, 0.5f, 0.5f);
		tempButton->SetActive(false);
		buttons.push_back(tempButton);

		tempButton = scene->CreateRectangle<Button>(50, 50, sf::Color::Transparent, nullptr);
		tempButton->Initialize("+", std::bind(&GameStatePause::IncreaseMusicSound, this));
		tempButton->SetPosition(windowWidth - 400, windowHeight - 400, 0.5f, 0.5f);
		tempButton->SetActive(false);
		buttons.push_back(tempButton);

		tempButton = scene->CreateRectangle<Button>(120, 50, sf::Color::Transparent, nullptr);
		tempButton->Initialize("Quitter", std::bind(&MainScene::QuitApp, scene));
		tempButton->SetPosition(windowWidth / 2, windowHeight - 100, 0.5f, 0.5f);
		tempButton->SetActive(false);
		buttons.push_back(tempButton);

		tempButton = scene->CreateRectangle<Button>(250, 50, sf::Color::Transparent, nullptr);
		tempButton->Initialize("Retour", std::bind(&MainScene::ShowLastState, scene));
		tempButton->SetPosition(10, 10, 0.f, 0.f);
		tempButton->SetActive(false);
		buttons.push_back(tempButton);

		// Bouton Retour au menu
		{
			/*tempButton = scene->CreateRectangle<Button>(250, 50, sf::Color::Transparent, nullptr);
			tempButton->Initialize("Retour au menu", std::bind(&MainScene::LoadGameState<GameStateMainMenu>, scene));
			tempButton->SetPosition(windowWidth / 2, windowHeight - 200, 0.5f, 0.5f);
			buttons.push_back(tempButton);*/
		}
	}
}

void GameStatePause::OnEvent(const sf::Event& event)
{
}

void GameStatePause::OnUpdate()
{
	// Affichage texte pour parametres
	if (m_soundManager != nullptr)
	{
		Debug* debug = Debug::Get();

		debug->DrawText(scene->GetWindowWidth() / 2, scene->GetWindowHeight() - 600, "Volume des bruitages : " + std::to_string(*m_soundManager->GetSoundVolume()), 0.5f, 0.5f, sf::Color::White, 30);
		debug->DrawText(scene->GetWindowWidth() / 2, scene->GetWindowHeight() - 400, "Volume de la musique : " + std::to_string(*m_soundManager->GetMusicVolume()), 0.5f, 0.5f, sf::Color::White, 30);
	}
}

void GameStatePause::EnterState()
{
}

void GameStatePause::ExitState()
{
}

void GameStatePause::IncreaseEffectSound()
{
	m_soundManager->ChangeSoundVolume(10);
}

void GameStatePause::DecreaseEffectSound()
{
	m_soundManager->ChangeSoundVolume(-10);
}

void GameStatePause::IncreaseMusicSound()
{
	m_soundManager->ChangeMusicVolume(5);
}

void GameStatePause::DecreaseMusicSound()
{
	m_soundManager->ChangeMusicVolume(-5);
}
