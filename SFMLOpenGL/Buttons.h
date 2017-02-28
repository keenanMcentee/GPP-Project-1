#ifndef BUTTONS
#define BUTTONS
#include "Widget.h"
/*
//AUTHOR: Keenan McEntee
//Description: Button ui-element.
//Date created: 20/2/2017
//Time worked on: 1.5hrs
//Edits: None.
//Bugs: None found during simple testing.
*/
class Buttons : public Widget
{
public:
	Buttons();
	~Buttons();
	void initialise(sf::Vector2f position, float width, float height, sf::Color on, sf::Color off, sf::Color rectColor, std::string text, Font *font);
	void initialise(sf::Vector2f position, float width, float height, sf::Color on, sf::Color off, sf::Color rectColor, sf::Texture *texture);
	void initialise(sf::Vector2f position, float width, float height, sf::Color on, sf::Color off, sf::Color rectColor, std::string text, Font *font, sf::Texture *texture);
	void update();
	void draw(RenderWindow *window);
	sf::Sprite m_sprite;
	sf::Text m_text;

};
#endif // !BUTTONS



