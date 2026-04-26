#pragma once
#ifndef BUTTON_H
#define BUTTON_H

#include "GameObject.h"
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
	void draw(sf::RenderWindow& window);

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