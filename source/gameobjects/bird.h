#ifndef BIRD_H
#define BIRD_H

#include "gameobject.h"
#include "../texture.h"

class Bird : public GameObject
{
public:
    Bird(int x, int y);

    void draw(SDL_Renderer* renderer) override;
    void update(uint64_t timespan_ms) override;
    bool loadData(SDL_Renderer* renderer) override;
    void unloadData() override;
    void setVelocity(const Vector2D& velocity);
    void setAcceleration(const Vector2D& accel);

private:
    Vector2D _velocity;
    Vector2D _accel;
    Texture _texture;
};
#endif // BIRD_H