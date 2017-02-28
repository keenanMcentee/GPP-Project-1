#include <Buttons.h>


/// <summary>
/// Base constructor for our buttons
/// </summary>
Buttons::Buttons() : Widget(sf::Vector2f(0, 0), (1), (1))
{
	m_colorOn = sf::Color::White;
	m_colorOff = sf::Color::White;

}
/// <summary>
/// Initialiser method that handles setting up all elements related to the button.
/// </summary>
/// <param name="position"></param>
/// <param name="width"></param>
/// <param name="height"></param>
/// <param name="on"></param>
/// <param name="off"></param>
/// <param name="rectColor"></param>
/// <param name="text"></param>
/// <param name="font"></param>
void Buttons::initialise(sf::Vector2f position, float width, float height, sf::Color on, sf::Color off, sf::Color rectColor, std::string text, Font *font)
{

	m_text.setString(text);
	m_text.setFont(*font);
	m_position = position;
	m_width = width;
	m_height = height;
	m_rect.setPosition(m_position);
	m_rect.setSize(sf::Vector2f(width, height));

	m_colorOn = on;
	m_colorOff = off;
	m_rect.setOutlineColor(m_colorOn);
	m_text.setCharacterSize(m_height / 2);
	m_text.setPosition(m_position.x + (m_width / 2.0f) - (m_text.getCharacterSize() / 2.0f * (m_text.getString().getSize() / 2.0f)),
		m_position.y + m_height / 2.0f - m_text.getCharacterSize() / 2.0f);
	m_rect.setFillColor(rectColor);
}
/// <summary>
/// Alternative initialiser method that allows us to use a texture instead of text.
/// </summary>
/// <param name="position"></param>
/// <param name="width"></param>
/// <param name="height"></param>
/// <param name="on"></param>
/// <param name="off"></param>
/// <param name="rectColor"></param>
/// <param name="texture"></param>
void Buttons::initialise(sf::Vector2f position, float width, float height, sf::Color on, sf::Color off, sf::Color rectColor, sf::Texture *texture)
{
	m_position = position;
	m_width = width;
	m_height = height;
	m_sprite.setTexture(*texture);
	m_rect.setPosition(m_position);
	m_rect.setSize(sf::Vector2f(width, height));
	m_colorOn = on;
	rectColor.a = 0;
	m_rect.setFillColor(rectColor);
	m_rect.setOutlineColor(m_colorOn);
	m_sprite.setPosition(m_position);
	m_sprite.setScale(m_width / texture->getSize().x, m_height / texture->getSize().y);
}
/// <summary>
/// Third alternative initialiser that allows us to apply a texture and text on top of it.
/// </summary>
/// <param name="position"></param>
/// <param name="width"></param>
/// <param name="height"></param>
/// <param name="on"></param>
/// <param name="off"></param>
/// <param name="rectColor"></param>
/// <param name="text"></param>
/// <param name="font"></param>
/// <param name="texture"></param>
void Buttons::initialise(sf::Vector2f position, float width, float height, sf::Color on, sf::Color off, sf::Color rectColor, std::string text, Font *font, sf::Texture *texture)
{

	m_text.setString(text);
	m_text.setFont(*font);
	m_position = position;
	m_width = width;
	m_height = height;
	m_rect.setPosition(m_position);
	m_rect.setSize(sf::Vector2f(width, height));

	m_colorOn = on;
	m_colorOff = off;
	m_rect.setOutlineColor(m_colorOn);

	m_text.setCharacterSize(m_height / 2);
	m_text.setPosition(m_position.x + (m_width / 2.0f) - (m_text.getCharacterSize() / 2.0f * (m_text.getString().getSize() / 2.0f)),
		m_position.y + m_height / 2.0f - m_text.getCharacterSize() / 2.0f);

	m_rect.setFillColor(rectColor);

	m_sprite.setTexture(*texture);
	m_sprite.setPosition(m_position);
	m_sprite.setScale(m_width / texture->getSize().x, m_height / texture->getSize().y);
}
/// <summary>
/// Update method that handles outlining the button if it is selected. It also changes the text colour if there is any text.
/// </summary>
void Buttons::update()
{
	if (m_highlighted)
	{
		m_rect.setOutlineThickness(2);
		m_text.setColor(m_colorOn);
	}
	else
	{
		m_rect.setOutlineThickness(0);
		m_text.setColor(m_colorOff);
	}
	if (m_sprite.getTexture() != NULL)
	{
		sf::Color empty = m_rect.getFillColor();
		empty.a = 0;
		m_rect.setFillColor(empty);
	}
}
/// <summary>
/// Render method for our button which handles drawing all elements related to it.
/// </summary>
/// <param name="window"></param>
void Buttons::draw(RenderWindow *window)
{
	window->draw(m_rect);
	if (m_sprite.getTexture() != NULL)
	{
		window->draw(m_sprite);
	}
	if (m_text.getString() != "")
	{
		window->draw(m_text);
	}

}
Buttons::~Buttons()
{
}
