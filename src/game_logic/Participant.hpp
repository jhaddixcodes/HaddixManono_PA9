#ifndef PARTICIPANT_HPP
#define PARTICIPANT_HPP

#include <string>
#include "Deck.hpp"

using std::string;

class Participant {
public:

	/**
	* @brief Constructs a new participant. This should never be called explicitly.
	*/
	Participant();

	/**
	* @brief Gets move from participant (either hit or stand). This should be called when testing in the console.
	* @return 'H' if hit, 'S' if stand.
	* @pre Hand must not be busted.
	*/
	virtual char getMove() = 0;

	/**
	* @brief Check if participant's hand is busted.
	* @return true if participant's hand is busted, false otherwise.
	*/
	bool isHandBusted();

private:
	Hand m_hand;
};

class Player : public Participant {
public:

	/**
	* @brief Constructs a new player.
	*/
	Player();

	/**
	* @brief Gets move from player (either hit or stand). This should be called when testing in the console.
	* @return 'H' if hit, 'S' if stand.
	* @pre Hand must not be busted.
	*/
	char getMove() override;

	/**
	* @brief Gets current bet from player.
	* @return Player's current bet.
	*/
	int getCurrentBet();

	/**
	* @brief Gets player's balance.
	* @return Player's current balance.
	*/
	int getBalance();

	/**
	* @brief Add or subtract bet from player's balance based on if they won or lost.
	* @param playerWon If the player won or not.
	*/
	void updateBalance(bool playerWon);

private:
	int m_currentBet;
	int m_balance;
};

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
	char getMove() override;
};

#endif