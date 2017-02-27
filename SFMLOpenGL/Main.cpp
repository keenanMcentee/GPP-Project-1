#include <Game.h>


/// @Project: Cube Game.
/// @File: Main.cpp
/// 
/// @Author: Keenan McEntee
/// @Tutorial kit by: Philip Bourke
/// 
/// @Description: OpenGL game using cubes.
/// @Date written: 23rd/february/2017 - 24th/february/2017

int main(void)
{
	sf::ContextSettings settings;
	settings.depthBits = 24u;
	settings.antialiasingLevel = 4u;
	Game& game = Game(settings);
	game.run();
}