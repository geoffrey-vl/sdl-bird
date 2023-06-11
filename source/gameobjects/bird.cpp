#include "bird.h"
#include "../constants.h"

Bird::Bird(int x, int y) : 
    GameObject(x, y),
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

void Bird::setVelocity(const Vector2D& velocity)
{
    _velocity = velocity;
}

void Bird::setAcceleration(const Vector2D& accel)
{
    _accel = accel;
}

void Bird::update(uint64_t timespan_ms)
{
    _velocity += _accel;
    _pos += _velocity;
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