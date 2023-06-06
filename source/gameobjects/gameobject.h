#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include <SDL2/SDL.h>

class GameObject
{
public:
    GameObject(int x, int y) : _x(x), _y(y) {}
    virtual ~GameObject() {}

    virtual void draw(SDL_Renderer* renderer) = 0;
    virtual void update() = 0;
    virtual bool loadData(SDL_Renderer* renderer) { return true; }
    virtual void unloadData() {}
    void setX(int x) { _x = x; }
    void setY(int y) { _y = y; }
    void setPos(int x, int y) { _x = x; _y = y; }

protected:
    int _x;
    int _y;
};
#endif // GAMEOBJECT_H