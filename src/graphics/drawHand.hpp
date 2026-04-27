/*
	Author: James Haddix, Lyon Manono
	Written: Apr 26 2026
	Last Updated: Apr 26 2026
	Description: Functions for drawing a participant's hand on a window centered on a position.
*/

#ifndef DRAWHAND_HPP
#define DRAWHAND_HPP

#include <SFML/Graphics.hpp>
#include <vector>
#include "../game_logic/Hand.hpp"

using std::vector;

/**
* @brief Draws card in the window centered at (x, y)
*/
void drawCard(sf::RenderWindow& window, const Card& card, sf::Font* pFont, float x, float y);

/**
* @brief Draws hand in the window centered at (x, y)
*/
void drawHand(sf::RenderWindow& window, const vector<Card>& cards, sf::Font* pFont, float x, float y);

#endif