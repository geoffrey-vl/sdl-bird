#ifndef GAME_H
#define GAME_H

#include <SDL2/SDL.h>
#include <string>
#include "texture.h"
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
	Texture* _bird;
};

#endif // GAME_H