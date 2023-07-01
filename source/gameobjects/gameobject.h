#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include <SDL2/SDL.h>
#include "../vector2d.h"

enum class Direction 
{
    NONE,
    TOPLEFT,
    TOPRIGHT,
    BOTTOMLEFT,
    BOTTOMRIGHT
};

class GameObject
{
public:
    GameObject(int x, int y) : 
        _pos(x, y)
    {}
    virtual ~GameObject() {}

    virtual void draw(SDL_Renderer* renderer) = 0;
    virtual void update(uint64_t timespan_ms) {}
    virtual bool loadData(SDL_Renderer* renderer) { return true; }
    virtual void unloadData() {}
    float getX() { return _pos.getX(); }
    float getY() { return _pos.getY(); }
    const Vector2D& getPos() const { return _pos; }
    void setX(float x) { _pos.setX(x); }
    void setY(float y) { _pos.setY(y); }
    void setPos(float x, float y) { _pos.setPos(x, y); }

protected:
    Vector2D _pos;
};
#endif // GAMEOBJECT_H