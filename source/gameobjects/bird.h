#ifndef BIRD_H
#define BIRD_H

#include "gameobject.h"
#include "../texture.h"
#include "../animation.h"

class Bird : public GameObject
{
public:
    Bird(int x, int y);

    void draw(SDL_Renderer* renderer) override;
    void update(uint64_t timespan_ms) override;
    bool loadData(SDL_Renderer* renderer) override;
    void unloadData() override;
    void startMove(Direction direction);
    bool isMoving();
    void stopMoving();

private:
    Texture _texture_down;
    Texture _texture_up;
    JumpAnimation _animation;
    Direction _direction;
    
    const char* birdmoveToString(Direction move);
};
#endif // BIRD_H