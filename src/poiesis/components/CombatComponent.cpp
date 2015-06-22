#include "poiesis/components/CombatComponent.h"

CombatComponent::CombatComponent() :
    power(0)
{
}

CombatComponent::CombatComponent(int power) :
    power(power)
{
}

std::string CombatComponent::GetComponentClass()
{
    return "CombatComponent";
}

int CombatComponent::GetPower()
{
    return power;
}

void CombatComponent::SetPower(int power)
{
    this->power = power;
}