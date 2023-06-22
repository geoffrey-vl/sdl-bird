#include "game.h"
#include "logger/logger.h"

static const char* TAG = "GAME";

Game::Game(const std::string& name) :
	_name(name),
	_running(false),
	_window(nullptr),
	_renderer(nullptr),
	_bird(0, 0),
	_is_level_setup(false),
	_current_box(nullptr)
{
	for(int i=0; i<_piramide.size(); i++) {
		_piramide[i] = std::make_shared<Box>();
	}
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
	for(auto box : _piramide) {
		if(!box->loadData(_renderer)) {
			return false;
		}
	}
	if(!_bird.loadData(_renderer)) {
		return false;
	}
	
	return true;
}

// link one box to the other, and in the opposite direction
inline void setAdjacent(std::shared_ptr<Box> a, Direction direction, std::shared_ptr<Box> b)
{
	a->setAdjacent(direction, b);
	switch (direction)
	{
		case Direction::TOPLEFT: 
			b->setAdjacent(Direction::BOTTOMRIGHT, a);
			break;
		case Direction::TOPRIGHT: 
			b->setAdjacent(Direction::BOTTOMLEFT, a);
			break;
		case Direction::BOTTOMLEFT: 
			b->setAdjacent(Direction::TOPRIGHT, a);
			break;
		case Direction::BOTTOMRIGHT: 
			b->setAdjacent(Direction::TOPLEFT, a);
			break;
		default:
			break;
	}
}

void Game::setup_level()
{
	int pir_startpos_x = (Const::GAME_WIDTH/2)-(Const::OBJ_WIDTH/2);
	int pir_startpos_y = Const::BOX_PROJECTED_HEIGHT;
	int row = 0;
	int cols = 0;
	static constexpr int ROWS = 7;
	int i = 0;
	while(row < ROWS) {
		for (int col=0; col<=row; col++) {
			_piramide[i]->setPos(pir_startpos_x+(col*Const::OBJ_WIDTH), pir_startpos_y);
			i++;
		}		
		row++;
		pir_startpos_x -= static_cast<int>(Const::OBJ_WIDTH/2);
		pir_startpos_y += Const::BOX_PROJECTED_HEIGHT;
	}
	_current_box = _piramide[0];
	// row 1
	setAdjacent(_piramide[0], Direction::BOTTOMLEFT, _piramide[1]);
	setAdjacent(_piramide[0], Direction::BOTTOMRIGHT, _piramide[2]);
	// row 2
	setAdjacent(_piramide[1], Direction::BOTTOMLEFT, _piramide[3]);
	setAdjacent(_piramide[1], Direction::BOTTOMRIGHT, _piramide[4]);
	setAdjacent(_piramide[2], Direction::BOTTOMLEFT, _piramide[4]);
	setAdjacent(_piramide[2], Direction::BOTTOMRIGHT, _piramide[5]);
	// row 3
	setAdjacent(_piramide[3], Direction::BOTTOMLEFT, _piramide[6]);
	setAdjacent(_piramide[3], Direction::BOTTOMRIGHT, _piramide[7]);
	setAdjacent(_piramide[4], Direction::BOTTOMLEFT, _piramide[7]);
	setAdjacent(_piramide[4], Direction::BOTTOMRIGHT, _piramide[8]);
	setAdjacent(_piramide[5], Direction::BOTTOMLEFT, _piramide[8]);
	setAdjacent(_piramide[5], Direction::BOTTOMRIGHT, _piramide[9]);
	// row 4
	setAdjacent(_piramide[6], Direction::BOTTOMLEFT, _piramide[10]);
	setAdjacent(_piramide[6], Direction::BOTTOMRIGHT, _piramide[11]);
	setAdjacent(_piramide[7], Direction::BOTTOMLEFT, _piramide[11]);
	setAdjacent(_piramide[7], Direction::BOTTOMRIGHT, _piramide[12]);
	setAdjacent(_piramide[8], Direction::BOTTOMLEFT, _piramide[12]);
	setAdjacent(_piramide[8], Direction::BOTTOMRIGHT, _piramide[13]);
	setAdjacent(_piramide[9], Direction::BOTTOMLEFT, _piramide[13]);
	setAdjacent(_piramide[9], Direction::BOTTOMRIGHT, _piramide[14]);
	// row 5
	setAdjacent(_piramide[10], Direction::BOTTOMLEFT, _piramide[15]);
	setAdjacent(_piramide[10], Direction::BOTTOMRIGHT, _piramide[16]);
	setAdjacent(_piramide[11], Direction::BOTTOMLEFT, _piramide[16]);
	setAdjacent(_piramide[11], Direction::BOTTOMRIGHT, _piramide[17]);
	setAdjacent(_piramide[12], Direction::BOTTOMLEFT, _piramide[17]);
	setAdjacent(_piramide[12], Direction::BOTTOMRIGHT, _piramide[18]);
	setAdjacent(_piramide[13], Direction::BOTTOMLEFT, _piramide[18]);
	setAdjacent(_piramide[13], Direction::BOTTOMRIGHT, _piramide[19]);
	setAdjacent(_piramide[14], Direction::BOTTOMLEFT, _piramide[19]);
	setAdjacent(_piramide[14], Direction::BOTTOMRIGHT, _piramide[20]);
	// row 6
	setAdjacent(_piramide[15], Direction::BOTTOMLEFT, _piramide[21]);
	setAdjacent(_piramide[15], Direction::BOTTOMRIGHT, _piramide[22]);
	setAdjacent(_piramide[16], Direction::BOTTOMLEFT, _piramide[22]);
	setAdjacent(_piramide[16], Direction::BOTTOMRIGHT, _piramide[23]);
	setAdjacent(_piramide[17], Direction::BOTTOMLEFT, _piramide[23]);
	setAdjacent(_piramide[17], Direction::BOTTOMRIGHT, _piramide[24]);
	setAdjacent(_piramide[18], Direction::BOTTOMLEFT, _piramide[24]);
	setAdjacent(_piramide[18], Direction::BOTTOMRIGHT, _piramide[25]);
	setAdjacent(_piramide[19], Direction::BOTTOMLEFT, _piramide[25]);
	setAdjacent(_piramide[19], Direction::BOTTOMRIGHT, _piramide[26]);
	setAdjacent(_piramide[20], Direction::BOTTOMLEFT, _piramide[26]);
	setAdjacent(_piramide[20], Direction::BOTTOMRIGHT, _piramide[27]);
	
	_bird.setPos((Const::GAME_WIDTH/2)-(Const::OBJ_WIDTH/2), 4);
}

