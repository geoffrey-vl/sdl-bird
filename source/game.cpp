#include "game.h"
#include "logger/logger.h"

static const char* TAG = "GAME";

Game::Game(const std::string& name) :
	_name(name),
	_running(false),
	_window(nullptr),
	_renderer(nullptr),
	_bird(0, 0),
	_is_level_setup(false)
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

	if(!loadAssets()) {
		return false;
	}

	_running = true;
	return true;
}

bool Game::loadAssets()
{
	Logger::debug(TAG, "Loading assets");
	for(auto& box : _piramide) {
		if(!box.loadData(_renderer)) {
			return false;
		}
	}
	if(!_bird.loadData(_renderer)) {
		return false;
	}
	
	return true;
}

void Game::setup_level()
{
	int pir_startpos_x = (Const::GAME_WIDTH/2)-(Const::OBJ_WIDTH/2);
	static constexpr int BOX_TOPPLANE_OFFSET = 48;
	int pir_startpos_y = BOX_TOPPLANE_OFFSET;
	int row = 0;
	int cols = 0;
	static constexpr int ROWS = 7;
	int i = 0;
	while(row < ROWS) {
		for (int col=0; col<=row; col++) {
			_piramide[i].setPos(pir_startpos_x+(col*Const::OBJ_WIDTH), pir_startpos_y);
			i++;
		}		
		row++;
		pir_startpos_x -= static_cast<int>(Const::OBJ_WIDTH/2);
		pir_startpos_y += BOX_TOPPLANE_OFFSET;
	}
	
	_bird.setPos((Const::GAME_WIDTH/2)-(Const::OBJ_WIDTH/2), 0);
}

bool Game::running()
{
	return _running;
}

void Game::render()
{
	SDL_RenderClear(_renderer); // clear the renderer to the draw color

	for(auto& box : _piramide) {
		box.draw(_renderer);
	}
	_bird.draw(_renderer);

	SDL_RenderPresent(_renderer); // draw to the screen
}

void Game::update(uint64_t timespan_ms)
{
	if (!_is_level_setup) {
		setup_level();
		_is_level_setup = true;
		_bird.setVelocity({10,10});
	}
	for(auto& box : _piramide) {
		box.update(timespan_ms);
	}
	_bird.update(timespan_ms);
	if( (_bird.getX() > Const::GAME_WIDTH) || (_bird.getY() > Const::GAME_HEIGHT) ) {
		//reset bird pos when it moves out of the window
		_bird.setPos((Const::GAME_WIDTH/2)-(Const::OBJ_WIDTH/2), 0);
	}
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
	_bird.unloadData();
	for(auto& box : _piramide) {
		box.unloadData();
	}
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