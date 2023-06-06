#include "box.h"

Box::Box() : 
    GameObject(0, 0),
    _texture("data/assets/box01.png")
{
}

void Box::draw(SDL_Renderer* renderer)
{
    _texture.render(renderer);
}

void Box::update()
{
    _texture.setPos(_x, _y);
}

bool Box::loadData(SDL_Renderer* renderer)
{
    if (!_texture.load(renderer)) {
        return false;
    }
    _texture.setSize(64, 64);
    return true;
}

void Box::unloadData()
{
    _texture.unload();
}