bool Game::running()
{
	return _running;
}

void Game::render()
{
	SDL_RenderClear(_renderer); // clear the renderer to the draw color

	for(auto& box : _piramide) {
		box->draw(_renderer);
	}
	_bird.draw(_renderer);

	SDL_RenderPresent(_renderer); // draw to the screen
}

inline Direction scanInput()
{
	const uint8_t* keystates = SDL_GetKeyboardState(0);
	if (keystates != 0) {
		if (keystates[SDL_SCANCODE_LEFT] == 1 && keystates[SDL_SCANCODE_UP] == 1) {
			return Direction::TOPLEFT;
		}
		if (keystates[SDL_SCANCODE_LEFT] == 1 && keystates[SDL_SCANCODE_DOWN] == 1) {
			return Direction::BOTTOMLEFT;
		}
		if (keystates[SDL_SCANCODE_RIGHT] == 1 && keystates[SDL_SCANCODE_UP] == 1) {
			return Direction::TOPRIGHT;
		}
		if (keystates[SDL_SCANCODE_RIGHT] == 1 && keystates[SDL_SCANCODE_DOWN] == 1) {
			return Direction::BOTTOMRIGHT;
		}
	}
	return Direction::NONE;
}

void Game::update(uint64_t timespan_ms)
{
	if (!_is_level_setup) {
		setup_level();
		_is_level_setup = true;
	}

	for(auto& box : _piramide) {
		box->update(timespan_ms);
	}

	// handle the user input
	if (!_bird.isMoving()) {
		Direction direction = scanInput();
		if (direction != Direction::NONE) {
			// check if this a valid box to jump to
			std::shared_ptr<Box> target_box = _current_box->getAdjecent(direction);
			if (target_box != nullptr) {
				_bird.setDirection(direction);
				_current_box = target_box;
			}
		}
	}

	// process bird
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
		box->unloadData();
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