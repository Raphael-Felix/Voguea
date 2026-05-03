#include "Button.h"

#include "Debug.h"
#include "SoundManager.h"

#include "SFML/Graphics/Shape.hpp"
#include "SFML/Window.hpp"
#include "SFML/Graphics.hpp"

void Button::OnUpdate()
{
	if (mActive)
	{
		m_waitDelay += GetDeltaTime();

		sf::Vector2f position = GetPosition(0.5f, 0.5f);

		Debug::DrawText(position.x, position.y, m_text, 0.5f, 0.5f, m_textColor, m_charSize);

		if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left) && m_clickable)
		{
			sf::Vector2i mousePos = sf::Mouse::getPosition(*dynamic_cast<sf::Window*>(GameManager::Get()->mpWindow));

			if (IsInside(mousePos.x, mousePos.y) && m_waitDelay >= 0.25f)
			{
				OnClicked();
				m_waitDelay = 0.f;
			}
		}
	}
}

void Button::OnClicked()
{
	if (m_behaviour == nullptr)
		return;

	int soundNumber = rand() % 1 + 1;

	SoundManager::GetInstance()->PlaySound("../../../res/sounds/click" + std::to_string(soundNumber) + ".wav");

	m_behaviour();
}

void Button::Initialize(std::string text, std::function<void()> function, int charSize, int outlineThickness, sf::Color color, void* variable)
{
	SetText(text);
	SetCharSize(charSize);
	SetTextColor(color);
	if (sf::Shape* shape = GetShape())
		shape->setOutlineThickness(outlineThickness);
	m_behaviour = function;
	m_variable = variable;
}