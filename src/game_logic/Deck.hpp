#ifndef DECK_HPP
#define DECK_HPP

#include <vector>

using std::vector;

enum class Suit
{
	SPADE, HEART, DIAMOND, CLUB
};

struct Card 
{
	Suit suit;
	string symbol;
};

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
	Card dealCard();

	/**
	* @brief Checks if the deck is empty.
	* @return true if deck has no cards left, false otherwise.
	*/
	bool isEmpty();

private:
	vector<Card> m_cards;
};

class Hand 
{
public:

	/**
	* @brief Constructs an empty hand.
	*/
	Hand();

	/**
	* @brief Calculates the number of points of the hand.
	* @return The maximum amount of points without going over 21.
	*/
	int calculatePoints();

	/**
	* @brief Checks if the hand is bust.
	* @return true if points above 21, false otherwise.
	*/
	bool isBust();

	/**
	* @brief Checks if the hand is 21.
	* @return true if points are 21, false otherwise.
	*/
	bool isTwentyOne();

private:
	vector<Card> m_cards;
};

#endif