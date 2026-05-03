#pragma once
#include "Entity.h"

#include <functional>

class Button :
    public Entity
{
protected:
    std::string m_text = "";
    sf::Color m_textColor = sf::Color::White;

    float m_waitDelay = 0.f;

    int m_charSize = 20;

    bool m_clickable = true;

    void* m_variable;

    std::function<void()> m_behaviour;

public:
    void OnUpdate() override;
    void OnClicked();

    void Initialize(std::string text, std::function<void()> function, int charSize = 30, int outlineThickness = 1, sf::Color color = sf::Color::White, void* variable = nullptr);

    void SetClickable(bool clickable) { m_clickable = clickable; }

    void SetText(std::string text) { m_text = text; }
    std::string GetText() { return m_text; }

    void SetCharSize(int size) { m_charSize = size; }

    void SetTextColor(sf::Color color) { m_textColor = color; }
};

