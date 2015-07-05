#include "poiesis/components/VitaminComponent.h"

VitaminComponent::VitaminComponent(float growthFactor) :
    growthFactor(growthFactor)
{
}

std::string VitaminComponent::GetComponentClass()
{
    return "VitaminComponent";
}

float VitaminComponent::GetGrowthFactor()
{
    return growthFactor;
}

void VitaminComponent::SetGrowthFactor(float growthFactor)
{
    this->growthFactor = growthFactor;
}