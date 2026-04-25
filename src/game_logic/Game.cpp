#include "Game.hpp"

Game::Game() : m_deck(Deck()), m_player(Player()), m_dealer(Dealer()), m_gameState(GameState::PLACING_BET) {}

void Game::toState(GameState state)
{
	m_gameState = state;
}

void Game::dealNewRound()
{
	// make new deck, empty player's and dealer's hands
	m_deck = Deck();
	m_player.emptyHand();
	m_dealer.emptyHand();

	// add cards to player and dealer's hands
	playerHit();
	playerHit();

	dealerHit();
	dealerHit();

	// check for blackjack, if either hand is blackjack we transition straight to round end and find out who won
	if (m_player.isHandTwentyOne() || m_dealer.isHandTwentyOne()) 
	{
		toState(GameState::ROUND_OVER);
	}
}

void Game::playerHit()
{
	m_player.hit(m_deck);
	if (m_player.isHandBusted())
	{
		toState(GameState::DEALER_TURN);
	}
}

void Game::dealerHit()
{
	m_dealer.hit(m_deck);
	if (m_dealer.isHandBusted())
	{
		toState(GameState::ROUND_OVER);
	}
}

void Game::playerStand()
{
	toState(GameState::DEALER_TURN);
}

void Game::dealerStand()
{
	toState(GameState::ROUND_OVER);
}

const GameState Game::getGameState() const
{
	return m_gameState;
}

const Hand& Game::getPlayerHand() const
{
	return m_player.getHand();
}

const Hand& Game::getDealerHand() const
{
	return m_dealer.getHand();
}

int Game::getPlayerScore() const
{
	return m_player.getHandPoints();
}

int Game::getDealerScore() const
{
	return m_dealer.getHandPoints();
}

int Game::getPlayerBalance() const
{
	return m_player.getBalance();
}

int Game::getPlayerBet() const
{
	return m_player.getCurrentBet();
}

void Game::setPlayerBet(int playerBet)
{
	m_player.setCurrentBet(playerBet);
}

string Game::getResultMessage() const
{
	if (m_gameState != GameState::ROUND_OVER)
	{
		return "";
	}

	if (m_player.isHandBusted())
	{
		return "Bust, dealer wins!";
	}

	if (m_dealer.isHandBusted())
	{
		return "Bust, player wins!";
	}

	if (m_player.getHandPoints() > m_dealer.getHandPoints())
	{
		return "Player wins!";
	}

	if (m_dealer.getHandPoints() > m_player.getHandPoints())
	{
		return "Dealer wins!";
	}

	return "Tie!";
}