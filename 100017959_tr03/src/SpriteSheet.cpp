// @file   SpriteSheet.cpp
// @author Matheus Vieira Portela
// @date   01/05/2015
//
// @brief Allows sequential rendering of sprites from a single image file.

#include "SpriteSheet.h"

SpriteSheet::SpriteSheet(std::string file, int numFrames, float frameTime) :
    Sprite(file), currentFrame(0), numFrames(numFrames), frameTime(frameTime),
    elapsedTime(0.0)
{
    frameWidth = GetWidth()/numFrames;
    SetFrameClip();
}

void SpriteSheet::UpdateElapsedTime(float dt)
{
    elapsedTime += dt;
}

void SpriteSheet::ResetElapsedTime()
{
    elapsedTime = 0.0;
}

bool SpriteSheet::IsFrameFinished()
{
    return (elapsedTime >= frameTime);
}

void SpriteSheet::UpdateCurrentFrame()
{
    ++currentFrame;
    currentFrame = currentFrame == numFrames ? 0 : currentFrame;
}

void SpriteSheet::SetFrameClip()
{
    int x = frameWidth*currentFrame;
    Point point(x, 0);
    SetClip(point, frameWidth, GetHeight());
}

void SpriteSheet::RenderNextFrame()
{
    UpdateCurrentFrame();
    SetFrameClip();
    ResetElapsedTime();
}

void SpriteSheet::Update(float dt)
{
    UpdateElapsedTime(dt);
    if (IsFrameFinished())
        RenderNextFrame();
}