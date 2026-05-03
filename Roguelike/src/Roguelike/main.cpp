#include <SFML/Graphics.hpp>
#include <iostream>

#include "GameManager.h"
#include "MainScene.h"

#include <cstdlib>
#include <crtdbg.h>
int main()
{
#ifdef _DEBUG
	_CrtDumpMemoryLeaks();
#endif

	GameManager* pInstance = GameManager::Get();

	pInstance->CreateWindow(1280, 720, "Roguelike", 60, sf::Color(17, 28, 60));

	pInstance->LaunchScene<MainScene>();

	return 0;
	
	return 0;
}
