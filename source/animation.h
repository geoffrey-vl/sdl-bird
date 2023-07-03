#ifndef ANIMATION_H
#define ANIMATION_H

#include "vector2d.h"
#include "stdint.h"

enum class AnimationState
{
    IDLE,
    STARTED,
    FINISHED
};

class Animation
{
public:
    virtual ~Animation() {};

    virtual void start(Vector2D start_pos, Vector2D end_pos, uint64_t anim_time);
    virtual AnimationState update(uint64_t timespan_ms) = 0;
    AnimationState getState() { return _state; };
    void stop();
    bool isStarted() { return _state == AnimationState::STARTED; }
    Vector2D getPos() { return _currentpos; }

protected:
    Animation();

    AnimationState _state;
    Vector2D _startpos;
    Vector2D _targetpos;
    Vector2D _currentpos;
    Vector2D _total_dist;
    Vector2D _direction; // unit vector
    uint64_t _anim_time_ms;
    uint64_t _millis_passed;
};

class LinearAnimation : public Animation
{
public:
    LinearAnimation();

    virtual AnimationState update(uint64_t timespan_ms) override;
};

class JumpAnimation : public Animation
{
public:
    JumpAnimation();

    virtual AnimationState update(uint64_t timespan_ms) override;
};

#endif //ANIMATION_H