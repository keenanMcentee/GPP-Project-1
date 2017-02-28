#include <SFML\Graphics.hpp>
#include <SFML\Audio.hpp>
#include "Label.h"
#include "Slider.h"
#include "Buttons.h"
#include "Checkbox.h"
#include "Xbox360Controller.h"
#include "ScreenManager.h"

//Author: Keenan McEntee
//Time started: 27/1/2017
//Header file to handle all the different screens instead of making individual header files.
//Edits:	27/1/2017 - Added License
//			29/1/2017 - Added Splash Screen
//			30/1/2017 - Added Main Menu
//			2/2/2017 -	Added Credits, options and play.
//			7/2/2017 -	Merged Screens branch back to Master branch on github.
#ifndef LICENCE
#define LICENCE

class Licence
{
public:
	Licence();
	void initialise(sf::Font *font);
	~Licence();
	Slider m_slider;
	void update(double time, xbox360Controller *gamePad, GameState *currentGameState);
	void render(sf::RenderWindow *window);

private:
	Label screen;
};
#endif // !CREDITS


#ifndef SPLASH
#define SPLASH
class Splash
{
public:
	Splash();
	~Splash();
	void initialise(sf::Font *font);
	void update(double time, xbox360Controller *gamePad, GameState *currentGameState);
	void render(sf::RenderWindow *window);

private:
	Label screen;
	Buttons startBtn;
};

#endif

#ifndef MENU
#define MENU
class Menu
{
public:
	Menu();
	void initialise(sf::Font *font);

	void update(double time, xbox360Controller *gamePad, GameState *currentGameState, bool* fromMenu);
	void render(sf::RenderWindow *window);
	void moveSelection(xbox360Controller *gamePad, GameState *currentGameState, bool* fromMenu);
private:
	Label screen;
	Buttons playBtn, optionsBtn, creditsBtn, exitBtn;
	sf::Texture btnTexture;
};

#endif

#ifndef CREDITS
#define CREDITS

#include <iostream>
#include <fstream>
class Credits
{
public:

	Credits();
	~Credits();
	void initialise(sf::Font *font);
	void update(sf::Time deltaTime, xbox360Controller *gamePad, GameState *currentGameState);
	void render(sf::RenderWindow *window);

private:
	Label screen;
	Buttons m_btnBack;
	sf::Time m_cumulativeTime;
	float m_speed;
	sf::Font m_comicSans;
	sf::Text m_textMessage[20];
	bool m_header[20];
	int m_textIndex;
	int m_timeBetweenTexts;
	std::string m_text;
};

#endif

#ifndef OPTIONS
#define OPTIONS
class Options
{
public:

	Options();
	void initialise(sf::Font *font);
	void update(double time, xbox360Controller *gamePad, GameState *currentGameState);
	void render(sf::RenderWindow *window);
	void selectionHandler(xbox360Controller * gamepad, GameState *currentGameState);
	bool fromMenu;
private:

	sf::Music bgMusic;
	Label screen;
	Label m_lblSliderVolume;
	Slider m_sliderVolume;
	Label m_lblMusicChk;
	Checkbox m_chkMusicToggle;
	Buttons m_btnBack;

	static const int SLIDER_VOLUME = 0, CHK_MUSIC_TOGGLE = 1, BACK_BTN = 2;

};
#endif // !OPTIONS
#ifndef PLAY
#define PLAY
class Play
{
public:
	Play();
	void initialise(sf::Font *font);

	void update(double time, xbox360Controller *gamePad, GameState *currentGameState);
	void render(sf::RenderWindow *window);
	void gamePlayControls(xbox360Controller *gamePad, GameState *currentGameState);
private:
	int highlighted;
	static const int BTN_PAUSE = 0, BTN_L = 1, BTN_R = 2;
	Buttons m_btnPause, m_btnMoveLeft, m_btnMoveRight;
	sf::Sprite playWindow;

	sf::Texture dungeonCorridor;

	Label screen;
	Slider health;
};
#endif // !PLAY

#ifndef PAUSE
#define PAUSE
class Pause
{
public:
	Pause();
	void initialise(sf::Font *font);

	void update(double time, xbox360Controller *gamePad, GameState *currentGameState, bool *fromMenu);
	void render(sf::RenderWindow *window);

private:
	int highlighted;
	static const int BTN_RESUME = 0, BTN_OPTIONS = 1, BTN_MENU = 2;
	Buttons m_btnResume, m_btnOptions, m_btnMenu;
	Label screen;
};
#endif // !PAUSE
