#ifndef SLIDER
#define SLIDER

#include "Widget.h"

/*
//AUTHOR: Keenan McEntee
//Description: Slider ui-element.
//Date created: 20/2/2017
//Time worked on: 1.5hrs
//Edits: None.
//Bugs: None found during simple testing.
*/
class Slider : public Widget
{
public:
	Slider();
	void initialise(sf::Vector2f position, float width, float height, float maxValue, float minValue, sf::Color rectColor);
	void update();
	void draw(RenderWindow *window);
	void increaseSlider();
	void decreaseSlider();
	float m_currentValue;	//Current value set on the slider.
private:
	float m_maxValue;		//Max value set on the slider.
	float m_minValue;		//Min value set on the slider.
	float m_upValue; //Value by which we decrease slider.
	float m_downValue;//Value by which we increase slider.
	sf::Color m_Color;		//Current colour of the slider.
	sf::RectangleShape m_slider; //Internal rectangle of the slider.
	sf::RectangleShape m_sliderShell; //surround of the slider to show its full size.
	float m_Maxwidth;		//Width & height of the inner slider.
	float m_Maxheight;
};

#endif // !SLIDER