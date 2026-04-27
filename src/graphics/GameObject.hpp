/*
	Author: Lyon Manono
	Written: Apr 23 2026
	Last Updated: Apr 23 2026
	Description: GameObject ABC that can be drawn at any position on the window
*/

#ifndef GAME_OBJECT_HPP
#define GAME_OBJECT_HPP

#include <SFML/Graphics.hpp>

// base class for anything that gets drawn on screen
// cards and buttons both inherit from this
class GameObject
{
public:
	GameObject();
	GameObject(float x, float y);
	virtual ~GameObject();

	// each derived class has to define how it draws itself
	virtual void draw(sf::RenderWindow& window) = 0;

	// position helpers
	float getX();
	float getY();
	void setPosition(float x, float y);

protected:
	float xPos;
	float yPos;
};

#endif