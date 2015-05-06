// @file   StillAnimation.cpp
// @author Matheus Vieira Portela
// @date   05/05/2015
//
// @brief Animation that stands in place.

#include "StillAnimation.h"

StillAnimation::StillAnimation(const Point& position,
    std::unique_ptr<Sprite> animatedSprite, float time)
{
    LOG_D("Animation position: " << position.ToString());
    sprite = std::move(animatedSprite);
    SetCenter(position);
    timer.Set(time);
}

void StillAnimation::UpdateAnimation(float dt)
{
    AnimatedSprite* animatedSprite = dynamic_cast<AnimatedSprite*>(sprite.get());
    animatedSprite->Update(dt);
}

void StillAnimation::Update(float dt)
{
    timer.Update(dt);
    UpdateAnimation(dt);    
}

void StillAnimation::Render()
{
    RenderSprite();
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