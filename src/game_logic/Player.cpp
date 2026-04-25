#include <iostream>

#include "Player.hpp"

using std::cout;
using std::cin;

Player::Player() : Participant(), m_currentBet(0), m_balance(0) {}

char Player::makeMoveConsole() const 
{
	char move;
	cout << "Enter move (H/S): ";
	cin >> move;

	return move;
}

int Player::getCurrentBet() const
{
	return m_currentBet;
}

int Player::getBalance() const
{
	return m_balance;
}

void Player::setCurrentBet(int bet)
{
	m_currentBet = bet;
}

void Player::updateBalance(Outcome roundOutcome)
{
	if (roundOutcome == Outcome::Won)
	{
		// add the player's bet to their balance
		m_balance += m_currentBet;
	}
	else if (roundOutcome == Outcome::Lost)
	{
		// subtract player's bet from their balance
		m_balance -= m_currentBet;
	}

	// otherwise the player tied so do nothing
}
