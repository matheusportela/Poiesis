#include "poiesis/components/CombatComponent.h"

CombatComponent::CombatComponent() :
    power(0)
{
}

CombatComponent::CombatComponent(float power) :
    power(power)
{
}

std::string CombatComponent::GetComponentClass()
{
    return "CombatComponent";
}

float CombatComponent::GetPower()
{
    return power;
}

void CombatComponent::SetPower(float power)
{
    this->power = power;
}