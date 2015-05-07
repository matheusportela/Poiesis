// @file   StillAnimation.cpp
// @author Matheus Vieira Portela
// @date   05/05/2015
//
// @brief Animation that stands in place.

#include "StillAnimation.h"

StillAnimation::StillAnimation(const Point& position,
    std::string sprite, int numFrames, float frameDuration) :
    AnimatedGameObject(sprite, numFrames, frameDuration)
{
    SetCenter(position);
    InitializeTimer(numFrames, frameDuration);
}

void StillAnimation::InitializeTimer(int numFrames, float frameDuration)
{
    float duration = numFrames*frameDuration;
    timer.Set(duration);
}

void StillAnimation::Update(float dt)
{
    AnimatedGameObject::Update(dt);
    timer.Update(dt);
}

void StillAnimation::Render()
{
    AnimatedGameObject::Render();
}

bool StillAnimation::IsDead()
{
    return timer.IsFinished();
}

void StillAnimation::NotifyCollision(std::shared_ptr<GameObject> other)
{   
}

bool StillAnimation::Is(std::string type)
{
    return (type == "StillAnimation");
}