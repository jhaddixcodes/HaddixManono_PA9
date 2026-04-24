#include "Card.h"

// default card is Ace of Hearts, face down
Card::Card()
{
	cardRank = 1;
	cardSuit = 0;
	faceUp = false;
	pFont = nullptr;
	xPos = 0;
	yPos = 0;
}

Card::Card(int rank, int suit, float x, float y)
{
	cardRank = rank;
	cardSuit = suit;
	faceUp = false;
	pFont = nullptr;
	xPos = x;
	yPos = y;
}

Card::~Card()
{
}

void Card::setRank(int rank)
{
	cardRank = rank;
}

void Card::setSuit(int suit)
{
	cardSuit = suit;
}

void Card::setFaceUp(bool up)
{
	faceUp = up;
}

void Card::setFont(sf::Font* font)
{
	pFont = font;
}

int Card::getRank()
{
	return cardRank;
}

int Card::getSuit()
{
	return cardSuit;
}

bool Card::isFaceUp()
{
	return faceUp;
}

// turn the rank number into what should show on the card
std::string Card::getRankString()
{
	if (cardRank == 1) return "A";
	if (cardRank == 11) return "J";
	if (cardRank == 12) return "Q";
	if (cardRank == 13) return "K";
	// 2 through 10
	return std::to_string(cardRank);
}

// letter for the suit (H, D, C, S)
std::string Card::getSuitString()
{
	if (cardSuit == 0) return "H";
	if (cardSuit == 1) return "D";
	if (cardSuit == 2) return "C";
	if (cardSuit == 3) return "S";
	return "?";
}

// hearts and diamonds are red, clubs and spades are black
sf::Color Card::getSuitColor()
{
	if (cardSuit == 0 || cardSuit == 1)
	{
		return sf::Color::Red;
	}
	return sf::Color::Black;
}

void Card::draw(sf::RenderWindow& window)
{
	// the card body
	sf::RectangleShape cardShape(sf::Vector2f(70.f, 100.f));
	cardShape.setPosition(sf::Vector2f(xPos, yPos));
	cardShape.setOutlineThickness(2.f);
	cardShape.setOutlineColor(sf::Color::Black);

	// face down - just draw the back
	if (!faceUp)
	{
		cardShape.setFillColor(sf::Color(30, 60, 150));
		window.draw(cardShape);

		// little inner rectangle so the back looks decorated
		sf::RectangleShape pattern(sf::Vector2f(54.f, 84.f));
		pattern.setPosition(sf::Vector2f(xPos + 8.f, yPos + 8.f));
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
	rankText.setString(getRankString());
	rankText.setCharacterSize(20);
	rankText.setFillColor(getSuitColor());
	rankText.setPosition(sf::Vector2f(xPos + 6.f, yPos + 4.f));
	window.draw(rankText);

	// big suit letter in the middle
	sf::Text suitText(*pFont);
	suitText.setString(getSuitString());
	suitText.setCharacterSize(36);
	suitText.setFillColor(getSuitColor());
	suitText.setPosition(sf::Vector2f(xPos + 22.f, yPos + 35.f));
	window.draw(suitText);

	// rank again in the bottom-right
	sf::Text rankText2(*pFont);
	rankText2.setString(getRankString());
	rankText2.setCharacterSize(20);
	rankText2.setFillColor(getSuitColor());
	rankText2.setPosition(sf::Vector2f(xPos + 52.f, yPos + 76.f));
	window.draw(rankText2);
}