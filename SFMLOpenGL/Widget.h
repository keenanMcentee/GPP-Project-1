#include <SFML/Graphics.hpp>
#ifndef WIDGET
#define WIDGET
using namespace sf;
/// <summary>
/// Base class for all our UI widgets in the game.
/// @Author: Keenan McEntee
/// @Written: 2/7/2017
/// @Approx time: 3.5hrs
/// @Edits:
/// </summary>
class Widget
{
public:
	Widget(sf::Vector2f position, float width, float height);
	Vector2f getPosition();
	void setPosition(Vector2f position);
	bool getHighlighted();
	void setHightlighted(bool highlighted);
	bool getSelected();
	void setSelected(bool selected);

protected:
	Vector2f m_position;
	bool m_highlighted;
	bool m_selected;
	RectangleShape m_rect;
	float m_width;
	float m_height;
	sf::Color m_colorOn;
	sf::Color m_colorOff;
};

#endif // !WIDGET


