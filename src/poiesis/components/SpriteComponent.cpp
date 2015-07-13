#include "poiesis/components/SpriteComponent.h"

SpriteComponent::SpriteComponent(std::string filename, Vector position,
    float rotation, float rotationSpeed, bool centered, float scale,
    int numFrames, float frameDuration, bool repeat, bool multipleFiles) :
    filename(filename), position(position), rotation(rotation),
    rotationSpeed(rotationSpeed), centered(centered), scale(scale),
    numFrames(numFrames), frameDuration(frameDuration), repeat(repeat),
    multipleFiles(multipleFiles)
{
    Random r;

    if (frameDuration > 0)
        elapsedTime = r.GenerateFloat(0, frameDuration);
    else
        elapsedTime = 0;

    if (numFrames > 1)
        currentFrame = r.GenerateInt(0, numFrames);
    else
        currentFrame = 0;
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

float SpriteComponent::GetRotation()
{
    return rotation;
}

void SpriteComponent::SetRotation(float rotation)
{
    this->rotation = rotation;
}

float SpriteComponent::GetRotationSpeed()
{
    return rotationSpeed;
}

void SpriteComponent::SetRotationSpeed(float rotationSpeed)
{
    this->rotationSpeed = rotationSpeed;
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

bool SpriteComponent::GetMultipleFiles()
{
    return multipleFiles;
}

void SpriteComponent::SetMultipleFiles(bool multipleFiles)
{
    this->multipleFiles = multipleFiles;
}
