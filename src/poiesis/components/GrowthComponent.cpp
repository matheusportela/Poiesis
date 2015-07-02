#include "poiesis/components/GrowthComponent.h"

GrowthComponent::GrowthComponent(int threshold) :
    threshold(threshold), level(1), energy(0), growthPower(0)
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

int GrowthComponent::GetEnergy()
{
    return energy;
}

void GrowthComponent::SetEnergy(int energy)
{
    this->energy = energy;
}

int GrowthComponent::GetGrowthPower()
{
    return growthPower;
}

void GrowthComponent::SetGrowthPower(int growthPower)
{
    this->growthPower = growthPower;
}