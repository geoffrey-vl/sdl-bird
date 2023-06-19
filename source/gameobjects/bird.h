#ifndef BIRD_H
#define BIRD_H

#include "gameobject.h"
#include "../texture.h"

enum class BirdMove 
{
    NONE,
    TOPLEFT,
    TOPRIGHT,
    BOTTOMLEFT,
    BOTTOMRIGHT
};


class Bird : public GameObject
{
public:
    Bird(int x, int y);

    void draw(SDL_Renderer* renderer) override;
    void update(uint64_t timespan_ms) override;
    bool loadData(SDL_Renderer* renderer) override;
    void unloadData() override;
    void setDirection(BirdMove direction);
    bool isMoving();
    void stopMoving();

private:
    bool _isMoving;
    BirdMove _birddirection;
    Vector2D _direction;
    Vector2D _target;
    Vector2D _velocity;
    Vector2D _accel;
    Texture _texture;

    void setVelocity(const Vector2D& velocity);
    void setAcceleration(const Vector2D& accel);
    bool isMovingLeft();
    bool isMovingRight();
    const char* birdmoveToString(BirdMove move);
};
#endif // BIRD_H