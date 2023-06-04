#include "bird.h"

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
}

bool Bird::loadData(SDL_Renderer* renderer)
{
    return _texture.load(renderer);
}