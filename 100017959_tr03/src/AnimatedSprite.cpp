// @file   AnimatedSprite.cpp
// @author Matheus Vieira Portela
// @date   01/05/2015
//
// @brief Allows sequential rendering of sprites from a single image file.

#include "AnimatedSprite.h"

AnimatedSprite::AnimatedSprite(std::string file, int numFrames, float frameTime) :
    Sprite(file), currentFrame(0), numFrames(numFrames), frameTime(frameTime),
    elapsedTime(0.0)
{
    frameWidth = GetWidth()/numFrames;
    SetFrameClip();
}

void AnimatedSprite::UpdateElapsedTime(float dt)
{
    elapsedTime += dt;
}

void AnimatedSprite::ResetElapsedTime()
{
    elapsedTime = 0.0;
}

bool AnimatedSprite::IsFrameFinished()
{
    return (elapsedTime >= frameTime);
}

void AnimatedSprite::UpdateCurrentFrame()
{
    ++currentFrame;
    currentFrame = currentFrame == numFrames ? 0 : currentFrame;
}

void AnimatedSprite::SetFrameClip()
{
    int x = frameWidth*currentFrame;
    Point point(x, 0);
    SetClip(point, frameWidth, GetHeight());
}

void AnimatedSprite::RenderNextFrame()
{
    UpdateCurrentFrame();
    SetFrameClip();
    ResetElapsedTime();
}

void AnimatedSprite::Update(float dt)
{
    UpdateElapsedTime(dt);
    if (IsFrameFinished())
        RenderNextFrame();
}