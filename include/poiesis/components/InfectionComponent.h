// Stores whether the entity is infected with an anomaly.

#ifndef INFECTION_COMPONENT_H_
#define INFECTION_COMPONENT_H_

#include <string>

#include "bandit/Engine.h"

#include "poiesis/EntityFactory.h"
#include "poiesis/components/SpriteComponent.h"

enum InfectionType
{
    NoInfection,
    CannotInput,
    Vulnerable,
    CannotEat,
    StrongImpulses
};

class InfectionComponent : public Component
{
  public:
    InfectionComponent(InfectionType infectionType, bool transmissible = true,
        bool temporary = false, float remainingTime = 0);
    std::string GetComponentClass();

    InfectionType GetInfectionType();
    void SetInfectionType(InfectionType infectionType);

    bool GetTransmissible();
    void SetTransmissible(bool transmissible);

    bool GetTemporary();
    void SetTemporary(bool temporary);

    float GetRemainingTime();
    void SetRemainingTime(float remainingTime);

  private:
    InfectionType infectionType;

    // Whether the entity can spread the infection to others.
    bool transmissible;

    // Whether the infection is temporary or permanent.
    bool temporary;

    // Remaining time for infection to stop.
    float remainingTime;
};

#endif // INFECTION_COMPONENT_H_