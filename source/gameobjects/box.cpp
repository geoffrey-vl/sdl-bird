#include "box.h"
#include "../constants.h"

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
    GameObject::update();
    _texture.setPos(_pos.getX(), _pos.getY());
}

bool Box::loadData(SDL_Renderer* renderer)
{
    if (!_texture.load(renderer)) {
        return false;
    }
    _texture.setSize(Const::OBJ_WIDTH, Const::OBJ_HEIGHT);
    return true;
}

void Box::unloadData()
{
    _texture.unload();
}