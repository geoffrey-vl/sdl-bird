#include "bird.h"
#include "../constants.h"

Bird::Bird(int x, int y) : 
    GameObject(x, y),
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
    if (_velocity.getX() < 0) return true;
    return false;
}

bool Bird::isMovingRight()
{
    if (_velocity.getX() > 0) return true;
    return false;
}

void Bird::setVelocity(const Vector2D& velocity)
{
    // updating velocity is only permitted while we're not moving
    if(isMoving()) return;

    _velocity = velocity;
    // set target position, which is half a block left/right
    if (isMovingRight()) _target.setX(_pos.getX() + Const::OBJ_WIDTH/2);
    else if (isMovingLeft()) _target.setX(_pos.getX() - Const::OBJ_WIDTH/2);
    _target.setY(_pos.getY() + 54);

    // calc the Unit vector which gives us a sense of the direction
    _direction = _target - _pos;
    _direction.normalize();

    _isMoving = true;
}

void Bird::setAcceleration(const Vector2D& accel)
{
    _accel = accel;
}

void Bird::stopMoving()
{
    _velocity.setPos(0, 0);
    _isMoving = true;
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
    if (step.getX() + _pos.getX() > _target.getX()) {
        _pos = _target;
        return;
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