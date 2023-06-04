#include "game.h"
#include "logger/logger.h"

static const char* TAG = "GAME";

Game::Game(const std::string& name) :
	_name(name),
	_running(false),
	_window(nullptr),
	_renderer(nullptr),
	_bird(nullptr)
{
}

Game::~Game()
{
	clean();
}

bool Game::init(int width, int height)
{
	if(_running) {
		Logger::warn(TAG, "Already initialized");
		return true;
	}
	Logger::debug(TAG, "Initializing SDL");
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER | SDL_INIT_NOPARACHUTE | SDL_INIT_GAMECONTROLLER) != 0) {
		Logger::error(TAG, "SDL_Init failed");
		return false;
	}
	SDL_version version;
	SDL_GetVersion(&version);
	Logger::debug(TAG, "SDL Version = %d.%d.%d", version.major, version.minor, version.patch);

	uint32_t flags = 0;
	flags |= SDL_WINDOW_RESIZABLE;
	flags |= SDL_WINDOW_ALLOW_HIGHDPI; // for Retina displays
	_window = SDL_CreateWindow(_name.c_str(), SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, flags); 
	if(_window == nullptr) {
		Logger::error(TAG, "couldn't create window");
		return false;
	}
	// Make absolutely sure that VSync will be off, to prevent timer issues.
	SDL_SetHint(SDL_HINT_RENDER_VSYNC, "0");

	_renderer = SDL_CreateRenderer(_window, -1 , SDL_RENDERER_ACCELERATED | SDL_RENDERER_TARGETTEXTURE);
	SDL_RendererInfo renderer_info;
	if (SDL_GetRendererInfo(_renderer, &renderer_info) != 0) {
		Logger::error(TAG, "failed retrieving renderer info");
		return false;
	}
	Logger::debug(TAG, "renderer = %s", renderer_info.name);

	Logger::debug(TAG, "Loading assets");
	_bird = new Bird(0, 0);
	if(!_bird->loadData(_renderer)) {
		return false;
	}

	_running = true;
	return true;
}

bool Game::running()
{
	return _running;
}

void Game::render()
{
	SDL_RenderClear(_renderer); // clear the renderer to the draw color

	_bird->draw(_renderer);

	SDL_RenderPresent(_renderer); // draw to the screen
}

void Game::update()
{
}

void Game::handleEvents()
{
	SDL_Event event;
	if(SDL_PollEvent(&event))
	{
		switch (event.type)
		{
			case SDL_QUIT:
				_running = false;
				break;
			default:
				break;
		}
	}
}

void Game::clean()
{
	delete _bird;
	if (_renderer) {
		SDL_DestroyRenderer(_renderer);
		_renderer = nullptr;
	}
	if (_window) {
		SDL_DestroyWindow(_window);
		_window = nullptr;
	}
	SDL_Quit();
}