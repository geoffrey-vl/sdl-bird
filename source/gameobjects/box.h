#ifndef BOX_H
#define BOX_H

#include "gameobject.h"
#include "../texture.h"
#include <map>
#include <memory>

class Box : public GameObject
{
public:
    Box();

    void draw(SDL_Renderer* renderer) override;
    bool loadData(SDL_Renderer* renderer) override;
    void unloadData() override;
    std::shared_ptr<Box> getAdjecent(Direction key);
    void setAdjacent(Direction key, std::shared_ptr<Box> adjacent);

private:
    std::map<Direction, std::shared_ptr<Box>> _adjacents;
    Texture _texture;
};

#endif // BOX_H