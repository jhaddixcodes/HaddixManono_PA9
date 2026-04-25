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
	const vector<Card>& getCards() const;

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
	* @brief Calculates the number of points of the hand.
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