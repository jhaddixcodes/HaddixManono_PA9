#ifndef PARTICIPANT_HPP
#define PARTICIPANT_HPP

#include "Deck.hpp"

class Participant {
public:

	/**
	* @brief Constructs a new participant. This should never be called explicitly.
	*/
	Participant();
	virtual ~Participant() = default;

	/**
	* @brief Gets move from participant (either hit or stand). This should be called when testing in the console.
	* @return 'H' if hit, 'S' if stand.
	* @pre Hand must not be busted.
	*/
	virtual char getMove() const = 0;

	/**
	* @brief Check if participant's hand is busted.
	* @return true if participant's hand is busted, false otherwise.
	*/
	bool isHandBusted();

private:
	Hand m_hand;
};

#endif