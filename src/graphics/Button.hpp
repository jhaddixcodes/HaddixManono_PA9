/*
	Author: Lyon Manono
	Written: Apr 23 2026
	Last Updated: Apr 23 2026
	Description: Clickable Button class that inherits from GameObject
	Note: Centered text math in draw() generated with Claude.
	Prompt: "How do I center sf::Text inside a rectangle in SFML 3,
	accounting for getLocalBounds offset"
*/

#ifndef BUTTON_HPP
#define BUTTON_HPP

#include "GameObject.hpp"
#include <SFML/Graphics.hpp>
#include <string>

// A clickable button with a text label
// Used for Hit / Stand / Deal
class Button : public GameObject
{
public:
	Button();
	Button(std::string label, float x, float y, float width, float height);
	~Button();

	// overridden from GameObject
	void draw(sf::RenderWindow& window) override;

	// checks if the given mouse position is inside this button
	bool isClicked(int mouseX, int mouseY);

	void setLabel(std::string label);
	void setFont(sf::Font* font);

private:
	std::string buttonLabel;
	float buttonWidth;
	float buttonHeight;
	sf::Font* pFont;  // not owned
};

#endif
