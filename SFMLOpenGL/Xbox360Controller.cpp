#include "Xbox360Controller.h"
#include <iostream>
/// <summary>
/// Constructor 
/// </summary>
xbox360Controller::xbox360Controller()
{

}
xbox360Controller::~xbox360Controller()
{

}
/// <summary>
/// Update method which handles checking if any of the buttons are pressed and the positions of the thumbsticks.
/// </summary>
void xbox360Controller::update()
{
	m_previousState = m_currentState;
	sf::Joystick::update();
	m_currentState.A = sf::Joystick::isButtonPressed(sf_Joystick_index, 0);	//0 = A
	m_currentState.B = sf::Joystick::isButtonPressed(sf_Joystick_index, 1); //1 = B
	m_currentState.X = sf::Joystick::isButtonPressed(sf_Joystick_index, 2); //2 = X
	m_currentState.Y = sf::Joystick::isButtonPressed(sf_Joystick_index, 3); //3 = Y


	m_currentState.LB = sf::Joystick::isButtonPressed(sf_Joystick_index, 4);//4 = Left Bumper
	m_currentState.RB = sf::Joystick::isButtonPressed(sf_Joystick_index, 5);//5 = Right Bumper
	m_currentState.start = sf::Joystick::isButtonPressed(sf_Joystick_index, 7);//6 = Start
	m_currentState.back = sf::Joystick::isButtonPressed(sf_Joystick_index, 6);//7 = Back
	m_currentState.LeftThumbstickDown = sf::Joystick::isButtonPressed(sf_Joystick_index, 8);//8 = LeftThumbStick
	m_currentState.RightThumbstickDown = sf::Joystick::isButtonPressed(sf_Joystick_index, 9);//9 = RightThumbStick


																							 //D-pad input handling.
	if (sf::Joystick::getAxisPosition(0, sf::Joystick::Axis::PovX) < (DPADTHRESHOLD * -1))
	{
		m_currentState.d_Left = true;
	}
	else
	{
		m_currentState.d_Left = false;
	}
	if (sf::Joystick::getAxisPosition(0, sf::Joystick::Axis::PovX) > DPADTHRESHOLD)
	{
		m_currentState.d_Right = true;
	}
	else
	{
		m_currentState.d_Right = false;
	}
	if (sf::Joystick::getAxisPosition(0, sf::Joystick::Axis::PovY) < (DPADTHRESHOLD * -1))
	{
		m_currentState.d_Down = true;
	}
	else
	{
		m_currentState.d_Down = false;
	}
	if (sf::Joystick::getAxisPosition(0, sf::Joystick::Axis::PovY) > DPADTHRESHOLD)
	{
		m_currentState.d_Up = true;
	}
	else
	{
		m_currentState.d_Up = false;
	} //End of D-pad input handling.


	  //R = right thumbstick Y
	  //U = Rthumbstick X
	m_currentState.LeftThumbStick = sf::Vector2f(sf::Joystick::getAxisPosition(0, sf::Joystick::Axis::X), sf::Joystick::getAxisPosition(0, sf::Joystick::Axis::Y));
	//X = LeftThumbstick X
	//Y = LeftThumbstick Y
	m_currentState.RightThumbStick = sf::Vector2f(sf::Joystick::getAxisPosition(0, sf::Joystick::Axis::U), sf::Joystick::getAxisPosition(0, sf::Joystick::Axis::R));

	//Z = RightTrigger && LeftTrigger
	//If the triggers aren't pulled further than float value 5, we set it to )
	if (sf::Joystick::getAxisPosition(0, sf::Joystick::Axis::Z) < -5)
	{
		m_currentState.RTrigger = -(sf::Joystick::getAxisPosition(0, sf::Joystick::Axis::Z));
	}
	else if (sf::Joystick::getAxisPosition(0, sf::Joystick::Axis::Z) > 5)
	{
		m_currentState.LTrigger = sf::Joystick::getAxisPosition(0, sf::Joystick::Axis::Z);
	}
	else
	{
		m_currentState.LTrigger = 0;
		m_currentState.RTrigger = 0;
	}
}
bool xbox360Controller::connect()
{
	if (isConnected(3))
	{
		sf_Joystick_index = 3;
		return true;
	}
	else if (isConnected(2))
	{
		sf_Joystick_index = 2;
		return true;
	}
	else if (isConnected(1))
	{
		sf_Joystick_index = 1;
		return true;
	}
	else if (isConnected(0))
	{
		sf_Joystick_index = 0;
		return true;
	}
	else
	{
		return false;
	}
}
bool xbox360Controller::isConnected(int i)
{
	return sf::Joystick::isConnected(i);
}

