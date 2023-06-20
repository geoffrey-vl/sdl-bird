#include "bird.h"
#include "../constants.h"
#include "../logger/logger.h"

static const char* TAG = "Bird";

Bird::Bird(int x, int y) : 
    GameObject(x, y),
    _birddirection(BirdMove::NONE),
    _direction(0, 0),
    _target(0, 0),
    _velocity(0, 0),
    _accel(0, 0),
    _texture("data/assets/bird.png")
{
}

void Bird::draw(SDL_Renderer* renderer)
{
    _texture.setPos(_pos.getX(), _pos.getY());
    _texture.render(renderer);
}

bool Bird::isMoving()
{
    return _isMoving;
}

bool Bird::isMovingLeft()
{
    if (_birddirection == BirdMove::TOPLEFT || _birddirection == BirdMove::BOTTOMLEFT) {
        return true;
    }
    return false;
}

bool Bird::isMovingRight()
{
    if (_birddirection == BirdMove::TOPRIGHT || _birddirection == BirdMove::BOTTOMRIGHT) {
        return true;
    }
    return false;
}

void Bird::setVelocity(const Vector2D& velocity)
{
    _velocity = velocity;
}

void Bird::setAcceleration(const Vector2D& accel)
{
    _accel = accel;
}

void Bird::setDirection(BirdMove direction)
{
    // updating velocity is only permitted while we're not moving
    if(isMoving()) return;

    setVelocity({40,40});

    _birddirection = direction;
    
    // set target position, which is half a block left/right
    if (isMovingLeft()) {
        _target.setX(_pos.getX() - Const::OBJ_WIDTH/2);
    }
    if (isMovingRight()) {
        _target.setX(_pos.getX() + Const::OBJ_WIDTH/2);
    }
    if (_birddirection == BirdMove::TOPLEFT || _birddirection == BirdMove::TOPRIGHT) {
        _target.setY(_pos.getY() - Const::BOX_PROJECTED_HEIGHT);
    }
    if (_birddirection == BirdMove::BOTTOMLEFT || _birddirection == BirdMove::BOTTOMRIGHT) {
        _target.setY(_pos.getY() + Const::BOX_PROJECTED_HEIGHT);
    }

    // calc the Unit vector which gives us a sense of the direction
    _direction = _target - _pos;
    _direction.normalize();

    Logger::debug(TAG, "Moving=%s, Target={%d,%d}", birdmoveToString(direction), static_cast<int>(_target.getX()), static_cast<int>(_target.getY()));
    _isMoving = true;    
}

void Bird::stopMoving()
{
    setVelocity({0,0});
    _isMoving = false;
}

void Bird::update(uint64_t timespan_ms)
{
    if(!isMoving()) return;

    _velocity += _accel;

    // calc the remaining distance
    Vector2D remaining_dist = _target - _pos;

    // stop when we reach the target pos
    if (remaining_dist.getX() == 0) {
        stopMoving();
        return;
    };

    // make sure we don't overshoot the target pos
    Vector2D step = _velocity * (static_cast<float>(timespan_ms)/1000.0f);
    if (isMovingLeft()) {
        if (_pos.getX() - step.getX() < _target.getX()) {
            _pos = _target;
            return;
        }
    }
    if (isMovingRight()) {
        if ( _pos.getX() + step.getX() > _target.getX()) {
            _pos = _target;
            return;
        }
    }

    _pos += (_direction*step);
}

bool Bird::loadData(SDL_Renderer* renderer)
{
    if (!_texture.load(renderer)) {
        return false;
    }
    _texture.setSize(Const::OBJ_WIDTH, Const::OBJ_HEIGHT);
    return true;
}

void Bird::unloadData()
{
    _texture.unload();
}

const char* Bird::birdmoveToString(BirdMove move) 
{
    switch(move) {
        case BirdMove::BOTTOMLEFT: return "BOTTOMLEFT";
        case BirdMove::BOTTOMRIGHT: return "BOTTOMRIGHT";
        case BirdMove::TOPLEFT: return "TOPLEFT";
        case BirdMove::TOPRIGHT: return "TOPRIGHT";
        case BirdMove::NONE: 
        default: return "NONE";
    }
}