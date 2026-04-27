/*
	Author: James Haddix
	Written: Apr 24 2026
	Last Updated: Apr 26 2026
	Description: Player class that inherits from Participant.
*/

#ifndef PLAYER_HPP
#define PLAYER_HPP

#include "Participant.hpp"

class Player : public Participant {
public:

	/**
	* @brief Constructs a new player.
	*/
	Player();

	/**
	* @brief Gets current bet from player.
	* @return Player's current bet.
	*/
	int getCurrentBet() const;

	/**
	* @brief Gets player's balance.
	* @return Player's current balance.
	*/
	int getBalance() const;

	/**
	* @brief Set the player's bet.
	* @param bet The new bet amount.
	*/
	void setCurrentBet(int bet);

	/**
	* @brief Add or subtract bet from player's balance based on if they won or lost.
	* @param roundOutcome The outcome of the current round.
	*/
	void setBalance(int balance);

private:
	int m_currentBet;
	int m_balance;
};

#endif