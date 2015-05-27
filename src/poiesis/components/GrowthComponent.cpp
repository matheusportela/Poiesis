#include "poiesis/components/GrowthComponent.h"

GrowthComponent::GrowthComponent(int threshold) :
    threshold(threshold), level(1), power(0)
{
}

std::string GrowthComponent::GetComponentClass()
{
    return "GrowthComponent";
}


int GrowthComponent::GetThreshold()
{
    return threshold;
}

void GrowthComponent::SetThreshold(int threshold)
{
    this->threshold = threshold;
}


int GrowthComponent::GetLevel()
{
    return level;
}

void GrowthComponent::SetLevel(int level)
{
    this->level = level;
}

int GrowthComponent::GetPower()
{
    return power;
}

void GrowthComponent::SetPower(int power)
{
    this->power = power;
}