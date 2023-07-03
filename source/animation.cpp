#include "animation.h"

Animation::Animation() :
    _state(AnimationState::IDLE),
    _startpos(),
    _targetpos(),
    _currentpos(),
    _total_dist(),
    _direction(),
    _anim_time_ms(0),
    _millis_passed(0)
{
}

void Animation::start(Vector2D start_currentpos, Vector2D end_currentpos, uint64_t anim_time)
{
    _startpos = start_currentpos;
    _currentpos = start_currentpos;
    _targetpos = end_currentpos;
    _anim_time_ms = anim_time;
    _millis_passed = 0;
    _total_dist = end_currentpos - start_currentpos;
    _total_dist.abs();
    
    // Also set the Unit vector which gives us a sense of the direction.
    if(_startpos.getX() < _targetpos.getX())
        _direction.setX(1);
    if(_startpos.getX() > _targetpos.getX())
        _direction.setX(-1);
    if(_startpos.getY() < _targetpos.getY())
        _direction.setY(1);
    if(_startpos.getY() > _targetpos.getY())
        _direction.setY(-1);
    
    _state = AnimationState::STARTED;
}

void Animation::stop()
{
    _state = AnimationState::FINISHED;
}

LinearAnimation::LinearAnimation() : 
    Animation() 
{
}

AnimationState LinearAnimation::update(uint64_t timespan_ms)
{
    if(!isStarted()) return _state;

    // calc the travelled percentage
    _millis_passed += timespan_ms;
    float percentage_anim = static_cast<float>(_millis_passed) / _anim_time_ms;
    if (percentage_anim >= 1.0) {
        // stop when we reached the target time
        _currentpos.setX(_startpos.getX() + _total_dist.getX() * _direction.getX());
        _currentpos.setY(_startpos.getY() + _total_dist.getY() * _direction.getY());
        stop();
        return _state;
    };

    // calc the travelled distance and apply
    Vector2D travelled_dist = _total_dist * percentage_anim;
    _currentpos = _startpos + travelled_dist * _direction;

    return _state;
}

JumpAnimation::JumpAnimation() : 
    Animation() 
{
}

AnimationState JumpAnimation::update(uint64_t timespan_ms)
{
    if(!isStarted()) return _state;

    // calc the travelled percentage
    _millis_passed += timespan_ms;
    float percentage_anim = static_cast<float>(_millis_passed) / _anim_time_ms;
    if (percentage_anim >= 1.0) {
        // stop when we reached the target time
        _currentpos.setX(_startpos.getX() + _total_dist.getX() * _direction.getX());
        _currentpos.setY(_startpos.getY() + _total_dist.getY() * _direction.getY());
        stop();
        return _state;
    };

    // quorter of a sinus (90°) is the total amount we want to travel
    constexpr float RAD_TOTAL = M_PI / 2;
    // depending on the direction we're heading to we either start at
    // the top of the sinus (90°) when moving downwards the screen or
    // at 180° when going upwards
    const float rad_begin = (_direction.getY() > 0 ?  M_PI / 2 : M_PI);
    // calculate the radians we've already travelled and the current radial pos
    float rad_travelled = percentage_anim * RAD_TOTAL;
    float rad_currentpos = rad_begin - rad_travelled;

    // calculate sin/cosin from the current radial pos (= theta)
    // The sine will be used to calculate the new x position, the cosine
    // for the y position.
    float sinus = std::sin(rad_currentpos);
    float cosinus = std::cos(rad_currentpos);

    // calc new positions
    float new_x = _startpos.getX() + (cosinus * _total_dist.getX()) * _direction.getX();
    if (_direction.getY() < 0 ) {
        new_x += _total_dist.getX() * _direction.getX();
    }
    float new_y = _startpos.getY() + (_total_dist.getY() - (sinus * _total_dist.getY()));
    if (_direction.getY() < 0 ) {
        new_y -= _total_dist.getY();
    }
    _currentpos.setX(new_x);
    _currentpos.setY(new_y);
    return _state;
}