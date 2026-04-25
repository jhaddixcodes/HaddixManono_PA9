#include "Dealer.hpp"

Dealer::Dealer() : Participant() {}

char Dealer::makeMoveConsole() const
{
	// in most casinos, the dealer hits until 17
	if (getHandPoints() < 17) {
		return 'H';
	}
	else {
		return 'S';
	}
}