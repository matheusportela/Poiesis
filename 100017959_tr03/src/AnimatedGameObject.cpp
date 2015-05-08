// @file   AnimatedGameObject.cpp
// @author Matheus Vieira Portela
// @date   07/05/2015
//
// @brief Abstract class for every object which contains an animated sprite.

#include "AnimatedGameObject.h"

AnimatedGameObject::AnimatedGameObject(std::string spriteFile, int numFrames,
    float frameDuration, bool repeat)
{
    InitializeAnimatedSprite(spriteFile, numFrames, frameDuration, repeat);
}

void AnimatedGameObject::InitializeAnimatedSprite(std::string spriteFile,
    int numFrames, int frameDuration, bool repeat)
{
    sprite = std::unique_ptr<Sprite>(new AnimatedSprite(spriteFile, numFrames,
        frameDuration, repeat));
}

void AnimatedGameObject::Update(float dt)
{
    UpdateAnimation(dt);
}

void AnimatedGameObject::UpdateAnimation(float dt)
{
    AnimatedSprite* animatedSprite = dynamic_cast<AnimatedSprite*>(sprite.get());
    animatedSprite->Update(dt);
}

void AnimatedGameObject::Render()
{
    RenderSprite();
}