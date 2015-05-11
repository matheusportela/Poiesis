// @file   AnimatedSprite.cpp
// @author Matheus Vieira Portela
// @date   01/05/2015
//
// @brief Allows sequential rendering of sprites from a single image file.

#include "AnimatedSprite.h"

AnimatedSprite::AnimatedSprite(std::string file, int numFrames,
    float frameDuration, bool repeat) :
    Sprite(file), currentFrame(0), numFrames(numFrames), frameDuration(frameDuration),
    repeat(repeat), elapsedTime(0.0)
{
    AdjustWidth();

    // Clip initially to show only the clipped frame.
    SetFrameClip();
}

void AnimatedSprite::AdjustWidth()
{
    int newWidth = GetWidth()/numFrames;
    SetWidth(newWidth);
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
    return (elapsedTime >= frameDuration);
}

void AnimatedSprite::UpdateCurrentFrame()
{
    ++currentFrame;

    if (repeat)
        currentFrame = currentFrame == numFrames ? 0 : currentFrame;
    else
        currentFrame = currentFrame == numFrames ? currentFrame-1 : currentFrame;
}

void AnimatedSprite::SetFrameClip()
{
    int frameX = GetWidth()*currentFrame;
    Point point(frameX, 0);
    SetClip(point, GetWidth(), GetHeight());
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