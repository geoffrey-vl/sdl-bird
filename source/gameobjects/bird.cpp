#include "bird.h"
#include "../constants.h"
#include "../logger/logger.h"

static const char* TAG = "Bird";

Bird::Bird(int x, int y) : 
    GameObject(x, y),
    _texture_down("data/assets/bird_down.png"),
    _texture_up("data/assets/bird_up.png"),
    _animation(),
    _direction(Direction::BOTTOMLEFT)
{
}

void Bird::draw(SDL_Renderer* renderer)
{
    switch (_direction)
    {
        case Direction::BOTTOMLEFT:
            _texture_down.setPos(_pos.getX(), _pos.getY());
            _texture_down.setFlip(SDL_FLIP_HORIZONTAL);
            _texture_down.render(renderer);
            break;
         case Direction::BOTTOMRIGHT:
            _texture_down.setPos(_pos.getX(), _pos.getY());
            _texture_down.setFlip(SDL_FLIP_NONE);
            _texture_down.render(renderer);
            break;
        case Direction::TOPLEFT:
            _texture_up.setPos(_pos.getX(), _pos.getY());
            _texture_up.setFlip(SDL_FLIP_HORIZONTAL);
            _texture_up.render(renderer);
            break;
        case Direction::TOPRIGHT:
            _texture_up.setPos(_pos.getX(), _pos.getY());
            _texture_up.setFlip(SDL_FLIP_NONE);
            _texture_up.render(renderer);
            break;
    }
}

bool Bird::isMoving()
{
    return _animation.isStarted();
}

void Bird::startMove(Direction direction)
{
    // starting movement is only permitted while we're not moving
    if(isMoving()) return;

    // set target position, which is half a block left/right.
    Vector2D target;
    if (direction == Direction::TOPLEFT || direction == Direction::BOTTOMLEFT) {
        target.setX(_pos.getX() - Const::OBJ_WIDTH/2);
    }
    if (direction == Direction::TOPRIGHT || direction == Direction::BOTTOMRIGHT) {
        target.setX(_pos.getX() + Const::OBJ_WIDTH/2);
    }
    if (direction == Direction::TOPLEFT || direction == Direction::TOPRIGHT) {
        target.setY(_pos.getY() - Const::BOX_PROJECTED_HEIGHT);
    }
    if (direction == Direction::BOTTOMLEFT || direction == Direction::BOTTOMRIGHT) {
        target.setY(_pos.getY() + Const::BOX_PROJECTED_HEIGHT);
    }

    _direction = direction;

    Logger::debug(TAG, "Moving=%s, Start={%d,%d}, Target={%d,%d}", 
        birdmoveToString(direction), 
        static_cast<int>(_pos.getX()), static_cast<int>(_pos.getY()),
        static_cast<int>(target.getX()), static_cast<int>(target.getY())
    );
    _animation.start(_pos, target, 500);  
}

void Bird::stopMoving()
{
    _animation.stop();
}

void Bird::update(uint64_t timespan_ms)
{
    if(!isMoving()) return;
    _animation.update(timespan_ms);
    _pos = _animation.getPos();
}

bool Bird::loadData(SDL_Renderer* renderer)
{
    if (!_texture_down.load(renderer)) {
        return false;
    }
    if (!_texture_up.load(renderer)) {
        return false;
    }
    _texture_down.setSize(Const::OBJ_WIDTH, Const::OBJ_HEIGHT);
    _texture_up.setSize(Const::OBJ_WIDTH, Const::OBJ_HEIGHT);
    return true;
}

void Bird::unloadData()
{
    _texture_down.unload();
    _texture_up.unload();
}

const char* Bird::birdmoveToString(Direction move) 
{
    switch(move) {
        case Direction::BOTTOMLEFT: return "BOTTOMLEFT";
        case Direction::BOTTOMRIGHT: return "BOTTOMRIGHT";
        case Direction::TOPLEFT: return "TOPLEFT";
        case Direction::TOPRIGHT: return "TOPRIGHT";
        case Direction::NONE: 
        default: return "NONE";
    }
}