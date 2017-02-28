#ifndef SFML
#include "SFML/Graphics.hpp" 
#endif // !SFML


#ifndef LABEL
#define LABEL
#include "Widget.h"
using namespace sf;
using namespace std;
/// <summary>
/// Label Class
/// @Author: Keenan McEntee
/// @Def: Basic label class to be used in any UI.
/// @Date written: 30/01/2017 ~ 25mins
/// @Edits: - Keenan - 7/2/2017 - Changed to inherit from widget class. ~1hr
/// @Time taken: ~1hr 25minutes.
/// </summary>
class Label : public Widget
{
public:
	Label();
	void intialise(string text, Vector2f position, Font* font);
	void intialise(string text, Vector2f position, Font* font, Color color);
	void intialise(string text, Vector2f position, Font* font, Color color, float rotation, int m_characterSize);
	void draw(RenderWindow *window);

	Text m_label;
	string getText();
	//void draw(RenderWindow* window);
	void setText(string text);
private:

	
	float m_angle;
	int m_characterSize;
	Color m_color;
	string m_text;
};
#endif // !Label
