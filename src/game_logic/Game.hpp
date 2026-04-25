#ifndef GAME_HPP
#define GAME_HPP

#include "Deck.hpp"
#include "Player.hpp"
#include "Dealer.hpp"

enum class GameState {
	PLACING_BET, PLAYER_TURN, DEALER_TURN, GAME_OVER
};

class Game 
{
public:

	/**
	* @brief Constructs a new Game object with Deck, one Player, and one Dealer
	*/
	Game();

	/**
	* @brief Deals cards to players and dealer. 
	*/
	void dealNewRound();

	/**
	* @brief Gives one card from the deck to the player.
	* @pre Player must not have busted.
	*/
	void playerHit();

	/**
	* @brief Gives one card from the deck to the player.
	* @pre Player must not have busted.
	*/
	void dealerHit();

	/**
	* @brief Get the current game state
	* @return The current game state
	*/
	const GameState& getGameState();

	/**
	* @brief Get the player's current hand
	* @return Const reference to player's hand
	*/
	const Hand& getPlayerHand();

	/**
	* @brief Get the dealer's current hand
	* @return Const reference to dealer's hand
	*/
	const Hand& getDealerHand();

	/**
	* @brief Get the player's current balance
	* @return int that's the player's balance
	*/
	int getPlayerBalance() const;
	
	/**
	* @brief Get the player's current bet
	* @return int that's the player's bet
	*/
	int getPlayerBet() const;

	/**
	* @brief Transitions to next state
	*/
	void nextState();

	/**
	* @brief Change the player's bet amount.
	* @param bet The new bet amount.
	*/
	void placeBet(int bet);
	
private:
	Deck m_deck;
	Dealer m_dealer;
	Player m_player;
};

#endif