#ifndef GAME_H
#define GAME_H

#include <SDL2/SDL.h>
#include <string>
#include <array>
#include "constants.h"
#include "gameobjects/bird.h"
#include "gameobjects/box.h"

class Game
{
public:
	Game(const std::string& name);
	virtual ~Game();

	bool init(int width, int height);
	void render();
	void update();
	void handleEvents();
	void clean();
	bool running();

private:
	std::string _name;
	bool _running;
	SDL_Window* _window;
	SDL_Renderer* _renderer;

	Bird _bird;
	std::array<Box, Const::NR_OF_BOXES> _piramide;
	bool _is_level_setup;

	bool loadAssets();
	void setup_level();
};

#endif // GAME_H