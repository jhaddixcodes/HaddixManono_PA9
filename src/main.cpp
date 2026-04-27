/*
	Authors: Lyon Manono, James Haddix
	Created: Apr 23 2026
	Last Updated: Apr 26 2026
	Description: Blackjack game using SFML.
*/

#include <SFML/Graphics.hpp>
#include "graphics/Button.hpp"
#include "graphics/InputField.hpp"
#include "graphics/drawHand.hpp"
#include "game_logic/Game.hpp"

int main()
{

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

	// --- buttons ---
	Button hitButton("Hit", 720.f, 450.f, 130.f, 50.f);
	if (fontLoaded) hitButton.setFont(&font);

	Button standButton("Stand", 720.f, 520.f, 130.f, 50.f);
	if (fontLoaded) standButton.setFont(&font);

	Button dealButton("Deal", 50.f, 520.f, 130.f, 50.f);
	if (fontLoaded) dealButton.setFont(&font);

	Button playAgainButton("Play Again", 350.f, 350.f, 200.f, 50.f);
	if (fontLoaded) playAgainButton.setFont(&font);

	Button quitGameButton("Quit Game", 350.f, 425.f, 200.f, 50.f);
	if (fontLoaded) quitGameButton.setFont(&font);

	// --- text labels for the table ---
	sf::Text dealerPointsLabel(font);
	sf::Text playerPointsLabel(font);
	sf::Text statusMessage(font);
	sf::Text playerBalanceLabel(font);
	sf::Text playerBetLabel(font);

	// only render text if the font is loaded
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

		playerBalanceLabel.setString("test");
		playerBalanceLabel.setCharacterSize(24);
		playerBalanceLabel.setFillColor(sf::Color::White);
		playerBalanceLabel.setPosition(sf::Vector2f(50.f, 450.f));

		playerBetLabel.setString("test");
		playerBetLabel.setCharacterSize(24);
		playerBetLabel.setFillColor(sf::Color::White);
		playerBetLabel.setPosition(sf::Vector2f(50.f, 500.f));

		statusMessage.setString("");
		statusMessage.setCharacterSize(28);
		statusMessage.setFillColor(sf::Color::Yellow);

		// to center statusMessage on screen, we can get the rectangle that bounds it and set its origin based on the center of that rectangle
		// taken from https://stackoverflow.com/questions/14505571/centering-text-on-the-screen-with-sfml
		sf::FloatRect textBounds = statusMessage.getLocalBounds();
		statusMessage.setOrigin(textBounds.getCenter());
		statusMessage.setPosition(sf::Vector2f(450.f, 325.f));
	}

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

					// handle whether betfield is focused
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

					// These are placeholders. James will replace the bodies
					// with actual game logic.
					if (game.getGameState() == GameState::PLAYER_TURN)
					{
						if (hitButton.isClicked(mx, my))
						{
							game.playerHit();
						}
						if (standButton.isClicked(mx, my))
						{
							game.playerStand();
						}
					}

					if (game.getGameState() == GameState::ROUND_OVER)
					{
						if (playAgainButton.isClicked(mx, my))
						{
							game.playAgain();
						}
						if (quitGameButton.isClicked(mx, my))
						{
							window.close();
						}
					}
				}
			}
			
			// handle text input...
			else if (const sf::Event::TextEntered* text = event->getIf<sf::Event::TextEntered>())
			{
				// ...if we expect it
				if (game.getGameState() == GameState::PLACING_BET)
				{
					// 13 is the unicode for Enter
					if (text->unicode == 13 && !betField.empty())
					{
						int bet = std::stoi(betField.getText());
						if (bet <= game.getPlayerBalance())
						{
							// update player's bet, move to next state
							game.setPlayerBet(bet);
							game.dealNewRound();
						}
					}

					else
					{
						betField.handleInput(*text);
					}
				}
			}
		}

		// handle dealer turn
		if (game.getGameState() == GameState::DEALER_TURN)
		{
			if (game.dealerWillHit())
			{
				game.dealerHit();
			}
			else
			{
				game.dealerStand();
			}
		}

		if (fontLoaded)
		{
			// update dealer and player scores
			dealerPointsLabel.setString("Dealer: " + std::to_string(game.getDealerScore()));
			playerPointsLabel.setString("Player: " + std::to_string(game.getPlayerScore()));

			// change status message. if game state isn't roundover this'll be blank
			statusMessage.setString(game.getResultMessage());
			sf::FloatRect textBounds = statusMessage.getLocalBounds();
			statusMessage.setOrigin(textBounds.getCenter());
			statusMessage.setPosition(sf::Vector2f(450.f, 325.f));

			// change player balance and bet message.
			playerBalanceLabel.setString("Balance: " + std::to_string(game.getPlayerBalance()));
			playerBetLabel.setString("Bet: " + std::to_string(game.getPlayerBet()));
		}
		// drawing
		window.clear(sf::Color(0, 100, 0));  // green felt table

		if (fontLoaded)
		{
			window.draw(dealerPointsLabel);
			window.draw(playerPointsLabel);
			window.draw(playerBalanceLabel);
			window.draw(playerBetLabel);
			window.draw(statusMessage);
		}

		// draw cards in player's and dealer's hand
		if (!game.getPlayerCards().empty())
		{
			drawHand(window, game.getPlayerCards(), &font, 450.f, 550.f);
		}
		if (!game.getDealerCards().empty())
		{
			drawHand(window, game.getDealerCards(), &font, 450.f, 100.f);
		}

		

		if (game.getGameState() == GameState::PLACING_BET)
		{
			betField.draw(window);
		}
		
		else if (game.getGameState() == GameState::WAITING_TO_DEAL)
		{
			dealButton.draw(window);
		}

		else if (game.getGameState() == GameState::PLAYER_TURN || game.getGameState() == GameState::DEALER_TURN)
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