#include "Label.h"
/// <summary>
/// Base constructor for our label that sets default values for the widget
/// </summary>
Label::Label() : Widget(sf::Vector2f(0, 0), (0), (0))
{

}
/// <summary>
/// Basic Label constructor that takes in a string for the text, vector for position and a Font.
/// </summary>
/// <param name="text"></param>
/// <param name="position"></param>
/// <param name="font"></param>
void Label::intialise(string text, Vector2f position, Font* font)
{
	m_position = position;
	m_label.setPosition(position);
	m_label.setString(text);
	m_label.setFont(*font);
}
/// <summary>
/// Label constructor that takes in a text, position, font and color.
/// </summary>
/// <param name="text"></param>
/// <param name="position"></param>
/// <param name="font"></param>
/// <param name="color"></param>
void Label::intialise(string text, Vector2f position, Font* font, Color color)
{
	m_position = position;
	m_label.setString(text);
	m_label.setPosition(m_position);
	m_label.setFont(*font);
	m_label.setColor(color);
}
/// <summary>
/// More advanced Label Constructor that takes in a text, position, font, rotation, characterSize and color.
/// </summary>
/// <param name="text"></param>
/// <param name="position"></param>
/// <param name="font"></param>
/// <param name="rotation"></param>
/// <param name="characterSize"></param>
/// <param name="color"></param>
void Label::intialise(string text, Vector2f position, Font* font, Color color, float rotation, int characterSize)
{
	m_position = position;
	m_label.setPosition(m_position);
	m_label.setString(text);
	m_label.setFont(*font);
	m_label.setColor(color);
	m_label.setRotation(rotation);
	m_label.setCharacterSize(characterSize);
}

/// <summary>
/// return the string associated with the label.
/// </summary>
/// <returns></returns>
string Label::getText()
{
	return m_label.getString();
}
/// <summary>
/// set new text to the label.
/// </summary>
/// <param name="text"></param>
void Label::setText(string text)
{
	m_label.setString(text);
}
/// <summary>
/// Draw method for the label that sends the information needed to the window to later be displayed.
/// </summary>
/// <param name="window"></param>
void Label::draw(sf::RenderWindow *window)
{
	window->draw(m_label);
}

