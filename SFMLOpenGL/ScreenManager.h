#ifndef SCREENMANAGER
#define SCREENMANAGER
/*
//Author: Keenan McEntee : Moved to seperate header for any class to see instead of being passed around constantly.

//Discrption: Simple header to store the different screens for the game so that
any class may access and see them.
*/
enum class GameState {
	License,
	Splash,
	Menu,
	Options,
	Play,
	Pause,
	Credits,
	End
};

#endif // !SCREENMANAGER
