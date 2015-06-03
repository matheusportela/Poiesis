// Creates cell with time.

#ifndef CELL_SPAWNING_SYSTEM_H_
#define CELL_SPAWNING_SYSTEM_H_

#include "bandit/Engine.h"

#include "poiesis/EntityFactory.h"

class CellSpawningSystem : public System
{
  public:
    std::string GetName();
    void Update(float dt);

  private:
    float accumulatedTime;
};

#endif // CELL_SPAWNING_SYSTEM_H_