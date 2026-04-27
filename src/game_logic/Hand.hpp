/*
	Author: James Haddix
	Written: Apr 24 2026
	Last Updated: Apr 26 2026
	Description: Hand class that wraps a vector of Cards (I think that's the right term).
*/

#ifndef HAND_HPP
#define HAND_HPP

#include <vector>

#include "Card.hpp"

using std::vector;

class Hand
{
public:

	/**
	* @brief Constructs an empty hand.
	*/
	Hand() = default;

	/**
	* @return Returns the current hand as a vector of cards.
	*/
	vector<Card>& getCards();

	/**
	* @brief Adds a card to the deck.
	* @param card The card to add.
	*/
	void addCard(const Card card);

	/**
	* @brief Empties the hand completely.
	*/
	void empty();

	/**
	* @brief Calculates the number of points of the hand from cards that are face up.
	* @return The amount of points closest to 21.
	*/
	int calculatePoints() const;

	/**
	* @return true if points above 21, false otherwise.
	*/
	bool isBust() const;

	/**
	* @return true if points are 21, false otherwise.
	*/
	bool isTwentyOne() const;

private:
	vector<Card> m_cards;
};

#endif