#include "bird.h"
#include "../constants.h"

Bird::Bird(int x, int y) : 
    GameObject(x, y),
    _texture("data/assets/bird.png")
{
}

void Bird::draw(SDL_Renderer* renderer)
{
    _texture.render(renderer);
}

void Bird::update()
{
    _texture.setPos(_x, _y);
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