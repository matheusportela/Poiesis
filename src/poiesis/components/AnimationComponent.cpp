#include "poiesis/components/AnimationComponent.h"

AnimationComponent::AnimationComponent(std::string filename, int numFrames,
    float frameDuration, bool repeat, Vector position, bool centered,
    float scale) :
    SpriteComponent(filename, position, centered, scale),
    currentFrame(1), numFrames(numFrames), frameDuration(frameDuration),
    repeat(repeat), elapsedTime(0.0)
{
}

std::string AnimationComponent::GetComponentClass()
{
    return "AnimationComponent";
}

int AnimationComponent::GetCurrentFrame()
{
    return currentFrame;
}

void AnimationComponent::SetCurrentFrame(int currentFrame)
{
    this->currentFrame = currentFrame;
}

int AnimationComponent::GetNumFrames()
{
    return numFrames;
}

void AnimationComponent::SetNumFrames(int numFrames)
{
    this->numFrames = numFrames;
}

float AnimationComponent::GetFrameDuration()
{
    return frameDuration;
}

void AnimationComponent::SetFrameDuration(float frameDuration)
{
    this->frameDuration = frameDuration;
}

bool AnimationComponent::GetRepeat()
{
    return repeat;
}

void AnimationComponent::SetRepeat(bool repeat)
{
    this->repeat = repeat;
}

float AnimationComponent::GetElapsedTime()
{
    return elapsedTime;
}

void AnimationComponent::SetElapsedTime(float elapsedTime)
{
    this->elapsedTime = elapsedTime;
}