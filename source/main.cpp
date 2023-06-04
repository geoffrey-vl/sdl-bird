#include "game.h"
#include "logger/logger.h"

int main(int argc, char *argv[])
{
	Game game("SdlCppGame");
	if(!game.init(100, 100)) {
		return -1;
	}
	while(game.running())
	{
		game.handleEvents();
		game.update();
		game.render();
		SDL_Delay(10);
	}
	Logger::debug("GAME", "closing game");
	game.clean();
	return 0;
}
