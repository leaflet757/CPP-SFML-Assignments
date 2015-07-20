#include "Game.h"


int main()
{
	OpenSFMLEngine::Game game;

	game.initActors();
	game.start();

	return 0;
}