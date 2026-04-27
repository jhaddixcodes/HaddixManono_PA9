/*
	Author: James Haddix
	Written: Apr 25 2026
	Last Updated: Apr 25 2026
	Description: InputField class inheriting from GameObject that can be typed into and submitted.
*/

#ifndef INPUTFIELD_HPP
#define INPUTFIELD_HPP

#include "GameObject.hpp"
#include <SFML/Graphics.hpp>
#include <string>

using std::string;

// an input field used for entering the player's bet
class InputField : public GameObject
{
public:

	/**
	* @brief Constructs a new InputField object.
	*/
	InputField(float x, float y, float width, float height);
	~InputField();

	// overridden from GameObject
	void draw(sf::RenderWindow& window) override;

	// checks if the given mouse position is inside this button
	bool isClicked(int mouseX, int mouseY);

	/**
	* @brief Handles keyboard input (pressing key, backspace, etc., you get the gist)
	*/
	void handleInput(const sf::Event::TextEntered& text);

	/**
	* @brief Clears the text in the input.
	*/
	void clear();

	/**
	* @return Whether the text is empty.
	*/
	bool empty();

	/**
	* @return m_inputText, the text inside the input.
	*/
	string getText();
	
	/**
	* @return If the box is focused.
	*/
	bool getFocused();

	/**
	* @brief Sets the font for the input text.
	*/
	void setFont(sf::Font* font);

	/**
	* @brief Sets whether the input field is currently focused.
	*/
	void setFocused(bool focused);

private:
	string m_inputText;
	bool m_focused;
	float m_displayWidth;
	float m_displayHeight;
	sf::Font* m_pFont;  // not owned
};

#endif