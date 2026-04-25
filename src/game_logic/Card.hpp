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
	Card(Suit suit, string symbol);

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

private:
	Suit m_suit;
	string m_symbol;
	int m_points;
};

#endif