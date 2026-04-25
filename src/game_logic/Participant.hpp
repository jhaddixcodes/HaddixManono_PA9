#ifndef PARTICIPANT_HPP
#define PARTICIPANT_HPP

#include "Deck.hpp"
#include "Hand.hpp"

class Participant {
public:

	/**
	* @brief Constructs a new participant. This should never be called explicitly except for by subclasses.
	*/
	Participant();

	virtual ~Participant() = default;

	/**
	* @return Returns a reference to the participant's hand
	*/
	const Hand& getHand() const;

	/**
	* @brief Returns the number of points in the participant's hand
	*/
	int getHandPoints() const;

	// TODO: makeMove()

	/**
	* @brief Gets move from participant (either hit or stand). This should be called when testing in the console.
	* @return 'H' if hit, 'S' if stand.
	* @pre Hand must not be busted.
	*/
	virtual char makeMoveConsole() const = 0;

	/**
	* @brief Hits the deck and adds the card to the participant's hand.
	* @pre Hand must not be busted, and deck must not be empty.
	*/
	void hit(Deck& deck);

	/**
	* @brief Empties the participant's hand.
	*/
	void emptyHand();

	/**
	* @return true if participant's hand is busted, false otherwise.
	*/
	bool isHandBusted() const;

	/**
	* @return true if participant's hand is 21, false otherwise.
	*/
	bool isHandTwentyOne() const;

private:
	Hand m_hand;
};

#endif