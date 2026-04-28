/*
	Author: Claude, James Haddix
	Written: Apr 24 2026
	Last Updated: Apr 26 2026
	Description: Simple Card class holding a suit and symbol that can be hidden or shown.
*/

#ifndef CARD_HPP
#define CARD_HPP

#include <string>

using std::string;

enum class Suit
{
	SPADE, HEART, DIAMOND, CLUB
};

class Card
{
public:

	/**
	* @brief Constructs a new card and calculates its point value from its symbol.
	* @param suit SPADE, HEART, DIAMOND, or CLUB
	* @param symbol String that can be anything 2-10, J, Q, K, or A.
	*/
	Card(Suit suit, string symbol, bool hidden);

	/**
	* @return The card's suit.
	*/
	Suit getSuit() const;

	/**
	* @return The card's symbol.
	*/
	string getSymbol() const;

	/**
	* @return The card's point value.
	*/
	int getCardValue() const;

	/**
	* @return true if the card is currently hidden, false otherwise.
	*/
	bool getHidden() const;

	/**
	* @brief Set whether the card is hidden or not
	*/
	void setHidden(bool hidden);

private:
	Suit m_suit;
	string m_symbol;
	int m_points;
	bool m_hidden;
};

#endif