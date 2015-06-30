#include "poiesis/components/SpriteComponent.h"

SpriteComponent::SpriteComponent(std::string filename, Vector position,
    bool centered, float scale, int numFrames, float frameDuration, bool repeat) :
    filename(filename), position(position), centered(centered), scale(scale),
    currentFrame(1), numFrames(numFrames), frameDuration(frameDuration),
    repeat(repeat), elapsedTime(0.0)
{
}

std::string SpriteComponent::GetComponentClass()
{
    return "SpriteComponent";
}

std::string SpriteComponent::GetFilename()
{
    return filename;
}

void SpriteComponent::SetFilename(std::string filename)
{
    this->filename = filename;
}

Vector SpriteComponent::GetPosition()
{
    return position;
}

void SpriteComponent::SetPosition(Vector position)
{
    this->position = position;
}

bool SpriteComponent::GetCentered()
{
    return centered;
}

void SpriteComponent::SetCentered(bool centered)
{
    this->centered = centered;
}

float SpriteComponent::GetScale()
{
    return scale;
}

void SpriteComponent::SetScale(float scale)
{
    this->scale = scale;
}

int SpriteComponent::GetCurrentFrame()
{
    return currentFrame;
}

void SpriteComponent::SetCurrentFrame(int currentFrame)
{
    this->currentFrame = currentFrame;
}

int SpriteComponent::GetNumFrames()
{
    return numFrames;
}

void SpriteComponent::SetNumFrames(int numFrames)
{
    this->numFrames = numFrames;
}

float SpriteComponent::GetFrameDuration()
{
    return frameDuration;
}

void SpriteComponent::SetFrameDuration(float frameDuration)
{
    this->frameDuration = frameDuration;
}

bool SpriteComponent::GetRepeat()
{
    return repeat;
}

void SpriteComponent::SetRepeat(bool repeat)
{
    this->repeat = repeat;
}

float SpriteComponent::GetElapsedTime()
{
    return elapsedTime;
}

void SpriteComponent::SetElapsedTime(float elapsedTime)
{
    this->elapsedTime = elapsedTime;
}