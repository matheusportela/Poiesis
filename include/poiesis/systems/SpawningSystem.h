// Creates food with time.

#ifndef SPAWNING_SYSTEM_H_
#define SPAWNING_SYSTEM_H_

#include "bandit/Engine.h"

#include "poiesis/EntityFactory.h"

enum SpawningType
{
    Level1CellSpawning,
    Level2CellSpawning,
    Level3CellSpawning,
    CellSpawning,
    CellParticleSpawning,
    FoodSpawning,
    BacteriumSpawning,
    VirusSpawning
};

class SpawningSystem : public System
{
  public:
    SpawningSystem(SpawningType spawningType, float spawningChance,
        float spawningPeriod);
    std::string GetName();
    void Update(float dt);
    void Spawn();
    void SpawnLevel1Cell();
    void SpawnLevel2Cell();
    void SpawnLevel3Cell();
    void SpawnCell();
    void SpawnCellParticle();
    void SpawnFood();
    void SpawnBacterium();
    void SpawnVirus();

  private:
    SpawningType spawningType;
    float spawningChance;
    PeriodicTimer timer;
    Random random;
};

#endif // SPAWNING_SYSTEM_H_