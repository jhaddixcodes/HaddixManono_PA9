#include "InputField.hpp"

InputField::InputField(float x, float y, float width, float height) : GameObject(x, y), m_displayWidth(width), m_displayHeight(height), m_focused(false), m_inputText(""), m_pFont(nullptr) {}
InputField::~InputField() {}

void InputField::draw(sf::RenderWindow& window)
{
	sf::RectangleShape inputBox(sf::Vector2f(m_displayWidth, m_displayHeight));
	inputBox.setPosition(sf::Vector2f(xPos, yPos));
	
	if (m_focused)
	{
		inputBox.setFillColor(sf::Color(220, 220, 220));
	}
	else {
		inputBox.setFillColor(sf::Color(150, 150, 150));
	}

	inputBox.setOutlineThickness(2.f);
	inputBox.setOutlineColor(sf::Color::Black);

	window.draw(inputBox);

	if (m_pFont == nullptr)
	{
		return;
	}

	// the text the user has entered
	sf::Text displayText(*m_pFont);
	displayText.setString(m_inputText);
	sf::FloatRect textBounds = displayText.getLocalBounds();

	float textX = xPos - textBounds.position.x;
	float textY = yPos + (m_displayHeight - textBounds.size.y) / 2.f - textBounds.position.y;
	displayText.setPosition(sf::Vector2f(textX, textY));
	
	if (m_focused)
	{
		displayText.setFillColor(sf::Color::Black);
	}
	else
	{
		displayText.setFillColor(sf::Color(50, 50, 50));
	}

	window.draw(displayText);
}

bool InputField::isClicked(int mouseX, int mouseY)
{
	if (mouseX >= xPos && mouseX <= xPos + m_displayWidth)
	{
		if (mouseY >= yPos && mouseY <= yPos + m_displayHeight)
		{
			return true;
		}
	}
	return false;
}

void InputField::handleInput(const sf::Event::TextEntered& text)
{
	if (!m_focused)
	{
		// the field isn't focused so just like...fuck, i don't know
		return;
	}

	// 8 is the unicode for backspace hopefully
	if (text.unicode == 8 && !m_inputText.empty())
	{
		// did not know you could do this. is that a bad look?
		m_inputText.pop_back();
	}
	// check if the text inputted was an integer (for the bet)
	else if (text.unicode >= '0' && text.unicode <= '9')
	{
		m_inputText += static_cast<char>(text.unicode);
	}
}

void InputField::clear()
{
	m_inputText = "";
}

bool InputField::empty()
{
	return m_inputText.empty();
}

string InputField::getText()
{
	return m_inputText;
}

bool InputField::getFocused()
{
	return m_focused;
}

void InputField::setFont(sf::Font* font)
{
	m_pFont = font;
}

void InputField::setFocused(bool focused)
{
	m_focused = focused;
}