#include "GameObject.h"

// default constructor, just zero out the position
GameObject::GameObject()
{
	xPos = 0;
	yPos = 0;
}

// constructor with a starting position
GameObject::GameObject(float x, float y)
{
	xPos = x;
	yPos = y;
}

// virtual destructor so derived classes clean up right
GameObject::~GameObject()
{
}

float GameObject::getX()
{
	return xPos;
}

float GameObject::getY()
{
	return yPos;
}

void GameObject::setPosition(float x, float y)
{
	xPos = x;
	yPos = y;
}