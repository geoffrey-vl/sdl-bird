#ifndef BIRD_H
#define BIRD_H

#include "gameobject.h"
#include "../texture.h"

class Bird : public GameObject
{
public:
    Bird(int x, int y);

    void draw(SDL_Renderer* renderer) override;
    void update() override;
    bool loadData(SDL_Renderer* renderer) override;
    void unloadData() override;

private:
    Texture _texture;
};
#endif // BIRD_H