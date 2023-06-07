#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include <SDL2/SDL.h>
#include "../vector2d.h"

class GameObject
{
public:
    GameObject(int x, int y) : 
        _pos(x, y),
        _velocity(0, 0),
        _accel(0, 0)
    {}
    virtual ~GameObject() {}

    virtual void draw(SDL_Renderer* renderer) = 0;
    virtual void update() 
    {
        _velocity += _accel;
        _pos += _velocity;
    }
    virtual bool loadData(SDL_Renderer* renderer) { return true; }
    virtual void unloadData() {}
    void setX(int x) { _pos.setX(x); }
    void setY(int y) { _pos.setY(y); }
    void setPos(int x, int y) { _pos.setPos(x, y); }

protected:
    Vector2D _pos;
    Vector2D _velocity;
    Vector2D _accel;
};
#endif // GAMEOBJECT_H