#include "Participant.hpp"

Participant::Participant() : m_hand(Hand()) {}

const Hand& Participant::getHand() const
{
	return m_hand;
}

int Participant::getHandPoints() const
{
	return m_hand.calculatePoints();
}

void Participant::hit(Deck& deck) {
	const Card card = deck.getCard();
	m_hand.addCard(card);
}

void Participant::emptyHand() {
	m_hand.empty();
}

bool Participant::isHandBusted() const {
	return m_hand.isBust();
}

bool Participant::isHandTwentyOne() const {
	return m_hand.isTwentyOne();
}