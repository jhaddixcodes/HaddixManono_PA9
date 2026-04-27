#include "drawHand.hpp"

// this function mostly originally written by Lyon
void drawCard(sf::RenderWindow& window, const Card& card, sf::Font* pFont, float x, float y)
{
	// the card body
	sf::RectangleShape cardShape(sf::Vector2f(70.f, 100.f));

	// center origin so (x, y) refers to the center of the card. this is reused
	sf::Vector2f origin = cardShape.getLocalBounds().getCenter();
	cardShape.setOrigin(origin);

	cardShape.setPosition(sf::Vector2f(x, y));
	cardShape.setOutlineThickness(2.f);
	cardShape.setOutlineColor(sf::Color::Black);

	// face down - just draw the back
	if (card.getHidden())
	{
		cardShape.setFillColor(sf::Color(30, 60, 150));
		window.draw(cardShape);

		// little inner rectangle so the back looks decorated
		sf::RectangleShape pattern(sf::Vector2f(54.f, 84.f));
		pattern.setOrigin(origin);
		pattern.setPosition(sf::Vector2f(x + 8.f, y + 8.f));
		pattern.setFillColor(sf::Color(60, 90, 180));
		pattern.setOutlineThickness(1.f);
		pattern.setOutlineColor(sf::Color(100, 130, 220));
		window.draw(pattern);
		return;
	}

	// face up - white background
	cardShape.setFillColor(sf::Color::White);
	window.draw(cardShape);

	// if there's no font loaded, just leave it as a blank white card
	if (pFont == nullptr)
	{
		return;
	}

	// rank in the top-left corner
	sf::Text rankText(*pFont);
	rankText.setString(card.getSymbol());
	rankText.setCharacterSize(20);
	if (card.getSuit() == Suit::DIAMOND || card.getSuit() == Suit::HEART)
	{
		rankText.setFillColor(sf::Color::Red);
	}
	else
	{
		rankText.setFillColor(sf::Color::Black);
	}

	rankText.setOrigin(origin);
	rankText.setPosition(sf::Vector2f(x + 6.f, y + 4.f));
	window.draw(rankText);

	// big suit letter in the middle
	sf::Text suitText(*pFont);
	suitText.setString(card.getSuitString());
	suitText.setCharacterSize(36);
	if (card.getSuit() == Suit::DIAMOND || card.getSuit() == Suit::HEART)
	{
		suitText.setFillColor(sf::Color::Red);
	}
	else
	{
		suitText.setFillColor(sf::Color::Black);
	}

	suitText.setOrigin(origin);
	suitText.setPosition(sf::Vector2f(x + 22.f, y + 35.f));
	window.draw(suitText);

	// rank again in the bottom-right
	sf::Text rankText2(*pFont);
	rankText2.setString(card.getSymbol());
	rankText2.setCharacterSize(20);
	if (card.getSuit() == Suit::DIAMOND || card.getSuit() == Suit::HEART)
	{
		rankText2.setFillColor(sf::Color::Red);
	}
	else
	{
		rankText2.setFillColor(sf::Color::Black);
	}
	rankText2.setOrigin(origin);
	rankText2.setPosition(sf::Vector2f(x + 52.f, y + 76.f));
	window.draw(rankText2);
}

// written by James
void drawHand(sf::RenderWindow& window, const vector<Card>& cards, sf::Font* pFont, float x, float y)
{
	// yeah maybe this should be a constant somewhere else, but hey, technically not a magic number
	float spacing = 10.f;
	float cardWidth = 70.f;
	int size = cards.size();

	// updates for every card across the space the hand is drawn on (bad comment, my bad)
	// this was a bitch to figure out
	float xi = x - (size / 2.0 - 0.5) * (spacing + cardWidth);

	for (const Card& card : cards)
	{
		drawCard(window, card, pFont, xi, y);
		// really it's half a card plus a space plus half a card but like why the hell would i write that that's gross as hell
		xi += cardWidth + spacing;
	}
}