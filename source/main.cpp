#include "game.h"
#include "logger/logger.h"

int main(int argc, char *argv[])
{
	Game game("sdl-bird");
	if(!game.init(Const::GAME_WIDTH, Const::GAME_HEIGHT)) {
		return -1;
	}
	
	while(game.running())
	{
		uint64_t frame_start =  SDL_GetTicks64();
		game.handleEvents();
		game.update(Const::DELAY_TIME);
		game.render();

		uint64_t frame_time = SDL_GetTicks64() - frame_start;
		if(frame_time < Const::DELAY_TIME)
		{
			SDL_Delay((int)(Const::DELAY_TIME - frame_time));
		}
	}
	Logger::debug("GAME", "closing game");
	game.clean();
	return 0;
}
