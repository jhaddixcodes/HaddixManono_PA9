/*
	Authors: Lyon Manono, James Haddix
	Created: Apr 23 2026
	Last Updated: Apr 27 2026
	Description: Blackjack game using SFML.
*/

#include <SFML/Graphics.hpp>
#include "graphics/Button.hpp"
#include "graphics/InputField.hpp"
#include "graphics/drawHand.hpp"
#include "game_logic/Game.hpp"
#include "tests/GameTests.hpp"

int main()
{
	// run tests from GameTests
	testAll();

	// the game interface
	Game game;

	// make the window
	sf::RenderWindow window(sf::VideoMode({ 900, 650 }), "Blackjack");
	window.setFramerateLimit(60);

	// try to load a font, if it fails cards/buttons still draw but without text
	sf::Font font;
	bool fontLoaded = font.openFromFile("assets/font.ttf");

	// text entry for entering a bet
	InputField betField(350.f, 300.f, 200.f, 50.f);
	if (fontLoaded) betField.setFont(&font);

	/* 
	UI element coordinates (button positions, label positions, card row y-values)
 	were refined with Claude to avoid overlap between cards, buttons, and text
 	labels at different game states.
 	Prompt: "Player cards draw centered at y=500 with height 100, where should
 	I put the Play Again and Quit buttons so they don't overlap the cards?"
	"Generate the most user friendly coordinate positions for the buttons and 
	labels"
	*/
	
	// buttons for the different game states
	Button hitButton("Hit", 720.f, 450.f, 130.f, 50.f);
	if (fontLoaded) hitButton.setFont(&font);

	Button standButton("Stand", 720.f, 520.f, 130.f, 50.f);
	if (fontLoaded) standButton.setFont(&font);

	Button dealButton("Deal", 50.f, 520.f, 130.f, 50.f);
	if (fontLoaded) dealButton.setFont(&font);

	// Lyon - tweaked the play again and quit game buttons due to overlap with player hand
	Button playAgainButton("Play Again", 350.f, 240.f, 200.f, 50.f);
	if (fontLoaded) playAgainButton.setFont(&font);

	Button quitGameButton("Quit Game", 350.f, 305.f, 200.f, 50.f);
	if (fontLoaded) quitGameButton.setFont(&font);

	// button shown only when the player runs out of money - James Request
	Button endGameButton("End Game", 350.f, 350.f, 200.f, 50.f);
	if (fontLoaded) endGameButton.setFont(&font);

	// text labels
	sf::Text dealerPointsLabel(font);
	sf::Text playerPointsLabel(font);
	sf::Text statusMessage(font);
	sf::Text playerBalanceLabel(font);
	sf::Text playerBetLabel(font);
	sf::Text betPromptLabel(font);
	sf::Text betHintLabel(font);
	sf::Text titleLabel(font);
	sf::Text brokeLabel(font); 
	

	// only set up text if the font loaded
	if (fontLoaded)
	{
		dealerPointsLabel.setString("Dealer: ");
		dealerPointsLabel.setCharacterSize(24);
		dealerPointsLabel.setFillColor(sf::Color::White);
		dealerPointsLabel.setPosition(sf::Vector2f(50.f, 80.f));

		playerPointsLabel.setString("Player: ");
		playerPointsLabel.setCharacterSize(24);
		playerPointsLabel.setFillColor(sf::Color::White);
		playerPointsLabel.setPosition(sf::Vector2f(50.f, 400.f));

		playerBalanceLabel.setCharacterSize(20);
		playerBalanceLabel.setFillColor(sf::Color::White);
		playerBalanceLabel.setPosition(sf::Vector2f(50.f, 450.f));

		playerBetLabel.setCharacterSize(20);
		playerBetLabel.setFillColor(sf::Color::White);
		playerBetLabel.setPosition(sf::Vector2f(50.f, 480.f));

		statusMessage.setCharacterSize(28);
		statusMessage.setFillColor(sf::Color::Yellow);

		// label above the input field telling user what to do
		betPromptLabel.setString("Place Your Bet");
		betPromptLabel.setCharacterSize(28);
		betPromptLabel.setFillColor(sf::Color::White);
		betPromptLabel.setPosition(sf::Vector2f(360.f, 250.f));

		// hint below input field
		betHintLabel.setString("Press Enter to confirm");
		betHintLabel.setCharacterSize(16);
		betHintLabel.setFillColor(sf::Color(200, 200, 200));
		betHintLabel.setPosition(sf::Vector2f(370.f, 360.f));

		// big title at the top
		titleLabel.setString("BLACKJACK");
		titleLabel.setCharacterSize(36);
		titleLabel.setFillColor(sf::Color::White);
		titleLabel.setPosition(sf::Vector2f(370.f, 10.f));

		// broke screen message
		brokeLabel.setString("You're out of money!");
		brokeLabel.setCharacterSize(36);
		brokeLabel.setFillColor(sf::Color::Yellow);
		brokeLabel.setPosition(sf::Vector2f(280.f, 250.f));
	}

	// clock used to slow down the dealer's auto hits so they don't all happen in one frame
	// dealer pacing using sf::Clock generated with Claude.
 	// Prompt: "How can I add a delay between dealer auto-hits in an SFML game loop without blocking the main thread"
	
	sf::Clock dealerClock;
	float dealerDelay = 0.8f; // seconds between dealer actions

	// flag for when the player has gone broke. when true we show the broke screen
	bool playerBroke = false;

	// main game loop 
	while (window.isOpen())
	{
		while (const std::optional event = window.pollEvent())
		{
			if (event->is<sf::Event::Closed>())
			{
				window.close();
			}

			// handle mouse clicks
			if (const auto* mousePressed = event->getIf<sf::Event::MouseButtonPressed>())
			{
				if (mousePressed->button == sf::Mouse::Button::Left)
				{
					int mx = mousePressed->position.x;
					int my = mousePressed->position.y;

					// if player is broke, only the end game button works
					if (playerBroke)
					{
						if (endGameButton.isClicked(mx, my))
						{
							window.close();
						}
						continue;
					}

					// only let user click into the bet field while placing bet
					if (game.getGameState() == GameState::PLACING_BET)
					{
						betField.setFocused(betField.isClicked(mx, my));
					}
					else
					{
						betField.setFocused(false);
					}

					if (game.getGameState() == GameState::WAITING_TO_DEAL)
					{
						if (dealButton.isClicked(mx, my))
						{
							game.dealNewRound();
						}
					}

					if (game.getGameState() == GameState::PLAYER_TURN)
					{
						if (hitButton.isClicked(mx, my))
						{
							game.playerHit();
							// if player just busted, the round is already over so no dealer clock needed
						}
						if (standButton.isClicked(mx, my))
						{
							game.playerStand();
							dealerClock.restart();
						}
					}

					if (game.getGameState() == GameState::ROUND_OVER)
					{
						if (playAgainButton.isClicked(mx, my))
						{
							game.playAgain();
							// after the balance updates, check if the player is broke
							if (game.getPlayerBalance() <= 0)
							{
								playerBroke = true;
							}
						}
						if (quitGameButton.isClicked(mx, my))
						{
							window.close();
						}
					}
				}
			}

			// handle text input for the bet field
			else if (const sf::Event::TextEntered* text = event->getIf<sf::Event::TextEntered>())
			{
				if (game.getGameState() == GameState::PLACING_BET && !playerBroke)
				{
					// 13 is the unicode for Enter
					if (text->unicode == 13 && !betField.empty())
					{
						int bet = std::stoi(betField.getText());
						// only accept bet if it's positive and within balance
						if (bet > 0 && bet <= game.getPlayerBalance())
						{
							game.setPlayerBet(bet);
							betField.clear();
						}
					}

					else
					{
						betField.handleInput(*text);
					}
				}
			}
		}

		// dealer takes one action per dealerDelay seconds
		if (game.getGameState() == GameState::DEALER_TURN)
		{
			if (dealerClock.getElapsedTime().asSeconds() >= dealerDelay)
			{
				if (game.dealerWillHit())
				{
					game.dealerHit();
				}
				else
				{
					game.dealerStand();
				}
				dealerClock.restart();
			}
		}

		// update text strings every frame so they stay in sync with the game
		if (fontLoaded)
		{
			dealerPointsLabel.setString("Dealer: " + std::to_string(game.getDealerScore()));
			playerPointsLabel.setString("Player: " + std::to_string(game.getPlayerScore()));
			playerBalanceLabel.setString("Balance: $" + std::to_string(game.getPlayerBalance()));
			playerBetLabel.setString("Bet: $" + std::to_string(game.getPlayerBet()));

			// status message changes based on what state we're in
			if (game.getGameState() == GameState::PLACING_BET)
			{
				statusMessage.setString("");
			}
			else if (game.getGameState() == GameState::WAITING_TO_DEAL)
			{
				statusMessage.setString("Click Deal to start the round");
			}
			else if (game.getGameState() == GameState::PLAYER_TURN)
			{
				statusMessage.setString("Hit or Stand?");
			}
			else if (game.getGameState() == GameState::DEALER_TURN)
			{
				statusMessage.setString("Dealer's turn...");
			}
			else if (game.getGameState() == GameState::ROUND_OVER)
			{
				statusMessage.setString(game.getResultMessage());
			}

			// recenter status message every frame since text length changes
			sf::FloatRect textBounds = statusMessage.getLocalBounds();
			statusMessage.setOrigin(textBounds.getCenter());
			statusMessage.setPosition(sf::Vector2f(450.f, 200.f));
		}

		// draw everything
		window.clear(sf::Color(0, 100, 0));  // green felt table

		// if player is broke, only show the broke screen and nothing else
		if (playerBroke)
		{
			if (fontLoaded)
			{
				window.draw(titleLabel);
				window.draw(brokeLabel);
			}
			endGameButton.draw(window);
			window.display();
			continue;
		}

		if (fontLoaded)
		{
			window.draw(titleLabel);
			window.draw(statusMessage);

			// only show points labels when there are actually cards on the table
			if (game.getGameState() != GameState::PLACING_BET)
			{
				window.draw(dealerPointsLabel);
				window.draw(playerPointsLabel);
				window.draw(playerBalanceLabel);
				window.draw(playerBetLabel);
			}
		}

		// draw cards in player's and dealer's hands
		if (!game.getPlayerCards().empty())
		{
			drawHand(window, game.getPlayerCards(), &font, 450.f, 500.f);
		}
		if (!game.getDealerCards().empty())
		{
			drawHand(window, game.getDealerCards(), &font, 450.f, 130.f);
		}

		// draw state-specific UI
		if (game.getGameState() == GameState::PLACING_BET)
		{
			if (fontLoaded)
			{
				window.draw(betPromptLabel);
				window.draw(betHintLabel);
				// show balance during betting too so player knows what they have to bet
				window.draw(playerBalanceLabel);
			}
			betField.draw(window);
		}
		else if (game.getGameState() == GameState::WAITING_TO_DEAL)
		{
			dealButton.draw(window);
		}
		else if (game.getGameState() == GameState::PLAYER_TURN)
		{
			hitButton.draw(window);
			standButton.draw(window);
		}
		else if (game.getGameState() == GameState::ROUND_OVER)
		{
			playAgainButton.draw(window);
			quitGameButton.draw(window);
		}

		window.display();
	}

	return 0;
}
