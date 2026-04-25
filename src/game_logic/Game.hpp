#ifndef GAME_HPP
#define GAME_HPP

#include "Deck.hpp"
#include "Player.hpp"
#include "Dealer.hpp"

enum class GameState
{
	PLACING_BET, PLAYER_TURN, DEALER_TURN, ROUND_OVER
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
	* @details Makes a new deck, clears hands, deals cards, transitions to end if blackjack occurs
	*/
	void dealNewRound();

	/**
	* @brief Gives one card from the deck to the player. If player busts, transitions to dealer's turn.
	*/
	void playerHit();

	/**
	* @brief Gives one card from the deck to the dealer. If dealer busts, transitions to round end.
	*/
	void dealerHit();

	/**
	* @brief Ends player's turn early and transitions to the dealer's turn.
	*/
	void playerStand();

	/**
	* @brief Ends dealer's turn early and transitions to round end.
	*/
	void dealerStand();

	/**
	* @return The current game state
	*/
	const GameState getGameState() const;

	/**
	* @return Const reference to player's hand
	*/
	const Hand& getPlayerHand() const;

	/**
	* @return Const reference to dealer's hand
	*/
	const Hand& getDealerHand() const;

	/**
	* @return Returns the player's current score
	*/
	int getPlayerScore() const;

	/**
	* @return Returns the dealer's current score
	*/
	int getDealerScore() const;

	/**
	* @return int that's the player's balance
	*/
	int getPlayerBalance() const;
	
	/**
	* @return int that's the player's bet
	*/
	int getPlayerBet() const;

	/**
	* @brief Change the player's bet amount.
	* @param bet The new bet amount.
	*/
	void setPlayerBet(int playerBet);

	/**
	* @return Returns human-readable string representing result of game.
	* @details If the game is not over, returns an empty string.
	*/
	string getResultMessage() const;
	
private:
	GameState m_gameState;
	Deck m_deck;
	Dealer m_dealer;
	Player m_player;

	/**
	* @brief Transitions to specified state
	*/
	void toState(GameState state);
};

#endif