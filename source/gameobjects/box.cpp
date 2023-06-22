#include "box.h"
#include "../constants.h"

Box::Box() : 
    GameObject(0, 0),
    _adjacents(),
    _texture("data/assets/box01.png")
{
    _adjacents[Direction::TOPLEFT] = nullptr;
    _adjacents[Direction::TOPRIGHT] = nullptr;
    _adjacents[Direction::BOTTOMLEFT] = nullptr;
    _adjacents[Direction::BOTTOMRIGHT] = nullptr;
}

std::shared_ptr<Box> Box::getAdjecent(Direction key)
{
    return _adjacents[key];
}

void Box::setAdjacent(Direction key, std::shared_ptr<Box> adjacent)
{
    _adjacents[key] = adjacent;
}

void Box::draw(SDL_Renderer* renderer)
{
    _texture.setPos(_pos.getX(), _pos.getY());
    _texture.render(renderer);
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