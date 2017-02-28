#include "Widget.h"

/// <summary>
/// Constructor for all our widgets
/// </summary>
/// <param name="position"></param>
/// <param name="width"></param>
/// <param name="height"></param>
Widget::Widget(sf::Vector2f position, float width, float height)
{
	m_position = position;
	m_width = width;
	m_height = height;
	m_highlighted = false;
	m_selected = false;
}
/// <summary>
/// Return the position of the label.
/// </summary>
/// <returns></returns>
sf::Vector2f Widget::getPosition()
{
	return m_position;
}
/// <summary>
/// set a new position for the label
/// </summary>
/// <param name="position"></param>
void Widget::setPosition(Vector2f position)
{
	m_position = position;
}
/// <summary>
/// Getter for that returns if the widget is highlighted or not
/// </summary>
/// <returns></returns>
bool Widget::getHighlighted() {
	return m_highlighted;
}
/// <summary>
/// setter to change if the widget is highlighted or not
/// </summary>
/// <param name="highlighted"></param>
void Widget::setHightlighted(bool highlighted) {
	m_highlighted = highlighted;
}
/// <summary>
/// function to get if the widget was pressed.
/// </summary>
/// <returns></returns>
bool Widget::getSelected() {
	return m_selected;
}
/// <summary>
/// function to set if the widget was pressed or not
/// </summary>
/// <param name="selected"></param>
void Widget::setSelected(bool selected) {
	m_selected = selected;
}