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

	// hide dealer's first card so isHandTwentyOne reads the correct dealer score below
	m_dealer.setCardHidden(true);

	// if either side has blackjack on the deal, end the round immediately
	// reveal dealer's hole card so the player can see why
	if (m_player.isHandTwentyOne() || m_dealer.getHand().getCards()[0].getCardValue() + m_dealer.getHand().getCards()[1].getCardValue() == 21)
	{
		m_dealer.setCardHidden(false);
		toState(GameState::ROUND_OVER);
		return;
	}
	toState(GameState::PLAYER_TURN);
}

void Game::playerHit()
{
	m_player.hit(m_deck);
	if (m_player.isHandBusted())
	{
		m_dealer.setCardHidden(false);
		toState(GameState::ROUND_OVER);
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
	m_dealer.setCardHidden(false);
	toState(GameState::DEALER_TURN);
}

void Game::dealerStand()
{
	toState(GameState::ROUND_OVER);
}

void Game::playAgain()
{
	updatePlayerBalance();
	// clear out the old hands, we dont wanna see the old hands as we decide to play again
	m_player.emptyHand();
	m_dealer.emptyHand();
	toState(GameState::PLACING_BET);
}

const GameState Game::getGameState() const
{
	return m_gameState;
}

bool Game::dealerWillHit() const
{
	return m_dealer.willHit();
}

vector<Card>& Game::getPlayerCards()
{
	return m_player.getHand().getCards();
}

vector<Card>& Game::getDealerCards()
{
	return m_dealer.getHand().getCards();
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

void Game::setPlayerBalance(int playerBalance)
{
	m_player.setBalance(playerBalance);
}

void Game::setPlayerBet(int playerBet)
{
	m_player.setCurrentBet(playerBet);
	toState(GameState::WAITING_TO_DEAL);
}

void Game::updatePlayerBalance()
{
	if (m_gameState != GameState::ROUND_OVER)
	{
		return;
	}

	if (m_player.isHandBusted() || (m_dealer.getHandPoints() > m_player.getHandPoints() && !m_dealer.isHandBusted()))
	{
		m_player.setBalance(m_player.getBalance() - m_player.getCurrentBet());
	}
	else if (m_dealer.isHandBusted() || m_player.getHandPoints() > m_dealer.getHandPoints())
	{
		m_player.setBalance(m_player.getBalance() + m_player.getCurrentBet());
	}
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