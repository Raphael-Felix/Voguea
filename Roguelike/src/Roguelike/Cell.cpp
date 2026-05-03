#include "Cell.h"
#include <SFML/Graphics/RectangleShape.hpp>

void Cell::OnInitialize()
{
	GetShape()->setFillColor(sf::Color::Transparent);
	GetShape()->setOutlineThickness(1.f);
}
