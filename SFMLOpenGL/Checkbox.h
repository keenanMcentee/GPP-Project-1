#include "Widget.h"
#ifndef CHECKBOX
#define CHECKBOX
/// <summary>
/// Checkbox UI element.
/// @Authod: Keenan McEntee
/// @Date: 8/2/2017
/// @Time: 20minutes.
/// </summary>
class Checkbox : public Widget
{
public:
	Checkbox();
	~Checkbox();
	void initialise(sf::Vector2f position, int width, int height, sf::Color color, sf::Color colorHighlight);
	void draw(RenderWindow *window);
	void update();
	RectangleShape m_chkBox;
	Color m_chkColor;
};
#endif // !CHECKBOX



