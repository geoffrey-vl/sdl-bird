#ifndef BOX_H
#define BOX_H

#include "gameobject.h"
#include "../texture.h"

class Box : public GameObject
{
public:
    Box();

    void draw(SDL_Renderer* renderer) override;
    void update() override;
    bool loadData(SDL_Renderer* renderer) override;
    void unloadData() override;

private:
    Texture _texture;
};

#endif // BOX_H