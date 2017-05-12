#include <iostream>
#include <cstdlib>
#include <string>
#include <cmath>
#include "GamePlayState.h"
using namespace cgf;
int main(int argc, char **argv)
{
    cgf::Game game(5,30);

	game.init("Framework com estados, sprites e tiling",800,600,false);
    GamePlayState state = GamePlayState();
    game.changeState(&state);

	while(game.isRunning())
	{
		game.handleEvents();
		game.update();
		game.draw();
	}

	// cleanup the engine
	game.clean();

    return 0;
}
