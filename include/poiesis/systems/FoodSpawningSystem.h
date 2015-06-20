// Creates food with time.

#ifndef FOOD_SPAWNING_SYSTEM_H_
#define FOOD_SPAWNING_SYSTEM_H_

#include "bandit/Engine.h"

#include "poiesis/EntityFactory.h"

class FoodSpawningSystem : public System
{
  public:
    FoodSpawningSystem();
    std::string GetName();
    void Update(float dt);
    void SpawnFood();

  private:
    Timer timer;
};

#endif // FOOD_SPAWNING_SYSTEM_H_