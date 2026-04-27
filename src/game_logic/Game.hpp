/*
	Author: James Haddix
	Written: Apr 24 2026
	Last Updated: Apr 26 2026
	Description: Game class containing everything needed to run a blackjack game. Basically a state machine, though very likely a bad one.
*/

#ifndef GAME_HPP
#define GAME_HPP

#include "Deck.hpp"
#include "Player.hpp"
#include "Dealer.hpp"

enum class GameState
{
	PLACING_BET, WAITING_TO_DEAL, PLAYER_TURN, DEALER_TURN, ROUND_OVER
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
	* @brief Goes back to the beginning of the game (placing bet)
	*/
	void playAgain();

	/**
	* @return The current game state
	*/
	const GameState getGameState() const;

	/**
	* @return Whether the dealer will hit or stand on their move
	*/
	bool dealerWillHit() const;

	/**
	* @return Const reference to player's hand
	*/
	vector<Card>& getPlayerCards();

	/**
	* @return Const reference to dealer's hand
	*/
	vector<Card>& getDealerCards();

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
	* @brief Change the player's balance.
	* @param balance The new balance.
	*/
	void setPlayerBalance(int playerBalance);

	/**
	* @brief Change the player's bet amount and move to the player's turn.
	* @param bet The new bet amount.
	*/
	void setPlayerBet(int playerBet);

	/**
	* @brief Updates the player's balance based on the game's result.
	*/
	void updatePlayerBalance();

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