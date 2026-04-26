#pragma once
#ifndef GAME_OBJECT_H
#define GAME_OBJECT_H

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