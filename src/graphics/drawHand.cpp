#include "drawHand.hpp"
//helper to get unicode suit symbol for a card
sf::String getSuitSymbol(Suit suit)
{
	if (suit == Suit::HEART) return L"\u2665";
	if (suit == Suit::DIAMOND) return L"\u2666";
	if (suit == Suit::CLUB) return L"\u2663";
	if (suit == Suit::SPADE) return L"\u2660";
	return L"?";
}
// draws a single card centered at (x, y)
void drawCard(sf::RenderWindow& window, const Card& card, sf::Font* pFont, float x, float y)
{
	// the card body
	sf::RectangleShape cardShape(sf::Vector2f(70.f, 100.f));

	// center origin so (x, y) refers to the center of the card
	sf::Vector2f origin = cardShape.getLocalBounds().getCenter();
	cardShape.setOrigin(origin);

	cardShape.setPosition(sf::Vector2f(x, y));
	cardShape.setOutlineThickness(2.f);
	cardShape.setOutlineColor(sf::Color::Black);

	// face down, just draw the back
	if (card.getHidden())
	{
		cardShape.setFillColor(sf::Color(30, 60, 150));
		window.draw(cardShape);

		// little inner rectangle so the back looks decorated
		sf::RectangleShape pattern(sf::Vector2f(54.f, 84.f));
		pattern.setOrigin(pattern.getLocalBounds().getCenter());
		pattern.setPosition(sf::Vector2f(x, y));
		pattern.setFillColor(sf::Color(60, 90, 180));
		pattern.setOutlineThickness(1.f);
		pattern.setOutlineColor(sf::Color(100, 130, 220));
		window.draw(pattern);
		return;
	}

	// face up, white background
	cardShape.setFillColor(sf::Color::White);
	window.draw(cardShape);

	// if no font we just leave it blank white
	if (pFont == nullptr)
	{
		return;
	}

	// pick the color based on suit
	sf::Color textColor = sf::Color::Black;
	if (card.getSuit() == Suit::DIAMOND || card.getSuit() == Suit::HEART)
	{
		textColor = sf::Color::Red;
	}

	//get the unicode symbol for the suit
	sf::String suitChar = getSuitSymbol(card.getSuit());

	// top left corner, rank stacked above suit
	sf::Text rankTopLeft(*pFont);
	rankTopLeft.setString(card.getSymbol());
	rankTopLeft.setCharacterSize(18);
	rankTopLeft.setFillColor(textColor);
	rankTopLeft.setPosition(sf::Vector2f(x - 30.f, y - 45.f));
	window.draw(rankTopLeft);

	sf::Text suitTopLeft(*pFont);
	suitTopLeft.setString(suitChar);
	suitTopLeft.setCharacterSize(20);
	suitTopLeft.setFillColor(textColor);
	suitTopLeft.setPosition(sf::Vector2f(x - 30.f, y - 28.f));
	window.draw(suitTopLeft);

	sf::Text suitCenter(*pFont);
	suitTopLeft.setString(suitChar);
	suitTopLeft.setCharacterSize(40);
	suitTopLeft.setFillColor(textColor);
	sf::FloatRect centerBounds = suitCenter.getLocalBounds();
	suitCenter.setOrigin(centerBounds.getCenter());
	suitCenter.setPosition(sf::Vector2f(x,y));
	window.draw(suitCenter);

	// bottom right corner, rank stacked above suit (mirrors top left)
	sf::Text rankBottomRight(*pFont);
	rankBottomRight.setString(card.getSymbol());
	rankBottomRight.setCharacterSize(18);
	rankBottomRight.setFillColor(textColor);
	rankBottomRight.setPosition(sf::Vector2f(x + 14.f, y + 8.f));
	window.draw(rankBottomRight);

	sf::Text suitBottomRight(*pFont);
	suitBottomRight.setString(suitChar);
	suitBottomRight.setCharacterSize(20);
	suitBottomRight.setFillColor(textColor);
	suitBottomRight.setPosition(sf::Vector2f(x + 14.f, y + 25.f));
	window.draw(suitBottomRight);
}

// draws a hand of cards centered at (x, y)
void drawHand(sf::RenderWindow& window, const vector<Card>& cards, sf::Font* pFont, float x, float y)
{
	float spacing = 10.f;
	float cardWidth = 70.f;
	int size = cards.size();

	// figure out where the leftmost card goes so the whole hand is centered on x
	float xi = x - (size / 2.0 - 0.5) * (spacing + cardWidth);

	for (const Card& card : cards)
	{
		drawCard(window, card, pFont, xi, y);
		xi += cardWidth + spacing;
	}
}