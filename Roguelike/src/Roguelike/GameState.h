#pragma once

#include <vector>
#include <SFML/Window/Window.hpp>

class MainScene;
class Data;
class Sounds;
class Entity;
class Button;

class GameState
{
protected:
    MainScene* scene;

    Data* data;

    Sounds* randomSounds;

    std::vector<Entity*> entities;

    std::vector<Button*> buttons;

public:
    GameState();
    ~GameState();

	virtual void Initialize() = 0;

	virtual void OnEvent(const sf::Event& event) = 0;
    virtual void OnUpdate() = 0;

    virtual void EnableButtons();
    virtual void DisableButtons();

    void OnEnterState();
    void OnExitState();

protected:
    virtual void EnterState();
    virtual void ExitState();
};
