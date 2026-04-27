#include <algorithm>
#include <stdexcept>
#include <random>

#include "Deck.hpp"

using std::random_device;
using std::mt19937;
using std::shuffle;
using std::runtime_error;

Deck::Deck()
{
	// create vectors of suits and symbols for enumerating every possible card
	std::vector<Suit> suits = {Suit::CLUB, Suit::DIAMOND, Suit::HEART, Suit::SPADE};
	std::vector<string> symbols = {"2", "3", "4", "5", "6", "7", "8", "9", "10", "J", "Q", "K", "A"};

	// this goes through every possible ocmbination of suit and symbol to get every card in the deck
	for (const Suit& suit : suits) 
	{
		for (const string& symbol : symbols) 
		{
			m_cards.push_back(Card(suit, symbol, false));
		}
	}

	// this random device represents some hardware source we can get randomness from
	std::random_device rd;
	std::mt19937 g(rd()); // called g for some reason because that's what it's called in C++'s shuffle documentation

	// shuffle the deck, begin and end are iterators which is kinda like a pointer that knows how to traverse a container
	shuffle(m_cards.begin(), m_cards.end(), g);
}

const Card Deck::getCard()
{

	// Deck must not be empty when this function is called
	if (isEmpty())
	{
		throw runtime_error("Deck is empty!");
	}

	// pop_back doesn't return anything, we use back to get the element and pop_back to delete it
	Card card = m_cards.back();
	m_cards.pop_back();

	return card;
}

bool Deck::isEmpty() const
{
	return (m_cards.empty());
}
