#include "Dealer.hpp"

Dealer::Dealer() : Participant() {}

void Dealer::setCardHidden(bool hidden)
{
	getHand().getCards().front().setHidden(hidden);
}

bool Dealer::willHit() const
{
	return getHandPoints() < 17;
}