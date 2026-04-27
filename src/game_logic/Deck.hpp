/*
	Author: James Haddix
	Written: Apr 24 2026
	Last Updated: Apr 24 2026
	Description: Deck class with shuffled Cards that can be taken out. This wraps a vector of Cards.
*/

#ifndef DECK_HPP
#define DECK_HPP

#include <vector>

#include "Card.hpp"

using std::vector;

class Deck 
{
public:

	/**
	* @brief Constructs a new deck and shuffles it.
	*/
	Deck();

	/**
	* @brief Gets the card from the end of the deck and removes it from the deck.
	* @return The card at the end of the deck.
	* @pre Deck must not be empty.
	*/
	const Card getCard();

	/**
	* @brief Checks if the deck is empty.
	* @return true if deck's size is 0, false otherwise.
	*/
	bool isEmpty() const;

private:
	vector<Card> m_cards;
};

#endif