#ifndef PLAYER_HPP
#define PLAYER_HPP

#include "Participant.hpp"

enum class Outcome
{
	Won, Lost, Tie
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
	char getMove() const override;

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
	* @brief Add or subtract bet from player's balance based on if they won or lost.
	* @param roundOutcome The outcome of the current round.
	*/
	void updateBalance(Outcome roundOutcome);

private:
	int m_currentBet;
	int m_balance;
};

#endif