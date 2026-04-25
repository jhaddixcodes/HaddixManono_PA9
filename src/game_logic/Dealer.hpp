#ifndef DEALER_HPP
#define DEALER_HPP

#include "Participant.hpp"

class Dealer : public Participant {
public:

	/**
	* @brief Constructs a new dealer.
	*/
	Dealer();

	/**
	* @brief Gets move from dealer (either hit or stand). This should be called when testing in the console.
	* @return 'H' if hand is under 17, 'S' if hand is 17 or more.
	* @pre Hand must not be busted.
	*/
	char makeMoveConsole() const override;
};

#endif