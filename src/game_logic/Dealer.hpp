/*
	Author: James Haddix
	Written: Apr 24 2026
	Last Updated: Apr 25 2026
	Description: Dealer class that inherits from Participant. Controlled with logic instead of a user.
*/

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
	* @brief Sets the first card in the dealer's hand to be hidden or shown.
	*/
	void setCardHidden(bool hidden);

	/**
	* @brief Gets whether the dealer hits or stands on their current hand
	* @return true if hand is under 17, stand if hand is 17 or more.
	* @pre Hand must not be busted.
	*/
	bool willHit() const;
};

#endif