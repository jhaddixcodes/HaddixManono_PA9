#pragma once
#ifndef CARD_H
#define CARD_H

#include "GameObject.h"
#include <SFML/Graphics.hpp>
#include <string>

// A playing card that knows how to draw itself

// rank: 1=Ace, 2-10 = number cards, 11=Jack, 12=Queen, 13=King
// suit: 0=Hearts, 1=Diamonds, 2=Clubs, 3=Spades
class Card : public GameObject
{
public:
	Card();
	Card(int rank, int suit, float x, float y);
	~Card();

	// overridden from GameObject
	void draw(sf::RenderWindow& window);

	// setters for the logic side to use
	void setRank(int rank);
	void setSuit(int suit);
	void setFaceUp(bool up);
	void setFont(sf::Font* font);

	// getters
	int getRank();
	int getSuit();
	bool isFaceUp();

private:
	int cardRank;
	int cardSuit;
	bool faceUp;
	sf::Font* pFont;  // not owned, just a pointer to a font loaded in main

	// helpers for drawing
	std::string getRankString();
	std::string getSuitString();
	sf::Color getSuitColor();
};

#endif