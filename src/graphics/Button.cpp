#include "Button.hpp"

Button::Button()
{
	buttonLabel = "";
	buttonWidth = 100.f;
	buttonHeight = 40.f;
	pFont = nullptr;
	xPos = 0;
	yPos = 0;
}

Button::Button(std::string label, float x, float y, float width, float height)
{
	buttonLabel = label;
	buttonWidth = width;
	buttonHeight = height;
	pFont = nullptr;
	xPos = x;
	yPos = y;
}

Button::~Button()
{
}

void Button::setLabel(std::string label)
{
	buttonLabel = label;
}

void Button::setFont(sf::Font* font)
{
	pFont = font;
}

// returns true if the mouse is inside the button's rectangle
bool Button::isClicked(int mouseX, int mouseY)
{
	if (mouseX >= xPos && mouseX <= xPos + buttonWidth)
	{
		if (mouseY >= yPos && mouseY <= yPos + buttonHeight)
		{
			return true;
		}
	}
	return false;
}

void Button::draw(sf::RenderWindow& window)
{
	// button background
	sf::RectangleShape btnShape(sf::Vector2f(buttonWidth, buttonHeight));
	btnShape.setPosition(sf::Vector2f(xPos, yPos));
	btnShape.setFillColor(sf::Color(200, 200, 200));
	btnShape.setOutlineThickness(2.f);
	btnShape.setOutlineColor(sf::Color::Black);
	window.draw(btnShape);

	// skip the label if we don't have a font
	if (pFont == nullptr)
	{
		return;
	}

	// label text, centered in the button
	sf::Text label(*pFont);
	label.setString(buttonLabel);
	label.setCharacterSize(18);
	label.setFillColor(sf::Color::Black);

	sf::FloatRect textBounds = label.getLocalBounds();
	float textX = xPos + (buttonWidth - textBounds.size.x) / 2.f - textBounds.position.x;
	float textY = yPos + (buttonHeight - textBounds.size.y) / 2.f - textBounds.position.y;
	label.setPosition(sf::Vector2f(textX, textY));

	window.draw(label);
}