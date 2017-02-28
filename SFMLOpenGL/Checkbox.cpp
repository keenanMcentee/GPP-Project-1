#include "Checkbox.h"


/// <summary>
/// Base constructor for the checkbox
/// </summary>
Checkbox::Checkbox() : Widget(sf::Vector2f(0, 0), (1), (1))
{
	m_colorOn = sf::Color::White;
	m_colorOff = sf::Color::White;
	m_rect.setFillColor(sf::Color::Color(0, 0, 0, 0));
}
/// <summary>
/// Initialise method that handles setting up all the components to our checkbox.
/// </summary>
/// <param name="position"></param>
/// <param name="width"></param>
/// <param name="height"></param>
/// <param name="color"></param>
/// <param name="colorHighlight"></param>
void Checkbox::initialise(sf::Vector2f position, int width, int height, sf::Color color, sf::Color colorHighlight) {
	m_chkColor = color;
	m_position = position;
	m_width = width;
	m_height = height;
	m_chkBox.setPosition(m_position);
	m_chkBox.setSize(sf::Vector2f(width, height));

	m_chkBox.setOutlineColor(m_chkColor);
	m_chkBox.setOutlineThickness(2);

	m_rect.setPosition(sf::Vector2f(m_position.x - 3, m_position.y - 3));
	m_rect.setSize(sf::Vector2f(m_chkBox.getSize().x + 6, m_chkBox.getSize().y + 6));
	m_rect.setOutlineColor(colorHighlight);
	colorHighlight.a = 0;
	m_rect.setFillColor(colorHighlight);
}
/// <summary>
/// Draw method for our checkbox.
/// </summary>
/// <param name="window"></param>
void Checkbox::draw(RenderWindow *window) {
	window->draw(m_chkBox);
	window->draw(m_rect);
}
/// <summary>
/// Simple update method to show whether the checkbox is enabled or not.
/// </summary>
void Checkbox::update() {
	if (m_highlighted)
	{
		m_rect.setOutlineThickness(2);
	}
	else
	{
		m_rect.setOutlineThickness(0);
	}

	if (m_selected)
	{
		m_chkColor.a = 255;
	}
	else
	{
		m_chkColor.a = 0;
	}
	m_chkBox.setFillColor(sf::Color(m_chkColor.r, m_chkColor.g + 180, m_chkColor.b, m_chkColor.a));
}

Checkbox::~Checkbox()
{
}
