// Creates food with time.

#ifndef SPAWNING_SYSTEM_H_
#define SPAWNING_SYSTEM_H_

#include "bandit/Engine.h"

#include "poiesis/EntityFactory.h"

enum SpawningType
{
    CellSpawning,
    FoodSpawning
};

class SpawningSystem : public System
{
  public:
    SpawningSystem(SpawningType spawningType, float spawningChance,
        float spawningPeriod);
    std::string GetName();
    void Update(float dt);
    void Spawn();
    void SpawnCell();
    void SpawnFood();

  private:
    SpawningType spawningType;
    float spawningChance;
    PeriodicTimer timer;
    Random random;
};

#endif // SPAWNING_SYSTEM_H_