/*
	Team: Lyon Manono and James Haddix
	Date: Apr 24 2026
	Description: Blackjack game using SFML. This file sets up the graphics
				 scaffold - cards, buttons, table. Logic (deck, scoring,
				 dealer AI) will be added later.
*/

#include <SFML/Graphics.hpp>
#include "Card.h"
#include "Button.h"

int main()
{
	// make the window
	sf::RenderWindow window(sf::VideoMode({ 900, 650 }), "Blackjack");
	window.setFramerateLimit(60);

	// try to load a font, if it fails cards/buttons still draw but without text
	sf::Font font;
	bool fontLoaded = font.openFromFile("assets/font.ttf");

	// placeholder cards so there's something to look at
	// (the logic side will replace these with real hands)
	Card dealerCard1(13, 3, 350.f, 80.f);   // King of Spades
	dealerCard1.setFaceUp(true);
	if (fontLoaded) dealerCard1.setFont(&font);

	Card dealerCard2(0, 0, 430.f, 80.f);    // hidden hole card
	if (fontLoaded) dealerCard2.setFont(&font);

	Card playerCard1(1, 0, 350.f, 400.f);   // Ace of Hearts
	playerCard1.setFaceUp(true);
	if (fontLoaded) playerCard1.setFont(&font);

	Card playerCard2(10, 2, 430.f, 400.f);  // 10 of Clubs
	playerCard2.setFaceUp(true);
	if (fontLoaded) playerCard2.setFont(&font);

	// --- buttons ---
	Button hitButton("Hit", 720.f, 450.f, 130.f, 50.f);
	if (fontLoaded) hitButton.setFont(&font);


	Button standButton("Stand", 720.f, 520.f, 130.f, 50.f);
	if (fontLoaded) standButton.setFont(&font);

	Button dealButton("Deal", 50.f, 520.f, 130.f, 50.f);
	if (fontLoaded) dealButton.setFont(&font);

	// --- text labels for the table ---
	sf::Text dealerLabel(font);
	sf::Text playerLabel(font);
	sf::Text statusMessage(font);
	if (fontLoaded)
	{
		dealerLabel.setString("Dealer");
		dealerLabel.setCharacterSize(24);
		dealerLabel.setFillColor(sf::Color::White);
		dealerLabel.setPosition(sf::Vector2f(50.f, 80.f));

		playerLabel.setString("Player");
		playerLabel.setCharacterSize(24);
		playerLabel.setFillColor(sf::Color::White);
		playerLabel.setPosition(sf::Vector2f(50.f, 400.f));

		statusMessage.setString("Click Deal to start!");
		statusMessage.setCharacterSize(28);
		statusMessage.setFillColor(sf::Color::Yellow);
		statusMessage.setPosition(sf::Vector2f(320.f, 280.f));
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

					// These are placeholders. James will replace the bodies
					// with actual game logic.
					if (hitButton.isClicked(mx, my))
					{
						// TODO (logic): deal another card to player
					}
					if (standButton.isClicked(mx, my))
					{
						// TODO (logic): reveal dealer hole card, dealer plays
						dealerCard2.setFaceUp(true);  // quick demo behavior
					}
					if (dealButton.isClicked(mx, my))
					{
						// TODO (logic): reset and start a new round
						dealerCard2.setFaceUp(false); // quick demo behavior
					}
				}
			}
		}

		// drawing
		window.clear(sf::Color(0, 100, 0));  // green felt table

		if (fontLoaded)
		{
			window.draw(dealerLabel);
			window.draw(playerLabel);
			window.draw(statusMessage);
		}

		dealerCard1.draw(window);
		dealerCard2.draw(window);
		playerCard1.draw(window);
		playerCard2.draw(window);

		hitButton.draw(window);
		standButton.draw(window);
		dealButton.draw(window);

		window.display();
	}

	return 0;
}