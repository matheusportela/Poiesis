#include "poiesis/components/SpriteComponent.h"

SpriteComponent::SpriteComponent(std::string filename, Vector position,
    bool centered, float scale) :
    filename(filename), position(position), centered(centered), scale(scale)
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