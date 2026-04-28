#include "Hand.hpp"

vector<Card>& Hand::getCards()
{
	return m_cards;
}

void Hand::addCard(const Card card)
{
	m_cards.push_back(card);
}

void Hand::empty()
{
	m_cards.clear();
}

int Hand::calculatePoints() const
{
	int points = 0;

	// this will let us calculate 1 vs. 11
	int numAces = 0;

	// iterate through all cards in the hand
	for (const Card& card : m_cards)
	{
		// only consider shown cards
		if (!card.getHidden())
		{
			// we keep track of how many aces so we can subtract 10s later
			if (card.getSymbol() == "A")
			{
				numAces++;
			}
			points += card.getCardValue();
		}
	}

	// if points are above 21, subtract 10 until we're out of aces. if it's above 21 still, bwomp
	while (points > 21 && numAces > 0) 
	{
		points -= 10;
		numAces--;
	}

	return points;
}

bool Hand::isBust() const
{
	return (calculatePoints() > 21);
}

bool Hand::isTwentyOne() const
{
	// when checking for 21 at the beginning of the round we disregard any hidden cards but other than that it's basically calculatePoints()
	
	int points = 0;

	// this will let us calculate 1 vs. 11
	int numAces = 0;

	// iterate through all cards in the hand
	for (const Card& card : m_cards)
	{
		// we keep track of how many aces so we can subtract 10s later
		if (card.getSymbol() == "A")
		{
			numAces++;
		}
		points += card.getCardValue();
	}

	// if points are above 21, subtract 10 until we're out of aces. if it's above 21 still, bwomp
	while (points > 21 && numAces > 0)
	{
		points -= 10;
		numAces--;
	}

	return points == 21;
}
