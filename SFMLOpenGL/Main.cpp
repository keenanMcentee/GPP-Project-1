#include <Game.h>

int main(void)
{
	sf::ContextSettings settings;
	settings.depthBits = 24u;
	settings.antialiasingLevel = 2u;
	Game& game = Game(settings);
	game.run();
}