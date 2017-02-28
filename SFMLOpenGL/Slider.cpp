#include "Slider.h"

/// <summary>
/// Base constructor for the Slider.
/// </summary>
Slider::Slider() : Widget(sf::Vector2f(0, 0), 0, 0)
{
	m_Color = sf::Color(0, 255, 0, 255);
	m_rect.setFillColor(sf::Color::Black);
}
/// <summary>
/// Initiliase method which handles setting up all the important components to a slider.
/// </summary>
/// <param name="position"></param>
/// <param name="width"></param>
/// <param name="height"></param>
/// <param name="maxValue"></param>
/// <param name="minValue"></param>
/// <param name="rectColor"></param>
void Slider::initialise(sf::Vector2f position, float width, float height, float maxValue, float minValue, sf::Color rectColor)
{
	m_position = position;
	m_width = width;
	m_height = height;
	m_rect.setPosition(m_position);
	m_rect.setSize(sf::Vector2f(width, height));
	m_rect.setOutlineColor(rectColor);
	m_maxValue = maxValue;
	m_minValue = minValue;
	m_currentValue = m_maxValue;
	m_slider.setPosition(m_position.x + 2, m_position.y + 2);

	m_Maxwidth = m_rect.getSize().x - 4;
	m_Maxheight = m_rect.getSize().y - 4;
	m_slider.setSize(sf::Vector2f(m_Maxwidth, m_Maxheight));
	m_sliderShell.setPosition(m_slider.getPosition());
	m_sliderShell.setSize(sf::Vector2f(m_Maxwidth, m_Maxheight));
	m_sliderShell.setOutlineColor(sf::Color::White);
	m_sliderShell.setFillColor(sf::Color::Black);
	m_sliderShell.setOutlineThickness(2);
}
/// <summary>
/// Update method which handles all the UI design like colouors, slider width and if its highlighted.
/// </summary>
void Slider::update()
{
	m_slider.setSize(sf::Vector2f(m_Maxwidth * (m_currentValue / m_maxValue), m_Maxheight));
	m_slider.setFillColor(sf::Color(255 - (m_currentValue / m_maxValue * 255), (m_currentValue / m_maxValue) * 255, 0, 255));
	if (m_highlighted)
	{
		m_rect.setOutlineThickness(2);
	}
	else
	{
		m_rect.setOutlineThickness(0);
	}
}
void Slider::draw(RenderWindow *window)
{
	window->draw(m_rect);
	window->draw(m_sliderShell);
	window->draw(m_slider);

}
/// <summary>
/// Simple method for increasing the value of the slider.
/// </summary>
void Slider::increaseSlider()
{
	if (m_currentValue < m_maxValue)
	{
		m_currentValue += 5;
	}
}
/// <summary>
/// Function that handles decreasing the slider value.
/// </summary>
void Slider::decreaseSlider()
{
	if (m_currentValue > m_minValue)
	{
		m_currentValue -= 5;
	}
}