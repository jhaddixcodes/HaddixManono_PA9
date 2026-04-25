#include "Card.hpp"

Card::Card(Suit suit, string symbol) : m_suit(suit), m_symbol(symbol), m_points(0)
{
	// constructor written by Claude
	if (m_symbol == "10")
	{
		m_points = 10;
	}
	else
	{
		switch (m_symbol[0])
		{
			case '2': m_points = 2; break;
			case '3': m_points = 3; break;
			case '4': m_points = 4; break;
			case '5': m_points = 5; break;
			case '6': m_points = 6; break;
			case '7': m_points = 7; break;
			case '8': m_points = 8; break;
			case '9': m_points = 9; break;
			case 'J': m_points = 10; break;
			case 'Q': m_points = 10; break;
			case 'K': m_points = 10; break;
			case 'A': m_points = 11; break;
		}
	}
}

Suit Card::getSuit() const
{
	return m_suit;
}

string Card::getSymbol() const
{
	return m_symbol;
}

int Card::getCardValue() const
{
	return m_points;
}