#include <cassert>
#include <iostream>

#include "GameTests.hpp"
#include "../game_logic/Game.hpp"

// these test cases written by Claude with prompt "Please write test cases for this class with just pure C++ only using public methods"

// Test 1: Initial game state is PLACING_BET
void testInitialState()
{
    Game game;
    assert(game.getGameState() == GameState::PLACING_BET);
    std::cout << "PASS: test_initialState\n";
}

// Test 2: Setting a bet transitions state to WAITING_TO_DEAL
void testSetPlayerBetTransitionsState()
{
    Game game;
    game.setPlayerBalance(500);
    game.setPlayerBet(50);
    assert(game.getGameState() == GameState::WAITING_TO_DEAL);
    assert(game.getPlayerBet() == 50);
    std::cout << "PASS: test_setPlayerBetTransitionsState\n";
}

// Test 3: playerStand transitions state to DEALER_TURN
void testPlayerStandTransitionsState()
{
    Game game;
    game.setPlayerBalance(500);
    game.setPlayerBet(50);
    game.dealNewRound();

    // Only run this part if the round didn't immediately end due to blackjack
    if (game.getGameState() == GameState::PLAYER_TURN)
    {
        game.playerStand();
        assert(game.getGameState() == GameState::DEALER_TURN);
        std::cout << "PASS: test_playerStandTransitionsState\n";
    }
    else
    {
        std::cout << "SKIP: test_playerStandTransitionsState (blackjack on deal)\n";
    }
}

// Test 4: playAgain resets state to PLACING_BET and clears hands
void testPlayAgainResetsState()
{
    Game game;
    game.setPlayerBalance(500);
    game.setPlayerBet(50);
    game.dealNewRound();

    // Bring the round to ROUND_OVER via playerStand + dealerStand if possible
    if (game.getGameState() == GameState::PLAYER_TURN)
    {
        game.playerStand();
        game.dealerStand();
    }

    assert(game.getGameState() == GameState::ROUND_OVER);
    game.playAgain();
    assert(game.getGameState() == GameState::PLACING_BET);
    assert(game.getPlayerCards().size() == 0);
    assert(game.getDealerCards().size() == 0);
    std::cout << "PASS: test_playAgainResetsState\n";
}

// Test 5: dealNewRound gives both player and dealer exactly 2 cards
void testDealNewRoundCardCount()
{
    Game game;
    game.setPlayerBalance(500);
    game.setPlayerBet(50);
    game.dealNewRound();

    assert(game.getPlayerCards().size() == 2);
    assert(game.getDealerCards().size() == 2);
    std::cout << "PASS: test_dealNewRoundCardCount\n";
}

void testAll()
{
    testInitialState();
    testSetPlayerBetTransitionsState();
    testPlayerStandTransitionsState();
    testPlayAgainResetsState();
    testDealNewRoundCardCount();

    std::cout << "\nAll tests passed!\n";
}