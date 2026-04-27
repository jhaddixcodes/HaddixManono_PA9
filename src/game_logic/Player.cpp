#include <iostream>

#include "Player.hpp"

using std::cout;
using std::cin;

Player::Player() : Participant(), m_currentBet(0), m_balance(500) {}

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

void Player::setBalance(int balance)
{
	m_balance = balance;
}
