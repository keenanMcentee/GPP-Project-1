#ifndef XBOX360CONTROLLER
#define XBOX360CONTROLLER

#include <SFML\Graphics.hpp>

//Author: Original template by Peter Lowe. Edits by Keenan McEntee

/// <summary>
/// Controller Data that contains infomartion on the gamepads state.
/// </summary>
struct GamePadState
{
	//Booleans to check if the button is pressed
	bool A;
	bool B;
	bool X;
	bool Y;
	bool LB;
	bool RB;
	bool LeftThumbstickDown;
	bool RightThumbstickDown;
	bool d_Down;
	bool d_Up;
	bool d_Left;
	bool d_Right;
	bool back;
	bool start;
	//Floats to store how far the trigger has been pulled
	float LTrigger;
	float RTrigger;
	//Vectors to store the X and Y co-ordinate of the analog stick using center(stationary) as 0,0
	sf::Vector2f RightThumbStick;
	sf::Vector2f LeftThumbStick;
};
/// <summary>
/// Xbox controller class to check the state of controller
/// </summary>
class xbox360Controller
{
private:
	//Deadzone for the D-Pad
	const int DPADTHRESHOLD = 50;
public:
	//ID of the controller that's conected.
	int sf_Joystick_index;
	//State of buttons
	GamePadState m_currentState;
	//State of buttons on controller during last frame.
	GamePadState m_previousState;
	//Constructor
	xbox360Controller();
	//Deconstructor
	~xbox360Controller();
	//Method that handles updating the gamepad information
	void update();
	//Bool For checking if the controller is connected
	bool isConnected(int i);
	//Bool to check if we need to connect a controller.
	bool connect();

};
#endif // !XBOX360CONTROLLER